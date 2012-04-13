<?php
/**
 * @file
 * Salesforce search admin include file.
 *
 * Admin functions for Salesforce search module.
 */
 
function sf_search_display_fields_form($object) {
  
}

/**
 * Settings form for Salesforce search.
 */
function sf_search_settings_form() {
  $contact_fields = _sf_search_contact_lookup_fields();
  
  $form['sf_search_donor_id_field'] = array(
    '#type' => 'select',
    '#title' => t('Donor ID field'),
    '#description' => t('The contact field that will be used when performing a lookup. This field should be configured as an external id in Salesforce.'),
    '#options' => $contact_fields,
    '#default_value' => variable_get('sf_search_donor_id_field', ''),
  );
  
  $form['sf_search_result'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search result display fields'),
    '#collapsible' => TRUE,
  );
  
  $form['sf_search_result']['sf_search_result_display_fields'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Fields to display'),
    '#options' => _sf_search_filter_mapped_fields(),
    '#default_value' => variable_get('sf_search_result_display_fields', array()),
  );

  // add a validation handler so we can lookup the data type of the choosen field  
  $form['#validate'][] = 'sf_search_settings_form_validate';
  
  return system_settings_form($form);
}

/**
 * Validation handler for sf_search settings form.
 */
function sf_search_settings_form_validate(&$form, $form_state) {
  $lookup_field = $form_state['values']['sf_search_donor_id_field'];
  
  // save data type so we can correctly construct soql query later
  if ($type = _sf_search_lookup_field_type($lookup_field)) {
    variable_set('sf_search_donor_id_field_type', $type);
  }
}

/**
 * Returns a subset of all contact fields based on fieldmap.
 */
function _sf_search_filter_mapped_fields() {
  $all_fields = _sf_search_contact_fields();
  $mapped_fields = _sf_search_fieldmap_field_list();
  $fields = array();

  foreach ($all_fields as $key => $field) {
    if (in_array($key, $mapped_fields)) {
      $fields[$key] = $field['label'];
    }
  }
 
  asort($fields);
  return $fields; 
}

/**
 * Returns all fields in the contact object.
 */
function _sf_search_contact_fields() {
  // get salesforce object definitions
  $objects = salesforce_management_api_fieldmap_objects('salesforce');
  if (!empty($objects) && array_key_exists('Contact', $objects)) {
    return $objects['Contact']['fields'];
  }  
  
  return FALSE;
}

/**
 * Returns an array of unique id fields on the contact object.
 */
function _sf_search_contact_lookup_fields() {
  $fields = array();

  // loop over all fields in the contact object and pick out the unique id fields
  $contact_fields = _sf_search_contact_fields();
  foreach ($contact_fields as $key => $field) {
    if ($field['unique']) {
      $fields[$key] = $field['label'];
    }    
  }
  
  return $fields;
}

/**
 * Returns the datatype of a given contact field.
 *
 * @param $field_id
 *   The id of the fields whose type to return.
 */
function _sf_search_lookup_field_type($field_id) {
  $fields = _sf_search_contact_fields();
  foreach ($fields as $key => $field) {
    if ($key == $field_id) {
      return $field['field_type'];
    }    
  }
  
  return FALSE;
}