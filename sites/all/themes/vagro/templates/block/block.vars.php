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
function vagro_preprocess_block(array &$vars) {
  if (in_array($vars['block']->delta, ['main-menu', 'navigation'])
      || in_array($vars['block']->region, ['navigation', 'footer'])){
    $vars['classes_array'] = array_diff($vars['classes_array'], ['block']);
  }
}
