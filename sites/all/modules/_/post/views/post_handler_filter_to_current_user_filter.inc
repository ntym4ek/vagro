<?php

/**
 * Posts to current user ок not only filter handler
 */
class post_handler_filter_to_current_user_filter extends views_handler_filter_boolean_operator {

  /**
   * {@inheritdoc}
   */
  public function construct() {
    parent::construct();
    $this->value_value = t('Post sent to current user');
  }

  /**
   * {@inheritdoc}
   */
  public function query() {
    $uid = $GLOBALS['user']->uid;

    $this->ensure_my_table();
    $where = "$this->table_alias.recid ";
    if (empty($this->value)) {
      $where .= "= $uid";
    }
    else {
      $where .= "<> $uid";
    }
    $this->query->add_where_expression($this->options['group'], "{$this->table_alias}.rectype = 'user'");
    $this->query->add_where_expression($this->options['group'], $where);
  }
}