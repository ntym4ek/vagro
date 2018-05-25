<?php

/**
 * Implements hook_token_info().
 */
function improvements_token_info() {
  $info['tokens']['term']['parents-with-current'] = array(
    'name' => t('Parents with current term'),
    'description' => t("An array of all the term's parents with current term, starting with the root."),
    'type' => 'array',
  );

  $info['tokens']['current-user']['host'] = array(
    'name' => t('User host'),
    'description' => t('User host'),
  );

  $info['tokens']['current-user']['user-agent'] = array(
    'name' => t('User agent'),
    'description' => t('User agent'),
  );

  $info['tokens']['url']['with-current-pager'] = array(
    'name' => t('URL with current page number'),
    'description' => t('URL with current page number'),
  );

  return $info;
}

/**
 * Implements hook_tokens().
 */
function improvements_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();

  // Term
  if ($type == 'term' && !empty($data['term'])) {
    $term = $data['term'];

    foreach ($tokens as $name => $original) {
      if ($name == 'parents-with-current') {
        $terms = token_taxonomy_term_load_all_parents($term->tid);
        $terms[] = entity_label('taxonomy_term', $term);
        $replacements[$original] = token_render_array($terms, $options);
      }
    }

    if ($parents_tokens = token_find_with_prefix($tokens, 'parents-with-current')) {
      $terms = token_taxonomy_term_load_all_parents($term->tid);
      $terms[] = entity_label('taxonomy_term', $term);
      $replacements += token_generate('array', $parents_tokens, array('array' => $terms), $options);
    }
  }
  // Current user
  elseif ($type == 'current-user') {
    foreach ($tokens as $name => $original) {
      if ($name == 'host') {
        $replacements[$original] = @gethostbyaddr(ip_address());
      }
      elseif ($name == 'user-agent') {
        $replacements[$original] = @$_SERVER['HTTP_USER_AGENT'];
      }
    }
  }
  // URL
  elseif ($type == 'url') {
    /** @see token_tokens() */
    $url_options = array('absolute' => TRUE);
    if (isset($options['language'])) {
      $url_options['language'] = $options['language'];
    }
    if (isset($data['options'])) {
      $url_options = $data['options'] + $url_options;
    }

    foreach ($tokens as $name => $original) {
      if ($name == 'with-current-pager' && !empty($data['path'])) {
        if ($page = pager_find_page()) {
          $url_options['query']['page'] = $page;
        }
        $replacements[$original] = url($data['path'], $url_options);
      }
    }
  }

  return $replacements;
}
