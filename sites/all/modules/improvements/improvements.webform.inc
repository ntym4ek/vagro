<?php

/**
 * Implements hook_form_FORM_ID_alter(): webform_configure_form.
 */
function improvements_form_webform_configure_form_alter(&$form, &$form_state) {
  $webform_node = $form['#node'];
  $webform_settings = !empty($webform_node->data) ? $webform_node->data : array();

  $form['advanced']['use_ajax'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use AJAX'),
    '#default_value' => !empty($webform_settings['webform_ajax']),
    '#weight' => 0.005,
  );

  $form['#submit'][] = 'improvements_webform_configure_form_submit';
}

/**
 * Submit callback for webform_configure_form.
 */
function improvements_webform_configure_form_submit($form, &$form_state) {
  $webform_node = &$form['#node'];
  $webform_node->data['webform_ajax'] = (bool)$form_state['values']['use_ajax'];
  node_save($webform_node);
}

/**
 * Implements hook_form_FORM_ID_alter(): webform_client_form.
 */
function improvements_form_webform_client_form_alter(&$form, &$form_state) {
  $webform_node = $form['#node'];
  $webform_settings = !empty($webform_node->data) ? $webform_node->data : array();

  if (!empty($webform_settings['webform_ajax'])) {
    $form['actions']['submit']['#ajax'] = array(
      'callback' => 'improvements_webform_client_form_ajax_submit',
      'wrapper' => $form['#id'],
      'event' => 'click',
    );

    unset($form['actions']['submit']['#pre_render']);
  }
}

/**
 * Webform ajax submit.
 */
function improvements_webform_client_form_ajax_submit($form, &$form_state) {
  if (form_get_errors()) {
    return $form;
  }
  else {
    $webform = $form['#node']->webform;
    return '
      <div class="webform-confirmation-message">
        ' . check_markup($webform['confirmation'], $webform['confirmation_format']) . '
      </div>
    ';
  }
}
