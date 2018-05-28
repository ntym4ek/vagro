<?php

function posts_page()
{
  return '';
}

/**
 * Menu callback: Displays a single post.
 *
 * @param $post
 *   The post object.
 *
 * @return array
 *   A page array suitable for use by drupal_render().
 *
 * @see post_menu()
 */
function post_page_view($post) {
  // For markup consistency with other pages, use post_view_multiple() rather than post_view().
  $posts = post_view_multiple(array($post->id => $post), 'full');

  return $posts;
}

/**
 * Presents the post editing form.
 */
function post_page_edit($post) {
  return drupal_get_form('post_form', $post);
}




/**
 * Form constructor for the post deletion confirmation form.
 *
 * @see post_delete_confirm_submit()
 */
function post_delete_confirm($form, &$form_state, $post) {
  $form['post_id'] = array('#type' => 'value', '#value' => $post->id);
  return confirm_form($form,
    t('Are you sure you want to delete post?'),
    'posts',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Executes post deletion.
 *
 * @see post_delete_confirm()
 */
function post_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    post_delete($form_state['values']['post_id']);
    drupal_set_message(t('Post has been deleted.'));
  }

  $form_state['redirect'] = 'admin/config/post/posts';
}