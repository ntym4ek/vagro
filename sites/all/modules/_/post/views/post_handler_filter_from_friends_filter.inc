<?php

/**
 * Posts from friends only filter handler
 *
 */
class post_handler_filter_from_friends_filter extends views_handler_filter {

  function query() {
    $this->operator = '';
    $this->ensure_my_table();

    // получить список ID друзей пользователя
    $uid = $GLOBALS['user']->uid;
    $friends = flag_friend_get_friends_query($uid);
    $friends_string = implode(',', $friends);
    $type = 'user';

    // добавить условие
    // посты должны быть от пользователей (тип user) из этого списка
    $this->query->add_where_expression($this->options['group'], "{$this->table_alias}.sentype = '" . $type . "'");
    $this->query->add_where_expression($this->options['group'], "{$this->table_alias}.senid IN(" . $friends_string . ")");
  }
}