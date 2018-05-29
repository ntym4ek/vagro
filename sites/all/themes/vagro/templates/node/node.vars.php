<?php
/**
 * @file
 * Stub file for "page" theme hook [pre]process functions.
 */

/**
 * Pre-processes variables for the "node" theme hook.
 *
 * See template for list of available variables.
 *
 * @see node.tpl.php
 *
 * @ingroup theme_preprocess
 */
function vagro_preprocess_node(&$vars) {
  /** ----- возможность создания отдельных шаблонов для разных view mode
   *  ----- http://xandeadx.ru/blog/drupal/576 -----
   */
  $node_type_suggestion_key = array_search('node__' . $vars['type'], $vars['theme_hook_suggestions']);
  if ($node_type_suggestion_key !== FALSE) {
    $node_view_mode_suggestion = 'node__' . $vars['view_mode'];
    array_splice($vars['theme_hook_suggestions'], $node_type_suggestion_key + 1, 0, array($node_view_mode_suggestion));

    $node_type_view_mode_suggestion = 'node__' . $vars['type'] . '__' . $vars['view_mode'];
    array_splice($vars['theme_hook_suggestions'], $node_type_suggestion_key + 2, 0, array($node_type_view_mode_suggestion));
  }

  /** ----- Подготовить Анонс Записи ---------------------------------------- */
  // фото
  if ($vars['view_mode'] == 'teaser') {
    global $user;
    $photo_style = 'thumbnail';
    $photo_uri = 'public://default_images/no_photo.png';

    if ($user = user_load($user->uid)) {
      $photo_uri = $user->picture->uri;
      $vars['author_title'] = $user->realname;
      $vars['author_url'] = url('user/' . $user->uid);
    }
    $vars['author_photo'] = image_style_url($photo_style, $photo_uri);
  }

  //
  $vars['post_url'] = url('node/' . $vars['node']->nid);
}


