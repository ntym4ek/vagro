<?php

/**
 * @file
 * Stub file for "block" theme hook [pre]process functions.
 */

/**
 * Pre-processes variables for the "block" theme hook.
 *
 * See template for list of available variables.
 *
 * @param array $vars
 *   An associative array of variables, passed by reference.
 *
 * @see block.tpl.php
 *
 * @ingroup theme_preprocess
 */
function vagro_preprocess_block(&$vars) {
  if (in_array($vars['block']->delta, ['main-menu'])
      || in_array($vars['block']->region, ['footer'])){
    $vars['classes_array'] = array_diff($vars['classes_array'], ['block']);
  }

  // убрать обёртку блока при выводе контента
  if ($vars['block_html_id'] == 'block-system-main') {
    $vars['theme_hook_suggestions'][] = 'block__no_wrapper';
  }
}
