<?php
/**
 * @file
 * Secure prepopulate admin functions
 */

/**
 * System settings form for secure prepopulate.
 */
function secure_prepopulate_admin_settings(&$form_state) {
  $form = array();
  $key = variable_get('secure_prepopulate_key', '') ? decrypt(variable_get('secure_prepopulate_key', '')) : '';
  $vector = variable_get('secure_prepopulate_iv', '') ? decrypt(variable_get('secure_prepopulate_iv', '')) : '';
  $form['secure_prepopulate_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Encryption key'),
    '#description' => t('To use 128 bit encryption enter a 16 byte (128 bit) AES key. 256 bit encryption requires a 32 byte key (256 bits).'),
    '#default_value' => $key,
  );

  $form['secure_prepopulate_iv'] = array(
    '#type' => 'textfield',
    '#title' => t('Initialization vector'),
    '#description' => t('A 16 byte initialization vector. The initialization vector (IV) is a fixed-size input to a cryptographic primitive that is typically required to be random or pseudorandom.'),
    '#default_value' => $vector,
  );

  $form['secure_prepopulate_precedence'] = array(
    '#type' => 'radios',
    '#title' => t('Pre-populate precedence'),
    '#description' => t('Determines which set of values take precedence when the user is already logged in.'),
    '#options' => array('url' => 'Encrypted URL values', 'drupal' => 'Drupal values'),
    '#default_value' => variable_get('secure_prepopulate_precedence', 'url'),
  );

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#name' => t('Advanced settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['advanced']['secure_prepopulate_additional_forms'] = array(
    '#type' => 'textarea',
    '#title' => t('Additional prepopulate forms'),
    '#description' => t('Add additional form id to prepopulate values. One per line.'),
    '#value' => variable_get('secure_prepopulate_additional_forms', ''),
  );

  return system_settings_form($form); 
}

/**
 * Settings validation routine.
 */
function secure_prepopulate_admin_settings_validate(&$form, &$form_state) {
  if (mb_strlen($form_state['values']['secure_prepopulate_key']) != 32 && mb_strlen($form_state['values']['secure_prepopulate_key']) != 16) {
    form_set_error('secure_prepopulate_key', 'Key must be either 128 bits (16 bytes) or 256 bits (32 bytes) in length.');
  }
  else {
    $form_state['values']['secure_prepopulate_key'] = encrypt($form_state['values']['secure_prepopulate_key']);
  }
  
  if (mb_strlen($form_state['values']['secure_prepopulate_iv']) != 16) {
    form_set_error('secure_prepopulate_iv', 'Initialization vector must be either 128 bits (16 bytes) in length.');
  }
  else {
    $form_state['values']['secure_prepopulate_iv'] = encrypt($form_state['values']['secure_prepopulate_iv']);
  }
}