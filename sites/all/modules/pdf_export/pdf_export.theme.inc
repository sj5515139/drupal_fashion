<?php
/**
 * @file
 * Theme functions for PDF Export module.
 */

/**
 * Theme function for the PDF Export module.
 */
function theme_pdf_export_button($variables) {
  $attributes = $variables['attributes'] + array(
    'data-pdf' => $variables['file_name'],
    'data-css-paths' => $variables['css_paths'],
    'data-css-theme' => $variables['theme_name'],
    'data-content-selector' => $variables['css_selector'],
    'title' => $variables['label'],
  );

  $attributes['class'][] = 'pdf-export';

  return l($variables['label'], 'javascript:void(0);', array(
    'external' => TRUE,
    'attributes' => $attributes,
  ));
}
