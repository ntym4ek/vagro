<?php

/**
 * Page callback: Builds the post administration overview.
 */
function post_admin_posts() {

  // Формируем сортируемую шапку для таблицы.
  $header = array(
    'uid' => array('data' => t('UID'), 'field' => 'p.uid'),
    'author' => t('Author'),
    'rectype' => array('data' => t('Recipient type'), 'field' => 'p.rectype'),
    'recid' => array('data' => t('Rcp ID'), 'field' => 'p.recid'),
    'created' => array('data' => t('Created'), 'field' => 'p.created', 'sort' => 'desc'),
    'message' => array('data' => t('Message'), 'field' => 'p.message'),
//    'operations' => array('data' => t('Operations')),
  );

  $query = db_select('posts', 'p')->extend('PagerDefault')->extend('TableSort');
  $post_ids = $query->fields('p', array('id'))
    ->limit(50)
    ->orderByHeader($header)
    ->execute()
    ->fetchCol();

  $posts = post_load_multiple($post_ids);

  // Подготавливаем список Записей.
  $destination = drupal_get_destination();
  $rows = array();
  foreach ($posts as $post) {
    $rows[$post->id] = array(
//      'title' => array(
//        'data' => array(
//          '#type' => 'link',
//          '#title' => $post->title,
//          '#href' => 'post/' . $post->id,
//        ),
//      ),
      'uid' => $post->uid,
      'author' => theme('username', array('account' => $post)),
      'rectype' => $post->rectype,
      'recid' => $post->recid,
      'message' => $post->message,
      'created' => format_date($post->created, 'short'),
    );

    // Формируем список доступных операций над текущей Записью.
//    $operations = array();
//    if (post_access('update', 'post', $post)) {
//      $operations['edit'] = array(
//        'title' => t('edit'),
//        'href' => 'post/' . $post->id . '/edit',
//        'query' => $destination,
//      );
//    }
//    if (post_access('delete', 'post', $post)) {
//      $operations['delete'] = array(
//        'title' => t('delete'),
//        'href' => 'post/' . $post->id . '/delete',
//        'query' => $destination,
//      );
//    }
//
//    $rows[$post->id]['operations'] = array();
//    if (count($operations) > 1) {
//      // Выводим операции в виде списка.
//      $rows[$post->id]['operations'] = array(
//        'data' => array(
//          '#theme' => 'links__post_operations',
//          '#links' => $operations,
//          '#attributes' => array('class' => array('links', 'inline')),
//        ),
//      );
//    }
//    elseif (!empty($operations)) {
//      // Выводим первую и единственную операцию.
//      $link = reset($operations);
//      $rows[$post->id]['operations'] = array(
//        'data' => array(
//          '#type' => 'link',
//          '#title' => $link['title'],
//          '#href' => $link['href'],
//          '#options' => array('query' => $link['query']),
//        ),
//      );
//    }
  }

  $page = array();
  $page['posts'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('No posts available.'),
  );

  $page['pager'] = array('#markup' => theme('pager'));

  return $page;
}