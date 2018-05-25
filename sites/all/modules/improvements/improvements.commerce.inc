<?php

/**
 * Remove outdated orders.
 */
function improvements_delete_outdated_orders() {
  $order_ids = db_select('commerce_order', 'o')
    ->fields('o', array('order_id'))
    ->condition('o.uid', 0)
    ->condition('o.status', array('cart', 'checkout_checkout'))
    ->condition('o.changed', REQUEST_TIME - max(ini_get('session.gc_maxlifetime'), 86400), '<')
    ->range(0, 100)
    ->execute()
    ->fetchCol();

  if ($order_ids) {
    commerce_order_delete_multiple($order_ids);
    watchdog('improvements', 'Удалено ' . count($order_ids) . ' незавершённых анонимных заказов', NULL);
  }
}

/**
 * Implements hook_form_BASE_FORM_ID_alter(): commerce_checkout_form.
 */
function improvements_form_commerce_checkout_form_alter(&$form, &$form_state) {
  // Change payment methods to their rule name
  if (isset($form['commerce_payment'])) {
    foreach ($form['commerce_payment']['payment_method']['#options'] as $payment_method_instance_id => &$payment_method_display_title) {
      $payment_method_display_title = CommerceHelper::getPaymentMethodTitle($payment_method_instance_id);
    }
  }

  // Hide text "Or" between buttons
  if (isset($form['buttons']['cancel'])) {
    $form['buttons']['cancel']['#prefix'] = '';
  }

  // Remove commerce_checkout.js script
  if (isset($form['#attached']['js'])) {
    $form['#attached']['js'] = array_diff($form['#attached']['js'], array(drupal_get_path('module', 'commerce_checkout') . '/commerce_checkout.js'));
  }
}

/**
 * Implements hook_form_FORM_ID_alter(): views_form_commerce_cart_form_default.
 */
function improvements_form_views_form_commerce_cart_form_default_alter(&$form, &$form_state) {
  if ($GLOBALS['user']->uid == 1) {
    $form['actions']['clear'] = array(
      '#type' => 'submit',
      '#value' => t('Clear cart'),
      '#submit' => array('improvements_clear_cart'),
    );
  }
}

/**
 * Clear current user cart.
 */
function improvements_clear_cart() {
  if ($order = commerce_cart_order_load($GLOBALS['user']->uid)) {
    commerce_cart_order_empty($order);
  }
}
