/**
 * @file
 * PDF Export button management.
 */

(function ($) {
  'use strict';

  Drupal.behaviors.pdfExport = {
    attach: function (context, settings) {
      $('.pdf-export', context).each(function () {
        var $button = $(this);

        $button.click(function () {

          // Prevents too many clicks.
          if ($button.hasClass('generating-pdf')) {
            return false;
          }

          $button.addClass('generating-pdf');

          var content = Drupal.behaviors.pdfExport.getHtml($button);

          $.ajax({
            url: Drupal.settings.basePath + Drupal.settings.pathPrefix + 'pdf_export/render',
            data: {
              html: content,
              filename: $button.attr('data-pdf'),
              css_paths: $button.attr('data-css-paths'),
              css_theme: $button.attr('data-css-theme'),
            },
            type: 'POST',
            dataType: 'json',
            success: function (data) {
              location.href = data.url;
            },

            complete: function () {
              $button.removeClass('generating-pdf');
            },

            error: function (jqXHR) {
              var response = $.parseJSON(jqXHR.responseText);

              alert(response.errorMessage);
            },

          });
        });
      });
    },

    getHtml: function ($button) {
      var $content = $($button.attr('data-content-selector'));

      if ($content.length === 0) {
        return;
      }

      var $clone = $content.clone();
      var html = '';
      $clone.each(function (index, value) {
        $('.generating-pdf', value).remove();

        html += this.elementToHtml($(value));
      }.bind(this));

      return html;
    },

    elementToHtml: function ($element) {
      return $element.wrap('<div>').parent().html();
    },
  };
})(jQuery);
