<?php

/**
 * Implements hook_metatag_info().
 */
function improvements_metatag_info() {
  $info['tags']['h1'] = array(
    'label' => 'H1',
    'description' => '',
    'class' => 'DrupalH1MetaTag',
    'group' => 'basic',
  );

  return $info;
}

/**
 * Process function for page.tpl.php.
 */
function improvements_process_page(&$vars) {
  if (!empty($GLOBALS['improvements']['page_title'])) {
    $vars['title'] = $GLOBALS['improvements']['page_title'];
  }
}
