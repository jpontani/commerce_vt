<?php
/**
 * @file
 *  Commerce VT Refund payment method callbacks.
 */

function commerce_vt_refund_submit_form($payment_method, $pane_values, $checkout_pane, $order) {
  $form = array();

  $form['refund_description'] = array(
    '#type' => 'textarea',
    '#title' => t('Reason for Refund'),
  );

  return $form;
}

function commerce_vt_refund_submit_form_submit($payment_method, $pane_form, $pane_values, $order, $charge) {
  $trans = commerce_payment_transaction_new('commerce_vt_refund', $order->order_id);
  $trans->currency_code = $charge['currency_code'];
  $trans->amount = $charge['amount'];
  $trans->status = COMMERCE_PAYMENT_STATUS_SUCCESS;
  $trans->message = "<strong>Reason for Refund:</strong> @reason";
  $trans->message_variables['@reason'] = $pane_values['refund_description'];
  commerce_payment_transaction_save($trans);
  commerce_order_status_update($order, 'refund_completed');
}