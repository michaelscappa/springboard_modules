<?php
 
/**
 * @file 
 * Include file for the admin configuration UI
 */

/**
 * Admin settings form.
 */
function springboard_social_admin_settings() {
  $form = array();
  $form['springboard_social_app_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Facebook App ID'),
    '#description' => t('A Facebook app ID is required for share links to work.'),
    '#default_value' => variable_get('springboard_social_app_id', ''),
  );
  $form['springboard_social_logo'] = array(
    '#type' => 'textfield',
    '#title' => t('Default logo'),
    '#description' => t('URL of the logo file to use on share popups.'),
    '#default_value' => variable_get('springboard_social_logo', ''),
  );
  $form['springboard_social_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Default title'),
    '#description' => t(''),
    '#default_value' => variable_get('springboard_social_title', ''),
  );
  $form['springboard_social_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Default message'),
    '#description' => t(''),
    '#default_value' => variable_get('springboard_social_message', ''),
  );
  $form['springboard_social_description'] = array(
    '#type' => 'textfield',
    '#title' => t('Default description'),
    '#description' => t(''),
    '#default_value' => variable_get('springboard_social_description', ''),
  );
  return system_settings_form($form);
}