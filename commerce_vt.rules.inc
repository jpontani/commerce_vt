<?php
/**
 * @file
 *  Commerce VT rules events, conditions and actions.
 */

function commerce_vt_rules_action_info() {
  $actions['commerce_vt_cancel_registrations'] = array(
    'label' => t('Mark Registration as cancelled.'),
    'group' => t('Commerce Registration'),
    'parameter' => array(
      'registration_id' => array(
        'type' => 'registration',
        'label' => t('Registration'),
        'description' => t('The registration to mark as cancelled.'),
      ),
    ),
    'callbacks' => array(
      'execute' => 'commerce_vt_mark_cancelled',
    ),
  );

  $actions['commerce_vt_increase_stock'] = array(
    'label' => t('Increase product stock, given a registration.'),
    'group' => t('Commerce Registration'),
    'parameter' => array(
      'registration' => array(
        'type' => 'registration',
        'label' => t('Registration'),
        'description' => t('The registration whose product stock should be increased.'),
      ),
    ),
    'callbacks' => array(
      'execute' => 'commerce_vt_increase_stock',
    ),
  );
	return $actions;
}

/**
 * Mark the registration as cancelled.
 */
function commerce_vt_mark_cancelled($registration) {
  $registration->status = "refund";
  registration_save($registration);
}

/**
 * Increase a registration's product stock level by one.
 */
function commerce_vt_increase_stock($registration) {
  if (!function_exists('commerce_stock_adjust')) {
    module_load_include('inc', 'commerce_stock', 'commerce_stock.rules');
  }
  $product = commerce_product_load($registration->eid);
  commerce_stock_adjust($product, 1);
}