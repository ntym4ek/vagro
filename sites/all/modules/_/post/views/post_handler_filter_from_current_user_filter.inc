<?php

/**
 * Posts to current user ок not only filter handler
 */
class post_handler_filter_from_current_user_filter extends views_handler_filter_boolean_operator {

  /**
   * {@inheritdoc}
   */
  public function construct() {
    parent::construct();
    $this->value_value = t('Post sent by current user');
  }

  /**
   * {@inheritdoc}
   */
  public function query() {
    $uid = $GLOBALS['user']->uid;

    $this->ensure_my_table();
    $where = "$this->table_alias.senid ";
    if (empty($this->value)) {
      $where .= "<> $uid";
    }
    else {
      $where .= "= $uid";
    }
    $this->query->add_where_expression($this->options['group'], "{$this->table_alias}.sentype = 'user'");
    $this->query->add_where_expression($this->options['group'], $where);
  }
}