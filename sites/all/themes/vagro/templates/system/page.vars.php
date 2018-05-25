<?php

/**
 * @file
 * Stub file for "page" theme hook [pre]process functions.
 */

/**
 * Pre-processes variables for the "page" theme hook.
 *
 * See template for list of available variables.
 *
 * @param array $variables
 *   An associative array of variables, passed by reference.
 *
 * @see page.tpl.php
 *
 * @ingroup theme_preprocess
 */
function vagro_preprocess_page(array &$vars)
{
  // Изменить ширину контента под 20 колоночную разметку
  if (!empty($vars['page']['sidebar_first']) && !empty($vars['page']['sidebar_second'])) {
    $vars['content_column_class'] = ' class="col-sm-12"';
  }
  elseif (!empty($vars['page']['sidebar_first']) || empty($vars['page']['sidebar_second'])) {
    $vars['content_column_class'] = ' class="col-sm-17"';
  }
  elseif (empty($vars['page']['sidebar_first']) || !empty($vars['page']['sidebar_second'])) {
    $vars['content_column_class'] = ' class="col-sm-15"';
  }
  else {
    $vars['content_column_class'] = ' class="col-sm-20"';
  }

  // убрать класс Container из TopBar
  $vars['navbar_classes_array'] = array_diff($vars['navbar_classes_array'], ['container']);
}

/**
 * Processes variables for the "page" theme hook.
 *
 * See template for list of available variables.
 *
 * @param array $variables
 *   An associative array of variables, passed by reference.
 *
 * @see page.tpl.php
 *
 * @ingroup theme_process
 */
function vagro_process_page(array &$var)
{
}
