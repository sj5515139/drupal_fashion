<?php
/**
 * @file
 * Add action to rule 'commerce_cart_expiration_delete_expired_carts'.
 */

/**
 * Implements hook_default_rules_configuration_alter().
 *
 * @link http://drupalcontrib.org/api/drupal/contributions!rules!rules.api.
 * php/function/hook_default_rules_configuration_alter/7
 */
function commerce_availability_default_rules_configuration_alter(&$configs) {
  $rule = $configs['commerce_cart_expiration_delete_expired_carts'];
  if (!empty($rule)) {
    $rule->active = TRUE;
    $rule->action('commerce_availability_clean_blocked', array(
      'interval' => 1800,
       'limit' => 0,
    ));
  }
  return $configs;
}
