// global variable to store all sf_search related items
var sfSearch = {};
sfSearch.contacts = []; // initialize empty contacts array

Drupal.behaviors.SfSearchSetup = function(context) {

  $('#sf-search-search-form').submit(function() {
    var query = $('#edit-sf-search-query').val();
    var nid = $('#edit-nid').val();
    var fid = $('#edit-fid').val();
    
    // hide any current search results
    $('#search-results').slideUp('fast');
    
    // search contacts
    contactSearch(query, nid, fid);
 
    return false;
  });

  $('#sf-search-lookup-form').submit(function() {
    var donor_id = $('#edit-sf-search-donor-id').val();
    var nid = $('#edit-nid').val();
    var fid = $('#edit-fid').val();
    
    // hide any current search results
    $('#search-results').slideUp('fast');
    
    // lookup the contact
    contactLookup(donor_id, nid, fid);
 
    return false;
  });
  
  /* throbbers */
  $("#sf-search-lookup-loading").bind("ajaxStart", function(){
    $(this).show();
  });
  
  $("#sf-search-lookup-loading").bind("ajaxStop", function(){
    $(this).hide();
  });
  
};

/**
 * Extract the contact when it's id is clicked.
 */
$("#sf-contacts tbody tr a.donor-id").live('click',function(){
    var position = $('#sf-contacts').dataTable().fnGetPosition(this.parentNode);
    var contact = $('#sf-contacts').dataTable().fnGetData(position[0]);
    $('#search-results').slideUp('fast');
    populateContactInfo(contact);
});

/**
 * Use the display columns setting to build a data structure that data tables
 * can use to display the contacts.
 */
function getColumnDefinitions() {
  var columns = [];
  for (var propName in Drupal.settings.sf_search.display_columns) {
    var column = {};
    column.sTitle = Drupal.settings.sf_search.display_columns[propName];
    column.mDataProp = propName;
    
    if (propName == Drupal.settings.sf_search.donor_id_field) {
      // add a render function
      column.fnRender = function(obj) {
        var columnValue = '<a class="donor-id">' + obj.aData[Drupal.settings.sf_search.donor_id_field] + '</a>';
        return columnValue;
      };
    }
    columns.push(column);
  }
  
  return columns;
}

/**
 * Displays the results of a search query.
 */
function displayResults(data) {
  if (data.length == 1) {
    // single contact, go ahead and populate form
    populateContactInfo(data[0]);
  }
  else if (data.length > 1) {
    // multiple contacts, return some formatted html for selecting a contact
    $('#search-results').html('<table cellpadding="0" cellspacing="0" border="0" class="display" id="sf-contacts"></table>');
            
    // save data for later
    sfSearch.contacts = data;
    
    // get a data tables friendly version of the column data
    columns = getColumnDefinitions();
    
    // create a data table on the fly filled with the returned contacts
    contactTable = $('#sf-contacts').dataTable( {
      "aaData": sfSearch.contacts,
      "aoColumns": columns
    });
    
    // display the results
    $('#search-results').slideDown('fast');
  }
  else {
    $('#search-results').html('<em>No contacts found.</em>').show().fadeOut(3000);
  }
}

/**
 * Performs a contact lookup by donor id.
 */
function contactLookup(donor_id, nid, fid) {
  var url = '/js/salesforce-search/lookup/' + nid + '/' + donor_id;
  $.getJSON(url, function(data) {
    displayResults(data);
  });
}

/**
 * Performs a full-text contact search.
 */
function contactSearch(query, nid, fid) {
  var url = '/js/salesforce-search/find/' + nid + '/' + query;
  $.getJSON(url, function(data) {
    displayResults(data);
  });
}

/**
 * Takes a contact object and uses a client-side fieldmap to populate a form.
 */
function populateContactInfo(contact) {
  var fieldMap = Drupal.settings.sf_search.field_map;
  for (var field in fieldMap) {
    var inputId = '#' + fieldMap[field];
    
    // there has to be a better solution for these state/country conversions
    if (field == 'MailingState') {
      contact[field] = Drupal.settings.sf_search.zones[contact[field]];
    }
    
    if (field == 'MailingCountry') {
      contact[field] = Drupal.settings.sf_search.countries[contact[field]];
    }
    
    
    $(inputId).val(contact[field]).effect('highlight', {}, 2000);
  }
}