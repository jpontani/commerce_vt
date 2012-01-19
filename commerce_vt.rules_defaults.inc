<?php
/**
 * @file
 * Commerce VT default rules file.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_vt_default_rules_configuration() {
  $rules = array();

  $rule = rules_import('{ "rules_registration_refund" : {
      "LABEL" : "Mark registration as refunded and increase product stock.",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "commerce_vt", "rules" ],
      "USES VARIABLES" : { "registration" : { "label" : "Registration", "type" : "registration" } },
      "ACTION SET" : [
        { "commerce_vt_cancel_registrations" : { "registration_id" : [ "registration" ] } },
        { "commerce_vt_increase_stock" : { "registration" : [ "registration" ] } },
        { "drupal_message" : {
            "message" : "The registration was marked as refunded, and the stock level was increased.",
            "type" : "warning"
          }
        }
      ]
    }
  }');
  $rules['rules_registration_refund'] = $rule;

  return $rules;
}

function commerce_vt_default_rules_configuration_alter(&$configs) {
  $configs['commerce_payment_commerce_vt_refund']->condition('data_is', array('data:select' => 'site:name', 'value' => 'This should never be the site name.'));
  if (module_exists('commerce_pip')) {
    $configs['commerce_payment_commerce_check']->condition('data_is', array('data:select' => 'site:name', 'value' => 'This should never be the site name.'));
    $configs['commerce_payment_commerce_cash']->condition('data_is', array('data:select' => 'site:name', 'value' => 'This should never be the site name.'));
    $configs['commerce_payment_commerce_card']->condition('data_is', array('data:select' => 'site:name', 'value' => 'This should never be the site name.'));
  }
}