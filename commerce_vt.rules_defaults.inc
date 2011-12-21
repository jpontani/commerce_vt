<?php
/**
 * @file
 * Commerce VT default rules file.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_vt_default_rules_configuration() {
  $rule = rules_reaction_rule();
  $rule->label = "Refund";
  $rule->active = TRUE;
  $rule->event('commerce_payment_methods')
    ->condition('data_is', array('data' => 'site:name', 'value' => 'This should never be the site name.'))
    ->action('commerce_payment_enable_commerce_vt_refund', array('commerce_order' => 'commerce-order', 'payment_method' => 'commerce_vt_refund'));
  
  $rules['commerce_payment_commerce_vt_refund'] = $rule;
}

function commerce_vt_default_rules_configuration_alter(&$configs) {
  $configs['commerce_payment_commerce_vt_refund']->condition('data_is', array('data:select' => 'site:name', 'value' => 'This should never be the site name.'));
  if (module_exists('commerce_pip')) {
    $configs['commerce_payment_commerce_check']->condition('data_is', array('data:select' => 'site:name', 'value' => 'This should never be the site name.'));
    $configs['commerce_payment_commerce_cash']->condition('data_is', array('data:select' => 'site:name', 'value' => 'This should never be the site name.'));
    $configs['commerce_payment_commerce_card']->condition('data_is', array('data:select' => 'site:name', 'value' => 'This should never be the site name.'));
  }
}