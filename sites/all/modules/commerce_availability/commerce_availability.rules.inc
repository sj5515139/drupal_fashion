<?php
/**
 * @file
 * Commerce Availability rules.
 */

/**
 * Implements hook_rules_action_info().

 * @link http://drupalcontrib.org/api/drupal/contributions!rules!rules.api.
 * php/function/hook_rules_action_info/7
 */
function commerce_availability_rules_action_info() {
  $actions = array();
  $actions['commerce_availability_clean_blocked'] = array(
    'label' => t('Clean blocked days on availability'),
    'parameter' => array(
      'interval' => array(
        'type' => 'duration',
        'label' => t('Cart expiration interval'),
        'description' => t('Time span until shopping carts are considered expired.'),
        'default value' => 1800,
      ),
      'limit' => array(
        'type' => 'integer',
        'label' => t('Number of shopping carts to process'),
        'description' => t('Number of shopping carts to process at a time. Useful for sites having a considerable amount of orders. Set to 0 for unlimited.'),
        'default value' => 0,
      ),
    ),
    'group' => t('Commerce Cart'),
    'callbacks' => array(
      'execute' => 'commerce_availability_commerce_cart_clean',
    ),
  );
  return $actions;
}

/**
 * Implements hook_rules_action_info().
 *
 * @link http://drupalcontrib.org/api/drupal/contributions!rules!rules.api.
 * php/function/hook_rules_action_info/7
 */
function commerce_availability_commerce_cart_clean($interval = 0, $limit = 0) {
  if ($interval > 0) {
    $expired_order_ids = commerce_cart_expiration_get_expired_carts($interval, $limit);
    if (!empty($expired_order_ids)) {
      $expired_orders = commerce_order_load_multiple($expired_order_ids);
      foreach ($expired_orders as $order) {
        commerce_availability_update_states_order($order, COMMERCE_AVAILABILITY_S_CAL_AV);
      }
    }
  }
}
