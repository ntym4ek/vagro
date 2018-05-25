<?php

/**
 * Implements hook_filter_info().
 */
function improvements_filter_info() {
  return array(
    'url_language_prefix' => array(
      'title' => t('Add language prefix to URLs'),
      'process callback' => 'improvements_url_language_prefix_filter_process',
    ),
  );
}

/**
 * Filter process callback.
 */
function improvements_url_language_prefix_filter_process($text, $filter, $format, $langcode, $cache, $cache_id) {
  return preg_replace_callback('/<a[^>]href="(.*?)"/is', function ($matches) {
    $input = $matches[0];
    $url = $matches[1];
    if (strpos($url, '/') === 0) {
      $new_url = url(drupal_substr($url, 1));
      $input = str_replace($url, $new_url, $input);
    }
    return $input;
  }, $text);
}
