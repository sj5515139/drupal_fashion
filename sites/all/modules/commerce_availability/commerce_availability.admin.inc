<?php
/**
 * @file
 * Commerce Availability admin settings form code.
 */

/**
 * Search for entities names.
 *
 * @param object $field
 *   The entity name for search.
 * @param string $entity_type
 *   The entity type for search.
 */
function commerce_availability_get_enames(&$field, $entity_type) {
  $options = array(t('-- empty --'));
  if (!is_array($field)) {
    $field = field_info_field($field);
  }
  if (!empty($field['bundles'][$entity_type])) {
    foreach ($field['bundles'][$entity_type] as $ename) {
      $options[$ename] = $ename;
    }
  }
  if (count($options) > 1) {
    unset($options[0]);
  }
  return $options;
}

/**
 * Search for line items for an specific field.
 *
 * @param array $form
 *   Nested array of form elements that comprise the form.
 * @param array $form_state
 *   A keyed array containing the current state of the form.
 */
function commerce_availability_get_lines(array $form, array &$form_state) {
  $ca_name_l_value = isset($form_state['values']['commerce_availability_f_name_l']) ? $form_state['values']['commerce_availability_f_name_l'] : '';
  $field = field_info_field($ca_name_l_value);
  $options = commerce_availability_get_enames($field, 'commerce_line_item');
  $form['line_item_fieldset']['commerce_availability_type_l']['#options'] = $options;
  return $form['line_item_fieldset']['commerce_availability_type_l'];
}

/**
 * Search for products for an specific field.
 *
 * @param array $form
 *   Nested array of form elements that comprise the form.
 * @param array $form_state
 *   A keyed array containing the current state of the form.
 */
function commerce_availability_get_products(array $form, array &$form_state) {
  $ca_name_p_value = isset($form_state['values']['commerce_availability_f_name_p']) ? $form_state['values']['commerce_availability_f_name_p'] : '';
  $field = field_info_field($ca_name_p_value);
  $options = commerce_availability_get_enames($field, 'commerce_product');
  $form['product_fieldset']['commerce_availability_type_p']['#options'] = $options;
  return $form['product_fieldset']['commerce_availability_type_p'];
}

/**
 * Search for fields.
 *
 * @param string $type
 *   Field type name.
 */
function commerce_availability_get_fields($type) {
  $options = array();
  $fields = field_info_fields();
  foreach ($fields as $key => $field) {
    if ($field['type'] == $type) {
      $options[$key] = $key;
    }
  }
  return $options;
}

/**
 * Form definition for admin settings.
 *
 * @param array $form
 *   Nested array of form elements that comprise the form.
 * @param array $form_state
 *   A keyed array containing the current state of the form.
 */
function commerce_availability_admin(array $form, array &$form_state) {
  $form['line_item_fieldset'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#title' => t('Line item field selection'),
    '#attributes' => array('id' => 'line_item_fieldset'),
  );
  $form['product_fieldset'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#title' => t('Product field selection'),
    '#attributes' => array('id' => 'product_fieldset'),
  );

  $ca_f_name_l = variable_get('commerce_availability_f_name_l', '');
  $default_ca_f_name_l = !empty($ca_f_name_l) ? array($ca_f_name_l => $ca_f_name_l) : array();
  $form['line_item_fieldset']['commerce_availability_f_name_l'] = array(
    '#type' => 'select',
    '#title' => t('Line item datetime field'),
    '#required' => TRUE,
    '#empty_option' => t('-- empty --'),
    '#empty_value' => 0,
    '#options' => commerce_availability_get_fields('datetime'),
    '#default_value' => $default_ca_f_name_l,
    '#ajax' => array(
      'event' => 'change',
      'wrapper' => 'ca_f_type_l_wrapper',
      'callback' => 'commerce_availability_get_lines',
      'method' => 'replace',
    ),
  );
  $ca_type_l_string = variable_get('commerce_availability_type_l', '');
  $ca_type_l = unserialize($ca_type_l_string);
  $default_ca_type_l = !empty($ca_type_l) ? $ca_type_l : array();
  $form['line_item_fieldset']['commerce_availability_type_l'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#title' => t('Select the line items to apply behaviour'),
    '#default_value' => $default_ca_type_l,
    '#required' => TRUE,
    '#empty_option' => t('-- empty --'),
    '#empty_value' => 0,
    '#validated' => TRUE,
    '#prefix' => '<div id="ca_f_type_l_wrapper">',
    '#suffix' => '</div>',
    '#options' => commerce_availability_get_enames($ca_f_name_l, 'commerce_line_item'),
  );

  $ca_f_name_p = variable_get('commerce_availability_f_name_p', '');
  $default_ca_f_name_p = !empty($ca_f_name_p) ? array($ca_f_name_p => $ca_f_name_p) : array();
  $form['product_fieldset']['commerce_availability_f_name_p'] = array(
    '#type' => 'select',
    '#title' => t('Product calendar field'),
    '#required' => TRUE,
    '#empty_option' => t('-- empty --'),
    '#empty_value' => 0,
    '#options' => commerce_availability_get_fields('availability_calendar'),
    '#default_value' => $default_ca_f_name_p,
    '#ajax' => array(
      'event' => 'change',
      'wrapper' => 'ca_f_type_p_wrapper',
      'callback' => 'commerce_availability_get_products',
      'method' => 'replace',
    ),
  );
  $ca_type_p_string = variable_get('commerce_availability_type_p', '');
  $ca_type_p = unserialize($ca_type_p_string);
  $default_ca_type_p = !empty($ca_type_p) ? $ca_type_p : array();
  $form['product_fieldset']['commerce_availability_type_p'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#title' => t('Select the products to apply behaviour'),
    '#default_value' => $default_ca_type_p,
    '#required' => TRUE,
    '#empty_option' => t('-- empty --'),
    '#empty_value' => 0,
    '#validated' => TRUE,
    '#prefix' => '<div id="ca_f_type_p_wrapper">',
    '#suffix' => '</div>',
    '#options' => commerce_availability_get_enames($ca_f_name_p, 'commerce_product'),
  );

  $form['commerce_availability_n_days_before'] = array(
    '#type' => 'textfield',
    '#title' => t('Days before'),
    '#default_value' => variable_get('commerce_availability_n_days_before', 2),
    '#size' => 2,
    '#maxlength' => 2,
    '#description' => t('Extra days before the event for shipping management.'),
    '#required' => TRUE,
  );
  $form['commerce_availability_n_days_after'] = array(
    '#type' => 'textfield',
    '#title' => t('Days after'),
    '#default_value' => variable_get('commerce_availability_n_days_after', 2),
    '#size' => 2,
    '#maxlength' => 2,
    '#description' => t('Extra days after the event for shipping management.'),
    '#required' => TRUE,
  );
  $form['commerce_availability_n_months_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Limit of months on the calendar'),
    '#default_value' => variable_get('commerce_availability_n_months_limit', 6),
    '#size' => 2,
    '#maxlength' => 2,
    '#description' => t('Limit of months on the calendar. 0 for no limit.'),
    '#required' => TRUE,
  );
  $form['commerce_availability_n_initial_buffer'] = array(
    '#type' => 'textfield',
    '#title' => t('Initial unavailable days'),
    '#default_value' => variable_get('commerce_availability_n_initial_buffer', 3),
    '#size' => 2,
    '#maxlength' => 2,
    '#description' => t('Unavailable days after the current day.'),
    '#required' => TRUE,
  );
  $form['commerce_availability_n_day_off'] = array(
    '#type' => 'textfield',
    '#title' => t('Day off'),
    '#default_value' => variable_get('commerce_availability_n_day_off', 6),
    '#size' => 2,
    '#maxlength' => 2,
    '#description' => t('Week day in number for the day off (-1 to invalidate). Whether the first or last day of the shipment period is a day off, the module adds a extra day to extend shipping management.'),
    '#required' => TRUE,
  );
  $form['commerce_availability_d_official_holidays'] = array(
    '#title' => t('Official holidays'),
    '#type' => 'textarea',
    '#description' => t('A comma-separated list of dates formatted as MM-DD. Whether the first or last day of the shipment period is holiday, the module adds a extra day to extend shipping management.'),
    '#default_value' => variable_get('commerce_availability_d_official_holidays', ''),
    '#rows' => 4,
    '#resizable' => TRUE,
  );
  $form['commerce_availability_d_bank_holidays'] = array(
    '#title' => t('Unofficial or bank holidays'),
    '#type' => 'textarea',
    '#description' => t('A comma-separated list of dates formatted as YYYY-MM-DD. Whether the first or last day of the shipment period is holiday, the module adds a extra day to extend shipping management.'),
    '#default_value' => variable_get('commerce_availability_d_bank_holidays', ''),
    '#rows' => 4,
    '#resizable' => TRUE,
  );
  $form['#validate'][] = 'commerce_availability_validate';
  return system_settings_form($form);
}

/**
 * Check for bookings in the future.
 */
function commerce_availability_check_orders() {
  $check_orders = TRUE;
  $statuses = commerce_order_statuses();
  unset($statuses['canceled']);
  $orders = array();
  foreach ($statuses as $status) {
    $orders_status = commerce_order_load_multiple(array(), array('status' => $status), TRUE);
    $orders = array_merge($orders, $orders_status);
  }
  foreach ($orders as $order) {
    if (!$check_orders) {
      break;
    }
    $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
    if (!empty($order_wrapper->commerce_line_items)) {
      foreach ($order_wrapper->commerce_line_items as $line_item_wrapper) {
        list($cid, $timestamp) = commerce_availability_check_line_item($line_item_wrapper);
        if (!empty($timestamp) && !empty($cid)) {
          if ($timestamp > time()) {
            $check_orders = FALSE;
            break;
          }
        }
      }
    }
  }
  return $check_orders;
}

/**
 * Check for changes that affect the order forms.
 *
 * @param array $form
 *   Nested array of form elements that comprise the form.
 * @param array $form_state
 *   A keyed array containing the current state of the form.
 */
function commerce_availability_check_values(array &$form, array &$form_state) {
  $check_changes = TRUE;
  $variables = array(
    'commerce_availability_n_days_before',
    'commerce_availability_n_days_after',
    'commerce_availability_n_day_off',
  );
  foreach ($variables as $variable) {
    if ($form_state['values'][$variable] != $form[$variable]['#default_value']) {
      $check_changes = FALSE;
      break;
    }
  }
  return $check_changes;
}

/**
 * Validate function for admin settings.
 *
 * @param array $form
 *   Nested array of form elements that comprise the form.
 * @param array $form_state
 *   A keyed array containing the current state of the form.
 */
function commerce_availability_validate(array $form, array &$form_state) {
  $values = $form_state['values'];

  if (!commerce_availability_check_values($form, $form_state) && !commerce_availability_check_orders()) {
    form_set_error('foo', check_plain(t('You can not make these changes. There are orders in the future affected. Cancel them or wait for expire.')));
  }

  foreach ($values as $name => $value) {
    if (strpos($name, 'commerce_availability_n_day_off') === 0 && (!is_numeric($value) || $value < -1 || $value > 6)) {
      form_set_error($name, check_plain(t('You must enter a positive integer between 0 and 6: !name field (-1 to invalidate) ' , array('!name' => $name))));
    }
    elseif (strpos($name, 'commerce_availability_n') === 0 && (!is_numeric($value) || $value < 0)) {
      form_set_error($name, check_plain(t('You must enter a positive integer or 0 for: !name field', array('!name' => $name))));
    }
    elseif (strpos($name, 'commerce_availability_f') === 0 && empty($value)) {
      form_set_error($name, check_plain(t('Empty value for: !name. You must select a field.', array('!name' => $name))));
    }
    elseif (strpos($name, 'commerce_availability_type') === 0 && empty($value)) {
      form_set_error($name, check_plain(t('Empty value for: !name. You must select a field.', array('!name' => $name))));
    }
    elseif (strpos($name, 'commerce_availability_type') === 0 && !empty($value)) {
      $form_state['values'][$name] = serialize($value);
    }
    elseif (strpos($name, 'commerce_availability_d_official_holidays') === 0) {
      $error = FALSE;
      $days = array_map('trim', explode(',', $value));
      $days = array_diff($days, array(''));
      if (!empty($days)) {
        foreach ($days as $day) {
          if (!preg_match('/^(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$/', $day)) {
            form_set_error($name, check_plain(t('Invalid format days for: !name.', array('!name' => $name))));
            $error = TRUE;
            break;
          }
        }
      }
      if (!$error) {
        $form_state['values'][$name] = implode(',', $days);
      }
    }
    elseif (strpos($name, 'commerce_availability_d_bank_holidays') === 0) {
      $error = FALSE;
      $days = array_map('trim', explode(',', $value));
      $days = array_diff($days, array(''));
      if (!empty($days)) {
        foreach ($days as $day) {
          if (!preg_match('/^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$/', $day)) {
            form_set_error($name, check_plain(t('Invalid format days for: !name.', array('!name' => $name))));
            $error = TRUE;
            break;
          }
        }
      }
      if (!$error) {
        $form_state['values'][$name] = implode(',', $days);
      }
    }
  }
}
