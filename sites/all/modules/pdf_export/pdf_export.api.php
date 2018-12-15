<?php

/**
 * @file
 * Documentation for PDF Export.
 */

/**
 * Change block definition before saving to the database.
 *
 * @param string $html
 *   The exported HTML ready to be exported. You can add your extra content to
 *   it or remove/rewrite whatever you need.
 *
 * @param string $filename
 *   The filename of the file to be exported.
 */
function hook_pdf_export_html_alter(&$html, $filename) {
  // Add a cover on the first page.
  $cover = theme('pdf_cover');

  $html = $cover . $html;
}

/**
 * Define libraries processors.
 *
 * An array indexed by the library machine name containing:
 *   name: Human readable name of the library.
 *   class: Process adapter name.
 *   file: Relative path to the processor file without extension.
 */
function hook_pdf_export_processor_info() {
  return array(
    'library_key' => array(
      'name' => 'My Library',
      'class' => 'PdfExportMyLibraryProcessor',
      'file' => 'includes/PdfExportMyLibraryProcessor',
    ),
  );
}
