// global variable to store all sf_search related items
var sfSearch = {};
sfSearch.contacts = []; // initialize empty contacts array

Drupal.behaviors.SfSearchSetup = function(context) {

  $('#sf-search-lookup-form').submit(function() {
    var donor_id = $('#edit-sf-search-donor-id').val();
    var nid = $('#edit-nid').val();
    var fid = $('#edit-fid').val();

    var url = '/js/salesforce-search/lookup/' + nid + '/' + fid + '/' + donor_id;

    // make an ajax request to the endpoint
    $.getJSON(url, function(data) {
      // check how much data we got back
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
      }
      else {
        // TODO: Add something to indicate no contacts where found
      }
    });

    return false;
    
  });
};

/**
 * Extract the contact when it's id is clicked.
 */
$("#sf-contacts tbody tr a.donor-id").live('click',function(){
    var position = $('#sf-contacts').dataTable().fnGetPosition(this.parentNode);
    var contact = $('#sf-contacts').dataTable().fnGetData(position[0]);
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
 * Takes a contact object and uses a client-side fieldmap to populate a form.
 */
function populateContactInfo(contact) {
  var fieldMap = Drupal.settings.sf_search.field_map;
  for (var field in fieldMap) {
    var inputId = '#' + fieldMap[field];
    $(inputId).val(contact[field]);
    // TODO: Add some effect so that user can see which fields populated
  }
}