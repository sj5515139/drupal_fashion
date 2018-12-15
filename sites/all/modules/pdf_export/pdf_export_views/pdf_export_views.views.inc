<?php
/**
 * @file
 * PDF Export views functions.
 */

/**
 * Implements hook_views_data().
 */
function pdf_export_views_views_data() {
  $data = array();

  $data['pdf_export_views_views']['table']['group'] = t('PDF Export Views');
  $data['pdf_export_views_views']['table']['join'] = array(
    '#global' => array(),
  );

  $data['pdf_export_views_views']['pdf_export_views'] = array(
    'title' => t('Export as PDF button'),
    'help' => t('Exports the view as a PDF.'),
    'area' => array(
      'handler' => 'pdf_export_views_handler_area',
      'access callback' => 'user_access',
      'access arguments' => array('pdf export'),
    ),
  );

  return $data;
}
