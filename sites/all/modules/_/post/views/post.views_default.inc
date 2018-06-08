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
  $handler->display->display_options['filter_groups']['operator'] = 'OR';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'AND',
  );
  /* Filter criterion: Собственная: Post sent by current user */
  $handler->display->display_options['filters']['from_current_user_filter']['id'] = 'from_current_user_filter';
  $handler->display->display_options['filters']['from_current_user_filter']['table'] = 'post';
  $handler->display->display_options['filters']['from_current_user_filter']['field'] = 'from_current_user_filter';
  $handler->display->display_options['filters']['from_current_user_filter']['value'] = '1';
  $handler->display->display_options['filters']['from_current_user_filter']['group'] = 1;
  /* Filter criterion: Post: Recid */
  $handler->display->display_options['filters']['recid']['id'] = 'recid';
  $handler->display->display_options['filters']['recid']['table'] = 'post';
  $handler->display->display_options['filters']['recid']['field'] = 'recid';
  $handler->display->display_options['filters']['recid']['value']['value'] = '0';
  $handler->display->display_options['filters']['recid']['group'] = 1;
  /* Filter criterion: Post: Rectype */
  $handler->display->display_options['filters']['rectype']['id'] = 'rectype';
  $handler->display->display_options['filters']['rectype']['table'] = 'post';
  $handler->display->display_options['filters']['rectype']['field'] = 'rectype';
  $handler->display->display_options['filters']['rectype']['group'] = 1;
  /* Filter criterion: Собственная: Post sent to current user */
  $handler->display->display_options['filters']['to_current_user_filter']['id'] = 'to_current_user_filter';
  $handler->display->display_options['filters']['to_current_user_filter']['table'] = 'post';
  $handler->display->display_options['filters']['to_current_user_filter']['field'] = 'to_current_user_filter';
  $handler->display->display_options['filters']['to_current_user_filter']['value'] = '1';
  $handler->display->display_options['filters']['to_current_user_filter']['group'] = 2;

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
    t('Block'),
  );


  $views[$view->name] = $view;

  /**
   * --
   */
  $view = new view();
  $view->name = 'stream';
  $view->description = 'Записи друзей и записи адресованные текущему пользователю';
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
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'OR',
  );
  /* Filter criterion: Собственная: Post sent to current user */
  $handler->display->display_options['filters']['to_current_user_filter']['id'] = 'to_current_user_filter';
  $handler->display->display_options['filters']['to_current_user_filter']['table'] = 'post';
  $handler->display->display_options['filters']['to_current_user_filter']['field'] = 'to_current_user_filter';
  $handler->display->display_options['filters']['to_current_user_filter']['value'] = '1';
  $handler->display->display_options['filters']['to_current_user_filter']['group'] = 1;
  /* Filter criterion: Собственная: Only from friends */
  $handler->display->display_options['filters']['from_friends_filter']['id'] = 'from_friends_filter';
  $handler->display->display_options['filters']['from_friends_filter']['table'] = 'post';
  $handler->display->display_options['filters']['from_friends_filter']['field'] = 'from_friends_filter';
  $handler->display->display_options['filters']['from_friends_filter']['group'] = 1;

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

  /**
   * --
   */
  $view = new view();
  $view->name = 'stream_search';
  $view->description = 'Поиск по всем Записям (кроме адресованных конкретным пользователям)';
  $view->tag = 'stream';
  $view->base_table = 'search_api_index_post_index';
  $view->human_name = 'Поиск в ленте';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Posts search';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Сбросить';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entity';
  /* Поле: Indexed Post: Post ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'search_api_index_post_index';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  /* Filter criterion: Поиск: Fulltext search */
  $handler->display->display_options['filters']['search_api_views_fulltext']['id'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['table'] = 'search_api_index_post_index';
  $handler->display->display_options['filters']['search_api_views_fulltext']['field'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['operator'] = 'OR';
  $handler->display->display_options['filters']['search_api_views_fulltext']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator_id'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['identifier'] = 's';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    3 => 0,
  );
  /* Filter criterion: Indexed Post: Recid */
  $handler->display->display_options['filters']['recid']['id'] = 'recid';
  $handler->display->display_options['filters']['recid']['table'] = 'search_api_index_post_index';
  $handler->display->display_options['filters']['recid']['field'] = 'recid';
  $handler->display->display_options['filters']['recid']['value'] = '0';
  /* Filter criterion: Indexed Post: Rectype */
  $handler->display->display_options['filters']['rectype']['id'] = 'rectype';
  $handler->display->display_options['filters']['rectype']['table'] = 'search_api_index_post_index';
  $handler->display->display_options['filters']['rectype']['field'] = 'rectype';

  /* Display: Страница */
  $handler = $view->new_display('page', 'Страница', 'page_1');
  $handler->display->display_options['path'] = 'stream/search';
  $translatables['posts_search'] = array(
    t('Master'),
    t('Posts search'),
    t('more'),
    t('Apply'),
    t('Сбросить'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Post ID'),
    t('.'),
    t(','),
    t('Страница'),
  );

  $views[$view->name] = $view;

  return $views;
}