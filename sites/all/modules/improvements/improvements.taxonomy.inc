<?php

/**
 * Implements hook_form_FORM_ID_alter(): taxonomy_form_vocabulary.
 */
function improvements_form_taxonomy_form_vocabulary_alter(&$form, &$form_state) {
  $vocabulary = $form_state['vocabulary'];
  $vocabulary_settings = isset($vocabulary->data) ? $vocabulary->data : array();

  $form['disable_description'] = array(
    '#title' => t('Disable description field'),
    '#type' => 'checkbox',
    '#default_value' => isset($vocabulary_settings['disable_description']) ? $vocabulary_settings['disable_description'] : FALSE,
  );

  $form['disable_parents'] = array(
    '#title' => t('Disable parents'),
    '#type' => 'checkbox',
    '#default_value' => isset($vocabulary_settings['disable_parents']) ? $vocabulary_settings['disable_parents'] : FALSE,
  );

  if (module_exists('path')) {
    $form['disable_path'] = array(
      '#title' => t('Disable path settings'),
      '#type' => 'checkbox',
      '#default_value' => isset($vocabulary_settings['disable_path']) ? $vocabulary_settings['disable_path'] : FALSE,
    );
  }

  array_unshift($form['#submit'], 'improvements_form_taxonomy_form_vocabulary_submit');
}

/**
 * Custom submit callback for taxonomy_form_vocabulary form.
 */
function improvements_form_taxonomy_form_vocabulary_submit($form, &$form_state) {
  $vocabulary = $form_state['vocabulary'];
  $settings_name = array('disable_description', 'disable_parents', 'disable_path');

  foreach ($settings_name as $setting_name) {
    $vocabulary->data[$setting_name] = isset($form_state['values'][$setting_name]) ? $form_state['values'][$setting_name] : NULL;
  }
}

/**
 * Implements hook_form_FORM_ID_alter(): taxonomy_form_term
 */
function improvements_form_taxonomy_form_term_alter(&$form, &$form_state) {
  $vocabulary = $form['#vocabulary'];
  $vocabulary_seetings = $vocabulary->data ? $vocabulary->data : array();

  // Autofocus to term name
  if (isset($form['name']) && empty($form['name']['#default_value'])) {
    $form['name']['#attributes']['autofocus'] = 'autofocus';
  }

  // Disable description field
  if (!empty($vocabulary_seetings['disable_description'])) {
    $form['description']['#access'] = FALSE;
  }

  // Disable parents
  if (!empty($vocabulary_seetings['disable_parents'])) {
    $form['relations']['parent']['#access'] = FALSE;
  }

  $form['#after_build'][] = 'improvements_form_taxonomy_form_term_after_build';
}

/**
 * Form taxonomy_form_term() after build callback.
 */
function improvements_form_taxonomy_form_term_after_build($form, $form_state) {
  $vocabulary = $form['#vocabulary'];
  $vocabulary_seetings = $vocabulary->data ? $vocabulary->data : array();

  if (isset($form['path'])) {
    if (!empty($vocabulary_seetings['disable_path'])) {
      $form['path']['#access'] = FALSE;
    }
  }

  return $form;
}
