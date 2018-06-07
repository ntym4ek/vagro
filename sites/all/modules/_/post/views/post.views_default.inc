<?php

/**
 * Implements hook_views_default_views().
 *
 * Views поставляемые с модулем
 */
function post_views_default_views() {
  $view = new view();
  $view->name = 'stream_profile';
  $view->description = 'Все Записи, адресованные Пользователю';
  $view->tag = 'stream';
  $view->base_table = 'post';
  $view->human_name = 'Лента в профиле';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Сбросить';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'entity';
  /* Поле: Post: Post ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'post';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  /* Sort criterion: Post: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'post';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Post: Recid */
  $handler->display->display_options['arguments']['recid']['id'] = 'recid';
  $handler->display->display_options['arguments']['recid']['table'] = 'post';
  $handler->display->display_options['arguments']['recid']['field'] = 'recid';
  $handler->display->display_options['arguments']['recid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['recid']['exception']['title'] = 'Все';
  $handler->display->display_options['arguments']['recid']['default_argument_type'] = 'user';
  $handler->display->display_options['arguments']['recid']['default_argument_options']['user'] = FALSE;
  $handler->display->display_options['arguments']['recid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['recid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['recid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Post: Rectype */
  $handler->display->display_options['arguments']['rectype']['id'] = 'rectype';
  $handler->display->display_options['arguments']['rectype']['table'] = 'post';
  $handler->display->display_options['arguments']['rectype']['field'] = 'rectype';
  $handler->display->display_options['arguments']['rectype']['default_action'] = 'default';
  $handler->display->display_options['arguments']['rectype']['exception']['title'] = 'Все';
  $handler->display->display_options['arguments']['rectype']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['rectype']['default_argument_options']['argument'] = 'user';
  $handler->display->display_options['arguments']['rectype']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['rectype']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['rectype']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['rectype']['limit'] = '0';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $translatables['stream_profile'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Сбросить'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Post ID'),
    t('.'),
    t(','),
    t('Все'),
    t('Block'),
  );

  $views[$view->name] = $view;

  /**
   * --
   */
  $view = new view();
  $view->name = 'stream';
  $view->description = 'Записи друзей кроме адресованных текущему пользователю (выводятся в личной ленте)';
  $view->tag = 'stream';
  $view->base_table = 'post';
  $view->human_name = 'Лента';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Сбросить';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'entity';
  /* Поле: Post: Post ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'post';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  /* Sort criterion: Post: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'post';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Собственная: Post sent to current user */
  $handler->display->display_options['filters']['to_current_user_filter']['id'] = 'to_current_user_filter';
  $handler->display->display_options['filters']['to_current_user_filter']['table'] = 'post';
  $handler->display->display_options['filters']['to_current_user_filter']['field'] = 'to_current_user_filter';
  $handler->display->display_options['filters']['to_current_user_filter']['value'] = '';
  /* Filter criterion: Собственная: Only from friends */
  $handler->display->display_options['filters']['from_friends_filter']['id'] = 'from_friends_filter';
  $handler->display->display_options['filters']['from_friends_filter']['table'] = 'post';
  $handler->display->display_options['filters']['from_friends_filter']['field'] = 'from_friends_filter';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $translatables['stream'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Сбросить'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Post ID'),
    t('.'),
    t(','),
    t('Block'),
  );

  $views[$view->name] = $view;

  return $views;
}