<?php
/**
 * @file
 * Salesforce search forms.
 *
 * Creates the lookup and search forms required by the Salesforce search module.
 */
 
/**
 * Creates a form to find a contact by donor id.
 */
function sf_search_lookup_form() {
  // donor id field
  $form['sf_search_donor_id'] = array(
    '#type' => 'textfield',
    '#title' => 'Donor Id',
  );
  
  $form['sf_search_lookup_form_submit'] = array(
    '#type' => 'submit',
    '#value' => 'Find',
  );
  
  return $form;
}

function sf_search_lookup_form_submit($form, &$form_state) {
  dsm('lookup form submitted');
}

/**
 * Creates a form to perform a full text search.
 */
function sf_search_search_form() {
  // create a full text query field
  $form['sf_search_query'] = array(
    '#type' => 'textfield',
    '#title' => 'What are you looking for',
  );
  
  $form['sf_search_search_form_submit'] = array(
    '#type' => 'submit',
    '#value' => 'Search',
  );
  
  return $form;
}