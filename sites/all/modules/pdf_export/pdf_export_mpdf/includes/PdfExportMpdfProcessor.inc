<?php
/**
 * @file
 * PDF Export: mPDF processor class.
 */

class PdfExportMpdfProcessor implements PdfExportProcessorInterface {
  protected $library;

  /**
   * Initializes the mPDF plugin.
   */
  public function loadLibrary() {
    $library = libraries_load('mpdf');

    if (!$library['loaded']) {
      return FALSE;
    }

    $this->library = new mPDF('utf-8', 'A4');

    return TRUE;
  }

  /**
   * Defines base path for images.
   */
  public function setBasePath($base_path) {
    $this->library->SetBasePath($base_path);
  }

  /**
   * Adds css styles to the pdf.
   *
   * @param string $styles
   *   CSS styles.
   */
  public function addCssStyles($styles) {
    $this->library->WriteHTML($styles, 1);
  }

  /**
   * Sets the HTML to be exported.
   *
   * @param string $html
   *   Final HTML string to be exported.
   */
  public function setHTML($html) {
    $this->library->WriteHTML($html, 2);
  }

  /**
   * Enable debugging for troubleshooting.
   */
  public function enableDebug() {
    $this->library->showImageErrors = TRUE;
    $this->library->debug = TRUE;
  }

  /**
   * Save generated file to the filesystem.
   *
   * @param string $filename
   *   The path where the pdf should be exported.
   *
   * @return bool
   *   TRUE if successfully exported. FALSE otherwise.
   */
  public function save($filename) {
    return $this->library->Output($filename, 'F');
  }
}
