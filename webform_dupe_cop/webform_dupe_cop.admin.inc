<?php
/**
 * @file
 * Administration page callbacks for the webform_dupe_cop module.
 */

/**
 * Admin settings form.
 */
function webform_dupe_cop_settings_form() {
  $form['webform_dupe_cop_timespan'] = array(
    '#type' => 'textfield',
    '#title' => t('Time span'),
    '#default_value' => variable_get('webform_dupe_cop_timespan', '1 hour'),
    '#description' => t('Each webform submission will be protected from duplicates for this period after the time when it was ' .
      'first submitted. Use the string format as given in the documentation for %url. Set to 0 for no time span limits.',
      array('%url' => l('strtotime()', 'http://php.net/manual/en/datetime.formats.relative.php'))),
  );
  $form['webform_dupe_cop_toggle'] = array(
    '#type' => 'checkbox',
    '#title' => t('Intercept submission'),
    '#default_value' => variable_get('webform_dupe_cop_toggle', 'TRUE'),
    '#description' => t('Toggle interception of duplicated forms. Uncheck this to just log the incident.'),
  );  
  $form['webform_dupe_cop_message'] = array(
    '#type' => 'textarea',
    '#rows' => 3,
    '#title' => t('Message'),
    '#default_value' => variable_get('webform_dupe_cop_message', '%date %time - Dupe detected at %webform_id by %user_id matches ' .
      'a submission submitted at %prev_date %prev_time.'),
    '#description' => t('Optional. Message  to display on dupe submission. You can use %date, %time, %webform_id, %user_id to substitute ' .
      'the date and time of the original submission.'),
  );
	$form['#validate'][] = 'webform_dupe_cop_settings_form_validate';
	return system_settings_form($form);
}

/**
 * Validate handler for admin form.
 */
function webform_dupe_cop_settings_form_validate($form, &$form_settings) {
  if (!strtotime($form_settings['values']['webform_dupe_cop_timespan'])) {
    form_set_error('webform_dupe_cop_timespan', t('Time span must be a valid textual datetime description.'));
  }
}
