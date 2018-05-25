<?php

/**
 * @file
 * The primary PHP file for this theme.
 */

/**
 * Implements hook_pre_render().
 */
function vagro_pre_render($element) {
  // добавить для form select обёртку div, чтобы можно было темизировать с помощью css
  if (in_array($element['#type'], array('select', 'textfield'))) {
    $element['#field_prefix'] = '<div class="form-input-wrapper">';
    $element['#field_suffix'] = '</div>';
  }

  return $element;
}

/**
 * Override theme_textarea().
 */
function vagro_textarea($vars) {
  $element = $vars['element'];
  element_set_attributes($element, array('id', 'name', 'cols', 'rows'));
  _form_set_class($element, array('form-textarea'));
  return '<textarea' . drupal_attributes($element['#attributes']) . '>' . check_plain($element['#value']) . '</textarea>';
}