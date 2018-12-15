/*
 * @file
 * Commerce Availability javascript
 */

(function($) {
  "use strict";

  var last_context = 1;
  var dateLimit = new Date();
  var today = new Date();

  Drupal.behaviors.commerce_availability = {
    attach : function(context, settings) {

      $('.date-clear', context).once('commerce_availability', function () {
        var daysLimit = Drupal.settings.commerce_availability.months_limit * 31;
        dateLimit.setDate(dateLimit.getDate() + daysLimit);

        if ($('.views-field-product-id').length > 0) {
          commerce_availability_customize_order_table();
        }

        $('.date-clear', context).each(function() {
          var pid = null;
          if ($(this).attr('id').indexOf(Drupal.settings.commerce_availability.date_field) > 0) {
            if ($('input[name="product_id"]', context).length > 0) {
              var n = $(this).closest('form').attr("id").split("--")[1];
              if (n > last_context) {
                last_context++;
              }
              else if (typeof n !== 'undefined') {
                return;
              }
              pid = $(this).closest('form').find('input[name="product_id"]').val();
            }
            else if ($('select[name="product_id"]', context).length > 0) {
              pid = $('select[name="product_id"] option:selected', context).val();
            }
            else if ($(this).closest('tr').find('td:first').length > 0) {
              pid = + ($(this).closest('tr').find('td:first').text());
            }

            if (pid) {
              var data = [{}];
              $.ajax({
                type : 'POST',
                url: settings.basePath + 'commerce_availability_ajax',
                context : this,
                data : {pid : pid}
              }).done(function(data) {
                data = $.parseJSON(data);
                if (data !== 'null' && data.length !== 0) {
                  commerce_availability_set_availability_dates($(this).attr('id'), data);
                }
                else {
                  commerce_availability_not_available($(this).attr('id'));
                }
              });
            }

            var months_limit = '+' + Drupal.settings.commerce_availability.months_limit + 'M';
            var numberOfMonths = 2;
            var picker_id = $(this).attr('id');
            Drupal.settings.datePopup[picker_id].settings.firstDay = 1;
            Drupal.settings.datePopup[picker_id].settings.maxDate = months_limit;
            Drupal.settings.datePopup[picker_id].settings.minDate = 0;
            Drupal.settings.datePopup[picker_id].settings.numberOfMonths = numberOfMonths;
            Drupal.settings.datePopup[picker_id].settings.beforeShowDay = function (date) {
              return commerce_availability_get_availability($(this).attr('id'), date);
            }
            Drupal.settings.datePopup[picker_id].settings.onClose = function () {
              return commerce_availability_check_availability($(this).attr('id'));
            },

            $(this).parents('.container-inline-date').click(function() {
              $(this).find('.date-clear').focus().focus();
            });
          }
        });
      });
    }
  }

  var commerce_availability_customize_order_table = function() {
    $('.views-table th:nth-child(1)').hide();
    $('.views-table td:nth-child(1)').hide();
    $('.views-row-edit-static').filter(function() {
      return $(this).text() == '';
    }).remove();
    $('.views-row-edit-static').next().hide();
    $('.views-row-edit-static').next().find('.date-clear').removeClass('date-clear');
  }

  var commerce_availability_not_available = function(picker_id) {
    $('#' + picker_id).attr('readonly', 'readonly');
    $('#' + picker_id).unbind('focus');
    $('#' + picker_id).parents('form').find('.form-submit').attr('disabled', true);
    $('#' + picker_id).parents('form').find('.form-submit').addClass('unavailable');
    $('#' + picker_id).parents('form').find('.form-submit').text(Drupal.t('Not available'));
  }

  var commerce_availability_set_availability_dates = function(picker_id, data) {
    Drupal.settings.datePopup[picker_id].settings.available_dates = data;
    commerce_availability_set_first_available_date(picker_id, new Date(), dateLimit);
  }

  var commerce_availability_get_availability = function(picker_id, date) {
    var day = $.datepicker.formatDate("yy-mm-dd", date);
    if ($(Drupal.settings.datePopup[picker_id].settings.available_dates).length > 0) {
      if (Drupal.settings.datePopup[picker_id].settings.available_dates[day]) {
        return [false, 'unavailable', Drupal.t('Unavailable day')];
      }
    }
      return [true];
  }

  var commerce_availability_check_availability = function(picker_id) {
    var day = $('#' + picker_id).datepicker('getDate');
    var today = new Date();
    var setFirst = false;
    if ($(Drupal.settings.datePopup[picker_id].settings.available_dates).length > 0
      && Drupal.settings.datePopup[picker_id].settings.available_dates[day]) {
        setFirst = true;
    }
    else if (day.getTime() < today.getTime()) {
      setFirst = true;
    }
    if (setFirst) {
      commerce_availability_set_first_available_date(picker_id, new Date(), dateLimit);
    }
  }

  var commerce_availability_set_first_available_date = function(picker_id, date, dateLimit) {
    if(commerce_availability_get_availability(picker_id, date)[0] == true) {
      var dateFormat = Drupal.settings.datePopup[picker_id].settings.dateFormat;
      var day = $.datepicker.formatDate(dateFormat, date);
      $('#' + picker_id).val(day);
      return;
    }
    else {
      var nextDay = new Date(date);
      nextDay.setDate(date.getDate() + 1);
      if(nextDay >= dateLimit) {
        return;
      }
      commerce_availability_set_first_available_date(picker_id, nextDay, dateLimit);
    }
  }
})(jQuery);
