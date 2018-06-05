<?php

/**
 * Page callback: Displays the user page.
 *
 * Displays user friends page
 *
 * @return
 *   A render array for either a user profile or a login form.
 *
 * @see user_view_page()
 * @see user_login()
 */
function post_friends_page() {
  global $user;
  if ($user->uid) {
    menu_set_active_item('user/' . $user->uid . '/friends');
    return menu_execute_active_handler(NULL, FALSE);
  }
}

function _friends_menu_block_content()
{
  $uid = $GLOBALS['user']->uid;

  // дерево пунктов меню
  $tree = array();
  $tree[]['link'] = array(
    'title' => 'My friends',
    'href' => "user/$uid/friends",
  );
  $tree[]['link'] = array(
    'title' => 'Pending friends',
    'href' => "user/$uid/friends/pending",
  );
  $tree[]['link'] = array(
    'title' => 'Friend requests',
    'href' => "user/$uid/friends/flagged",
  );

  // значения общие для всех пунктов
  $default_link = array(
    'menu_name' => '',
    'access_callback' => 'flag_friend_views_access',
    'hidden' => 0,
    'has_children' => 0,
    'access' => TRUE,
  );

  // заполнить массив общими и дефолтными значениями
  foreach($tree as $key => $leaf) {
    $tree[$key]['link'] = array_merge($leaf['link'], $default_link);
    $tree[$key]['link']['mlid'] = $key;
    $tree[$key]['link']['in_active_trail'] = $_GET['q'] == "user/$uid/friends";
    $tree[$key]['below'] = array();
  }

  // Build links.
  $friends_nav = menu_tree_output($tree);

  return render($friends_nav);
}

