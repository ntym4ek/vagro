<?php

function vagro_preprocess_user_profile(&$vars)
{
  /** ----- возможность создания отдельных шаблонов для разных view mode
   *  ----- http://xandeadx.ru/blog/drupal/576 -----
   */
  $node_view_mode_suggestion = 'user_profile__' . $vars['elements']['#view_mode'];
  array_splice($vars['theme_hook_suggestions'], 1, 0, array('user_profile'));
  array_splice($vars['theme_hook_suggestions'], 2, 0, array($node_view_mode_suggestion));

  $aid = $vars['elements']['#account']->uid;
  $vars['user_url'] = url('user/' . $aid);
  $vars['username'] = empty($vars['elements']['#account']->realname) ? $vars['elements']['#account']->name : $vars['elements']['#account']->realname;

  if ($vars['elements']['#view_mode'] == 'teaser') {
    // меню действий с пользователем
    $actions = [];
//  $actions[] = 'Действие 1';
//  $actions[] = 'Действие 2';

    $vars['actions'] = theme('item_list',
      array(
        'items' => $actions,
        'title' => NULL,
        'type' => 'ul',
        'attributes' => array('class' => array('menu', 'nav', 'user-actions')),
      )
    );
  } else {
    $vars['counts']['friends'] = count(flag_friend_get_friends_query($aid));
  }

  // кнопки флагов, отключить заголовки категорий
  $vars['user_profile']['flags']['#title'] = '';
  $vars['user_profile']['flags']['friend']['#title'] = '';
}