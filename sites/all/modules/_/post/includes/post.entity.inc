<?php

include 'post.user.inc';

/**
 * Implements hook_entity_info().
 */
function post_entity_info() {
  $return = array(
    // Ключ 'post' - машинное название сущности.
    'post' => array(
      'label' => t('Post'), // Человеко-понятное название сущности.
      'entity class' => 'Entity', // Класс сущности.
      'controller class' => 'EntityAPIController', // Контроллер сущности.
      'views controller class' => 'EntityDefaultViewsController',
      'base table' => 'post', // Таблица, в которой хранится информация об сущностях.
      'view callback' => 'post_view_multiple', // Функция, которая генерирует рендер массив сущности.
      'uri callback' => 'post_uri', // Функция, которая возваращает uri сущности.
      'fieldable' => TRUE, // Позволяем прикреплять поля к сущности.
      'entity keys' => array('id' => 'id'),
      // Массив, в котором описываются типы сущности Post
      // если привести анологию с модулем Node, то это типы материалов.
      'bundles' => array(
        // Ключ 'post' - машинное название типа.
        'post' => array(
          'label' => t('Post'), // Человеко-понятное название типа.
          'admin' => array(
            'path' => 'admin/config/post/posts', // Путь, по которому доступна админка.
            'access arguments' => array('configure post settings'), // Права доступа в админку.
          ),
        ),
      ),
      // Режимы отображения сущности.
      'view modes' => array(
        // Ключи 'full' и 'administrator'  - машинные названия режимов.
        'full' => array(
          'label' => t('Full'), // Человеко-понятное название режима.
          'custom settings' => TRUE, // Режим включен по умолчанию.
        ),
        'administrator' => array(
          'label' => t('Administrator'),
          'custom settings' => TRUE,
        ),
      ),
      'module' => 'post',
    ),
  );

  return $return;
}

/**
 * Implements callback_entity_info_uri().
 */
function post_uri($post) {
  return array(
    'path' => 'post/' . $post->id,
  );
}


/**
 * Determines whether the current user may perform the operation on the post.
 *
 * @param $op
 *   The operation to be performed on the post. Possible values are:
 *   - "view"
 *   - "update"
 *   - "delete"
 *   - "create"
 * @param $entity_type
 *   The entity type on which the operation is to be perform.
 * @param $post
 *   The post object on which the operation is to be performed.
 * @param $account
 *   Optional, a user object representing the user for whom the operation is to
 *   be performed. Determines access for a user other than the current user.
 *
 * @return bool
 *   TRUE if the operation may be performed, FALSE otherwise.
 */
function post_access($op, $entity_type, $post = NULL, $account = NULL)
{
  $rights = &drupal_static(__FUNCTION__, array());

  // todo так как отправителем Записи может быть любая сущность, сначала
  // нужно опрелелить владельца этой сущности, чьи права будем проверять дальше

    // для сущности 'user' владелец записан в $post->senid
  $uids = [];
  if ($post) {
    $callback = $post->sentype . '_entity_access';
    if (function_exists($callback)) { $uids = $callback($post->senid, $op); }
    if (count($uids) == 0) { return FALSE; }
  }

  if (!in_array($op, array('view', 'update', 'delete', 'create'), TRUE)) {
    // Если $op не равен ни одной из поддерживаемых операций, возвращаем "доступ запрещен".
    return FALSE;
  }

  // Если в функцию не передан пользователь, то проверяем права для текущего пользователя.
  if (empty($account)) {
    global $user;
    $account = $user;
  }

  // $post может быть объектом или не существовать, поэтому испольем его id,
  // или $entity_type в качестве статичного идентификатора, который будет использоваться ключом кеша.
  $cid = is_object($post) && !empty($post->id) ? $post->id : $entity_type;

  // Если мы уже проверяли для данной сущности и пользователя права доступа,
  // то возвращаем их из кеша.
  if (isset($rights[$account->uid][$cid][$op])) {
    return $rights[$account->uid][$cid][$op];
  }

  // Проверяем, может ли пользователь создавать новые Записи.
  if ($op == 'create' && user_access('create post', $account)) {
    $rights[$account->uid][$cid][$op] = TRUE;
    return TRUE;
  }

  if ($op == 'update') {
    // Проверяем, может ли пользователь редактирвоать любые Записи.
    if (user_access('edit any post', $account)) {
      $rights[$account->uid][$cid][$op] = TRUE;
      return TRUE;
    }
    // Проверяем, может ли пользователь редактирвоать свои Записи.
    elseif (user_access('edit own post', $account) && in_array($account->uid, $uids)) {
      $rights[$account->uid][$cid][$op] = TRUE;
      return TRUE;
    }
  }
  elseif ($op == 'delete') {
    // Проверяем, может ли пользователь удалять любые Записи.
    if (user_access('delete any post', $account)) {
      $rights[$account->uid][$cid][$op] = TRUE;
      return TRUE;
    }
    // Проверяем, может ли пользователь удалять свои Записи.
    elseif (user_access('delete own post', $account) && in_array($account->uid, $uids)) {
      $rights[$account->uid][$cid][$op] = TRUE;
      return TRUE;
    }
  }
  // Проверяем, может ли пользователь просматривать Записи.
  elseif ($op == 'view' && user_access('view post', $account)) {
    $rights[$account->uid][$cid][$op] = TRUE;
    return TRUE;
  }

  return FALSE;
}

/**
 * Loads a post by ID.
 */
function post_load($post_id) {
  $posts = post_load_multiple(array($post_id), array());
  return $posts ? reset($posts) : FALSE;
}

/**
 * Loads multiple posts by ID or based on a set of matching conditions.
 *
 * @see entity_load()
 *
 * @param $post_ids
 *   An array of post IDs.
 * @param $conditions
 *   An array of conditions to filter loaded posts by on the {post}
 *   table in the form 'field' => $value.
 * @param $reset
 *   Whether to reset the internal post loading cache.
 *
 * @return
 *   An array of post objects indexed by post_id.
 */
function post_load_multiple($post_ids = array(), $conditions = array(), $reset = FALSE) {
  return entity_load('post', $post_ids, $conditions, $reset);
}

/**
 * Implements hook_entity_load().
 */
function post_entity_load($entities, $type) {
  // По умолчанию, сущность имеет только sender id сущности, создавшей её,
  // добавляем код, чтобы получить наименование и изображение
  if ($type == 'post') {
    foreach ($entities as $entity) {
      $callback = $entity->sentype . '_post_info';
      if (function_exists($callback)) {
        $sender_info = $callback($entity->senid);
        $entity->sen_name = $sender_info['sen_name'];
        $entity->sen_img_uri = $sender_info['sen_img_uri'];
        $entity->sen_url = $sender_info['sen_url'];
      }
      else {
        $entity->name = variable_get('anonymous', t('Anonymous'));
      }
    }
  }
}


/**
 * Deletes a post.
 *
 * @param $post_id
 *   A post ID.
 */
function post_delete($post_id) {
  post_delete_multiple(array($post_id));
}

/**
 * Deletes multiple posts.
 *
 * @param $post_ids
 *   An array of post IDs.
 */
function post_delete_multiple($post_ids) {
  entity_delete_multiple('post', $post_ids);
}

/**
 * Implements hook_theme().
 */
function post_theme() {
  return array(
    'post' => array(
      'render element' => 'elements',
      'template' => 'templates/post',
    ),
  );
}


/**
 * Processes variables for post.tpl.php
 * подготовка переменных
 */
function post_preprocess_post(&$vars) {
  $vars['view_mode'] = $vars['elements']['#view_mode'];

  $vars['post'] = $vars['elements']['#post'];
  $post = $vars['post'];

  // время публикации
  if (REQUEST_TIME - $post->created > 24 * 60 * 60) {
    $vars['post_date'] = format_date($post->created, 'custom', 'M jS, Y');
  } else {
    $vars['post_date'] = format_interval(REQUEST_TIME - $post->created) . t(' ago');
  }

  // автор
  $vars['sen_name'] = $post->sen_name;
  $vars['sen_url'] = $post->sen_url;
  $sen_img_style = 'thumbnail';
  $sen_img_uri = empty($post->sen_img_uri) ? 'public://default_images/no_photo.png' : $post->sen_img_uri;
  $vars['sen_img_url'] = image_style_url($sen_img_style, $sen_img_uri);

  $uri = post_uri($post);
  $vars['post_url']  = url($uri['path']);

  $vars['page'] = $vars['view_mode'] == 'full';

  //$vars = array_merge((array) $post, $vars);

  $vars += array('content' => array());
  foreach (element_children($vars['elements']) as $key) {
    $vars['content'][$key] = $vars['elements'][$key];
  }

  // Делаем поля доступными в качестве переменных для соответствующего языка.
  field_attach_preprocess('post', $post, $vars['content'], $vars);

  // todo изучить тему о безопасном выводе, есть ли встроенные функции или
  // todo нужно заботиться самому
  $vars['message'] = strip_tags($post->message);

  // меню действий с постом
  $actions = [];
  if (post_access('update', 'post', $post)) { $actions[] = l(t('Edit'), 'post/' . $post->id . '/edit', array('query' => array('destination' => $_GET['q']))); }
  if (post_access('delete', 'post', $post)) { $actions[] = l(t('Delete'), 'post/' . $post->id . '/delete', array('query' => array('destination' => $_GET['q']))); }

  $vars['actions'] = theme('item_list',
    array(
      'items' => $actions,
      'title' => NULL,
      'type' => 'ul',
      'attributes' => array('class' => array('menu', 'nav', 'post-actions')),
    )
  );

  // соц. кнопки
  $vars['like'] = '<a href="#"><i class="far fa-heart"></i></a>';
  $vars['share'] = '<a href="#"><i class="far fa-share-square"></i></a>';

}

/**
 * Constructs a drupal_render() style array from an array of loaded posts.
 *
 * @param $posts
 *   An array of posts as returned by post_load_multiple().
 * @param $view_mode
 *   View mode, e.g. 'teaser', 'full'...
 * @param $langcode
 *   (optional) A language code to use for rendering. Defaults to NULL which is
 *   the global content language of the current request.
 *
 * @return array
 *   An array in the format expected by drupal_render().
 */
function post_view_multiple($posts, $view_mode = 'full', $langcode = NULL) {
  // Подготавливаем данные для отображения.
  field_attach_prepare_view('post', $posts, $view_mode, $langcode);
  entity_prepare_view('post', $posts, $langcode);
  $build = array();
  $weight = 0;
  foreach ($posts as $post) {
    $build['post'][$post->id] = post_view($post, $view_mode, $langcode);
    $build['post'][$post->id]['#weight'] = $weight++;
  }
  $build['post']['#sorted'] = TRUE;
  return $build;
}

/**
 * Generates an array for rendering the given post.
 *
 * @param $post
 *   A post object.
 * @param $view_mode
 *   View mode, e.g. 'teaser', 'full'...
 * @param $langcode
 *   (optional) A language code to use for rendering. Defaults to the global
 *   content language of the current request.
 *
 * @return array
 *   An array as expected by drupal_render().
 */
function post_view($post, $view_mode = 'full', $langcode = NULL) {
  if (!isset($langcode)) {
    global $language;
    $langcode = $language->language;
  }

  // Заполняем $post->content данными в виде рендерного массива.
  post_build_content($post, $view_mode, $langcode);

  $build = $post->content;
  // Скрываем данные, чтобы избежать их дублирования при выводе $post->content.
  unset($post->content);

  $build += array(
    '#theme' => 'post',
    '#post' => $post,
    '#view_mode' => $view_mode,
    '#language' => $langcode,
  );

  return $build;
}

/**
 * Builds a structured array representing the post's content.
 *
 * @param $post
 *   A post object.
 * @param $view_mode
 *   View mode, e.g. 'teaser', 'full'...
 * @param $langcode
 *   (optional) A language code to use for rendering. Defaults to the global
 *   content language of the current request.
 */
function post_build_content($post, $view_mode = 'full', $langcode = NULL) {
  if (!isset($langcode)) {
    global $language;
    $langcode = $language->language;
  }

  // Удаляем существующий конент, если существует.
  $post->content = array();

  field_attach_prepare_view('post', array($post->id => $post), $view_mode, $langcode);
  entity_prepare_view('post', array($post->id => $post), $langcode);
  $post->content += field_attach_view('post', $post, $view_mode, $langcode);

  $post->content += array('#view_mode' => $view_mode);

  $post->content['links'] = array(
    '#theme' => 'links__post',
    '#pre_render' => array('drupal_pre_render_links'),
    '#attributes' => array('class' => array('links')),
  );
}
