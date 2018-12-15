<?php
/**
 * @file
 * Definition of pdf_export_views_handler_area.
 */

/**
 * PDF export area text handler.
 *
 * @ingroup views_area_handlers
 */
class pdf_export_views_handler_area extends views_handler_area {

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();

    $options['button_label'] = array('default' => 'Export as PDF');
    $options['button_classes'] = array('default' => 'btn');
    $options['pdf_name'] = array('default' => NULL);
    $options['pdf_content_selector'] = array('default' => '.view');
    $options['css_theme'] = array('default' => NULL);
    $options['css_files'] = array('default' => NULL);

    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['button_label'] = array(
      '#title' => t('Button label'),
      '#type' => 'textfield',
      '#default_value' => $this->options['button_label'],
    );

    $form['button_classes'] = array(
      '#title' => t('CSS classes'),
      '#type' => 'textfield',
      '#default_value' => $this->options['button_classes'],
    );

    $form['pdf_name'] = array(
      '#title' => t('PDF name'),
      '#description' => t("Let this field empty if you want to use the view's name. If you enter a name, you should append the .pdf at the end."),
      '#type' => 'textfield',
      '#default_value' => $this->options['pdf_name'],
    );

    $form['pdf_content_selector'] = array(
      '#title' => t('PDF content selector'),
      '#description' => t('Use the selector for the content you would like to display on PDF, you can separate it with comma and the order passed will be respected.'),
      '#type' => 'textfield',
      '#required' => TRUE,
      '#default_value' => $this->options['pdf_content_selector'],
    );

    $themes = list_themes();
    $themes_options = array();
    foreach ($themes as $theme_name => $theme_obj) {
      if (1 == $theme_obj->status) {
        $themes_options[$theme_name] = $theme_name;
      }
    }
    $form['css_theme'] = array(
      '#title' => t('CSS theme'),
      '#description' => t('The theme where the css file is.'),
      '#type' => 'select',
      '#options' => $themes_options,
      '#default_value' => $this->options['css_theme'],
    );

    $form['css_files'] = array(
      '#title' => t('CSS file'),
      '#description' => t('The path to the css file relative to the theme path. You can include multiple paths separated by an space.'),
      '#type' => 'textfield',
      '#default_value' => $this->options['css_files'],
    );
  }

  /**
   * {@inheritdoc}
   */
  public function render($empty = FALSE) {
    // Don't show export button when view is empty and "Display even if view has
    // no result" is unchecked
    if ($empty && !$this->options['empty']) {
      return '';
    }

    $button_classes = explode(' ', $this->options['button_classes']);

    $pdf_name = $this->view->name . '.pdf';
    if (!empty($this->options['pdf_name'])) {
      $pdf_name = $this->options['pdf_name'];
    }
    return theme('pdf_export_button', array(
      'attributes' => array(
        'class' => $button_classes,
      ),
      'label' => $this->options['button_label'],
      'file_name' => $pdf_name,
      'css_paths' => $this->options['css_files'],
      'theme_name' => $this->options['css_theme'],
      'css_selector' => $this->options['pdf_content_selector'],
    ));
  }
}
