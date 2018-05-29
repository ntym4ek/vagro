<?php

/**
 * функции отображения блоков на страницах сайта
 * возвращает true для страниц, где нужно отобразить блок
 */


/**
 * блок Входа
 */
function login_helper_blocks()
{
  global $user;
  return !$user->uid && !(arg(0) == 'user' && !is_numeric(arg(1)));
}

/**
 * блок Регистрации
 */
function register_helper_blocks()
{
  global $user;
  return !$user->uid && !(arg(0) == 'user' && !is_numeric(arg(1)));
}

/**
 * блок формы создания Записи
 */
function post_form_helper_blocks()
{
  $pages = ['post/*/edit', 'post/*/delete'];
  return _check_pages_match($pages, FALSE) && post_access("create", "post");
}

/**
 * блок меню вывода Новостей
 */
function news_menu_helper_blocks()
{
  $pages = ['posts', 'post/*'];
  return _check_pages_match($pages, TRUE);
}

/**
 * блок меню вывода Фото пользователя
 */
function profile_photo_helper_blocks()
{
  $pages = ['user/*'];
  return _check_pages_match($pages, TRUE);
}

/**
 * блок меню вывода Фото пользователя
 */
function profile_actions_helper_blocks()
{
  $pages = ['edit/*'];
  return _check_pages_match($pages, TRUE);
}



/**
 * проверка совпадения массива страниц и текущей страницы
 * @param $pages - массив страниц
 * @param $visibility - можно задать совпадение или несовпадение
 * @return bool
 */
function _check_pages_match($pages, $visibility = TRUE)
{
  $pages = drupal_strtolower(implode(chr(13), $pages));
  if ($pages) {
    $path = drupal_strtolower(drupal_get_path_alias($_GET['q']));
    // Compare the lowercase internal and lowercase path alias (if any).
    $page_match = drupal_match_path($path, $pages);
    if ($path != $_GET['q']) {
      $page_match = $page_match || drupal_match_path($_GET['q'], $pages);
    }
    $page_match = !($visibility xor $page_match);
  }
  else {
    $page_match = FALSE;
  }

  return $page_match;
}

/**
 * -------------------------- Extended block visibility --------------------------------------------
 * функции, определяющие видимость блоков при использовании модуля
 * https://www.drupal.org/project/extended_block_visibility
 * todo переделать бы под свои функции видимости а блок отключить
 */
function _vagro_system_main_menu_block_visibility()
{
  return (user_is_anonymous()) ? false : true;
}

function _vagro_views_posts_block_block_visibility()
{
  $pages = ['posts', 'user', 'user/*'];
  return _check_pages_match($pages, TRUE);
}