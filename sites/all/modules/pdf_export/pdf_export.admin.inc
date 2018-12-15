<?php
/**
 * @file
 * PDF Export: Admin & config area.
 */

/**
 * PDF Export admin form definition.
 */
function pdf_export_admin_form() {
  $form = array();

  $options = array();
  foreach (module_invoke_all('pdf_export_processor_info') as $library => $processor) {
    $options[$library] = $processor['name'];
  }
  $form['pdf_export_library'] = array(
    '#type' => 'select',
    '#title' => t('PDF Library'),
    '#description' => t('Choose what library to use. See the full list at: !d_o_page', array(
      '!d_o_page' => l(t('PDF Export'), 'https://www.drupal.org/project/pdf_export'),
    )),
    '#options' => $options,
    '#default_value' => variable_get('pdf_export_library', FALSE),
  );

  $form['pdf_export_scheme'] = array(
    '#type' => 'select',
    '#title' => t('Save PDF files to'),
    '#description' => t('Choose where the PDF files should be stored when generated.'),
    '#options' => _pdf_export_admin_schemes_to_select(file_get_stream_wrappers()),
    '#default_value' => variable_get('pdf_export_scheme', 'temporary'),
  );

  $form['pdf_export_folder'] = array(
    '#type' => 'textfield',
    '#title' => t('PDFs folder'),
    '#description' => t('It is always recommended to use a folder to prevent security breaches.'),
    '#default_value' => variable_get('pdf_export_folder', 'pdf_export'),
  );

  $form['pdf_export_rewrite_basic_auth'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable basic auth rewrite'),
    '#description' => t('Useful for sites behind basic authentication.'),
    '#default_value' => variable_get('pdf_export_rewrite_basic_auth', FALSE),
  );

  $form['pdf_export_site_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Site domain'),
    '#description' => t('The site domain without trailing slash. i.e. %domain. Use it if the images are not properly exported using the basic auth rewriting does not work.', array(
      '%domain' => 'https://www.domain.com',
    )),
    '#default_value' => variable_get('pdf_export_site_domain', FALSE),
  );

  $form['pdf_export_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable library debug'),
    '#default_value' => variable_get('pdf_export_debug', FALSE),
  );

  return system_settings_form($form);
}

/**
 * Creates the schemes select options for the admin page.
 *
 * @param array $schemes
 *   The array of schemes.
 *
 * @return array
 *   The array to be used on the #options property of the select.
 */
function _pdf_export_admin_schemes_to_select(array $schemes) {
  $options = array();

  foreach ($schemes as $scheme => $info) {
    $options[$scheme] = $info['name'];
  }

  return $options;
}
