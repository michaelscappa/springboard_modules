/**
 * jQuery to support fundraiser behaviors.
 */
Drupal.behaviors.fundraiser = function(context) {

  // Turn autocomplete off on CC and CVV form elements.
  $('#edit-submitted-credit-card-information-card-number, #edit-submitted-credit-card-information-card-cvv').attr('autocomplete','off');

  // Make sure cc number and cvv are numeric
  $('#edit-submitted-credit-card-information-card-number').numeric();
  $('#edit-submitted-credit-card-information-card-cvv').numeric();
  $('#edit-submitted-credit-card-information-card-expiration-date-day').hide();

  // When the amount changes, change the displayed total.
  $('#edit-submitted-donation-quantity').change(function() {
    $('#total').empty();
    var total = this.value * $('#webform-component-donation--amount input:radio:checked').val();
    $('#edit-submitted-donation-quantity').after('<p id="total">Total: $' + total + '</p>');
  });

  // When other amount changes, make sure the amount radio is correctly set.
  $('#edit-submitted-donation-other-amount').change(function() {
    if ($(this).val() != '') {
      $(':radio[value=other]').attr('checked', true);
    }
  });

  // On submission, deactivate the button and show processing message.
  $('.node .webform-client-form #edit-submit').click(function() {
    $(this).hide();
    $('.fundraiser_submit_message').hide();
    $(this).after('<div class="donation-processing-wrapper">'+
    '<p class="donation-thank-you">Thank you.</p><p class="donation-processing">Your donation is being processed.</p>'+
    '<div class="donation-processing-spinner"></div></div>');
  });

}