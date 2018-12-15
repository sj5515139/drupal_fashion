<?php
/**
 * @file
 * Modify 'commerce_line_item_table' view to show the datetime field.
 */

define('COMMERCE_AVAILABILITY_POS_TABLE', 3);

/**
 * Implements hook_views_default_views_alter().
 *
 * @link https://api.drupal.org/api/views/views.api.php/function/
 * hook_views_default_views_alter/7
 */
function commerce_availability_views_default_views_alter(&$views) {
  $vname = 'commerce_line_item_table';
  if (!empty($views[$vname])) {
    $handler = &$views[$vname]->display['default'];
    $handler->display_options['style_plugin'] = 'editableviews_table';
    $handler->display_options['relationships']['commerce_product_product_id'] = array(
      'id' => 'commerce_product_product_id',
      'table' => 'field_data_commerce_product',
      'field' => 'commerce_product_product_id',
      'required' => TRUE,
    );
    $style_options = &$handler->display_options['style_options'];
    $style_options['columns']['product_id'] = 'product_id';
    $style_options['columns'][COMMERCE_AVAILABILITY_F_NAME_L] = COMMERCE_AVAILABILITY_F_NAME_L;
    $style_options['info']['product_id'] = array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    );
    $style_options['info'][COMMERCE_AVAILABILITY_F_NAME_L] = array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    );
    $fields = &$handler->display_options['fields'];

    $field = array();
    $field['id'] = COMMERCE_AVAILABILITY_F_NAME_L . '_editable';
    $field['table'] = 'field_data_' . COMMERCE_AVAILABILITY_F_NAME_L;
    $field['field'] = COMMERCE_AVAILABILITY_F_NAME_L . '_editable';
    $field['label'] = t('Event day');
    $field['element_type'] = '0';
    $field['element_wrapper_type'] = '0';
    $field['element_default_classes'] = FALSE;
    $field['settings'] = array(
      'format_type' => 'short',
      'fromto' => 'both',
      'multiple_number' => '',
      'multiple_from' => '',
      'multiple_to' => '',
    );
    $field['field_api_classes'] = TRUE;
    $field['widget_type'] = 'date_popup';
    $field['suppress_label'] = 1;
    $field['suppress_description'] = 1;
    $first_array = array_splice($fields, 0, COMMERCE_AVAILABILITY_POS_TABLE);
    $fields = array_merge($first_array, array(COMMERCE_AVAILABILITY_F_NAME_L . '_editable' => $field), $fields);

    $field = array();
    $field['id'] = 'product_id';
    $field['table'] = 'commerce_product';
    $field['field'] = 'product_id';
    $field['relationship'] = 'commerce_product_product_id';
    $field['link_to_product'] = 0;
    $first_array = array_splice($fields, 0, 0);
    $fields = array_merge($first_array, array('product_id' => $field), $fields);
  }
}
