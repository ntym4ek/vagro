<?php

/**
 * Implements hook_admin_menu_output_build().
 */
function improvements_admin_menu_output_build(&$content) {
  if (module_exists('backup_migrate')) {
    $content['icon']['icon']['backup'] = array(
      '#title' => 'Сделать бэкап',
      '#weight' => 51,
      '#access' => user_access('perform backup'),
      '#href' => 'admin/config/system/backup_migrate/run',
    );
  }
  if (module_exists('devel')) {
    $content['icon']['icon']['php'] = array(
      '#title' => 'Выполнить PHP',
      '#weight' => 52,
      '#access' => user_access('execute php code'),
      '#href' => 'devel/php',
    );
  }
}

/**
 * Implements hook_admin_menu_output_alter().
 */
function improvements_admin_menu_output_alter(&$content) {
  $content['menu']['admin/index']['#access'] = FALSE;
  $content['icon']['icon']['drupal.org']['#access'] = FALSE;
}

/**
 * Implements hook_form_FORM_ID_alter(): dblog_clear_log_form
 */
function improvements_form_dblog_clear_log_form_alter(&$form, &$form_state) {
  $form['dblog_clear']['#type'] = 'container';
}

/**
 * Implements hook_form_FORM_ID_alter(): system_site_information_settings.
 */
function improvements_form_system_site_information_settings_alter(&$form, &$form_state) {
  $form['#submit'][] = 'improvements_form_system_site_information_settings_submit';
}

/**
 * Custom submit for system_site_information_settings() form.
 * @see improvements_form_system_site_information_settings_alter()
 */
function improvements_form_system_site_information_settings_submit($form, &$form_state) {
  if (substr(strrchr($form_state['values']['site_mail'], '@'), 1) != $_SERVER['HTTP_HOST']) {
    drupal_set_message('Домен e-mail адреса отличается от домена сайта, поэтому возможно часть исходящих писем будет попадать в спам. Измените e-mail адрес, либо воспользуйтесь модулем SMTP.', 'warning');
  }
}

/**
 * Preprocess vars for block-admin-display-form.tpl.php.
 */
function improvements_preprocess_block_admin_display_form(&$vars) {
  foreach ($vars['block_listing'] as $region => $blocks) {
    foreach ($blocks as $block_delta => $block) {
      $span = $vars['form']['blocks'][$block_delta]['module']['#value'] . ':' . $vars['form']['blocks'][$block_delta]['delta']['#value'];
      $vars['block_listing'][$region][$block_delta]->block_title .= ' <span style="float:right;">' . $span . '</span> ';
    }
  }
}

/**
 * Implements hook_views_data_alter().
 */
function improvements_views_data_alter(&$data) {
  foreach ($data as $data_key => $data_items) {
    foreach ($data_items as $item_key => $item) {
      if (is_array($item) && isset($item['field']) && isset($item['title'])) {
        $data[$data_key][$item_key]['help'] = isset($item['help']) ? $item['help'] . ' [' . $item_key . ']' : '[' . $item_key . ']';
      }
    }
  }
}

/**
 * Database backup.
 */
function improvements_backup_migrate_run() {
  backup_migrate_include('profiles', 'destinations');
  $settings = _backup_migrate_profile_saved_default_profile('default');
  $settings->destination_id = array('manual');

  _backup_migrate_message_callback('_backup_migrate_message_browser');
  backup_migrate_perform_backup($settings);

  drupal_goto($_SERVER['HTTP_REFERER']);
}

/**
 * Logs redirect.
 */
function improvements_logs_redirect() {
  drupal_goto('admin/reports/dblog');
}

/**
 * Implements hook_requirements().
 */
function improvements_requirements($phase) {
  $requirements = array();

  if ($phase == 'runtime') {
    $t = get_t();
    $zero_user_exists = _improvements_zero_user_exists();

    $requirements['improvements_zero_user'] = array(
      'title' => $t('Zero user'),
      'value' => $zero_user_exists ? $t('Exists') : $t('Does not exist') . ' (' . l($t('restore'), 'admin/config/people/accounts/restore-zero-user') . ')',
      'severity' => $zero_user_exists ? REQUIREMENT_OK : REQUIREMENT_ERROR,
    );
  }

  return $requirements;
}

/**
 * Menu callback. Restore zero user.
 */
function improvements_zero_user_restore() {
  if (!_improvements_zero_user_exists()) {
    db_query("INSERT INTO {users} (name, pass, mail, theme, signature, language, init, timezone) VALUES ('', '', '', '', '', '', '', '')");
    db_query("UPDATE {users} SET uid = 0 WHERE name = ''");

    drupal_set_message(t('Zero user restored'));
  }

  drupal_goto('admin/reports/status');
}

/**
 * Return TRUE if zero user exists.
 */
function _improvements_zero_user_exists() {
  return (bool)db_select('users')->condition('uid', 0)->countQuery()->execute()->fetchField();
}

/**
 * Implements hook_form_FORM_ID_alter(): menu_overview_form.
 */
function improvements_form_menu_overview_form_alter(&$form, &$form_state) {
  // Add link
  foreach (element_children($form) as $key) {
    if (isset($form[$key]['operations'])) {
      $form[$key]['operations']['add'] = array(
        '#type' => 'link',
        '#title' => 'добавить',
        '#href' => 'admin/structure/menu/manage/' . $form[$key]['#item']['menu_name'] . '/add',
        '#options' => array(
          'query' => array(
            'parent' => $form[$key]['mlid']['#value'],
          ),
        ),
        '#weight' => 2,
      );
      $form[$key]['operations']['edit']['#weight'] = 1;
      $form[$key]['operations']['delete']['#weight'] = 3;
      uasort($form[$key]['operations'], 'element_sort');
    }
  }

}

/**
 * Implements hook_form_FORM_ID_alter(): menu_edit_item.
 */
function improvements_form_menu_edit_item_alter(&$form, &$form_state) {
  $form_type = $form_state['build_info']['args'][0];
  $menu_name = $form_state['build_info']['args'][2]['menu_name'];

  // Autofocus
  if (isset($form['link_title']) && empty($form['link_title']['#default_value'])) {
    $form['link_title']['#attributes']['autofocus'] = 'autofocus';
  }

  // Set parent
  if ($form_type == 'add' && !empty($_GET['parent'])) {
    $form['parent']['#default_value'] = $menu_name . ':' . $_GET['parent'];
  }

  // Set weight
  if ($form_type == 'add') {
    $query = db_select('menu_links', 'ml');
    $query->addExpression('MAX(weight)');
    $query->condition('ml.menu_name', $menu_name);
    $query->condition('ml.plid', !empty($_GET['parent']) ? $_GET['parent'] : 0);
    $max_weight = $query->execute()->fetchField();

    if ($max_weight !== NULL) {
      $form['weight']['#default_value'] = $max_weight + 1;
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter(): system_modules.
 */
function improvements_form_system_modules_alter(&$form, &$form_state) {
  if (isset($form['modules'])) {
    foreach (element_children($form['modules']) as $package) {
      foreach (element_children($form['modules'][$package]) as $module_name) {
        if (isset($form['modules'][$package][$module_name]['links']['configure'])) {
          $form['modules'][$package][$module_name]['links'] = array('configure' => $form['modules'][$package][$module_name]['links']['configure']) + $form['modules'][$package][$module_name]['links'];
        }
      }
    }
  }
}
