<?php
/**
 * @file
 * PdfProcessor interface.
 */

interface PdfExportProcessorInterface {
  /**
   * Creates an instance of the library.
   */
  public function loadLibrary();

  /**
   * Defines the base path.
   */
  public function setBasePath($base_path);

  /**
   * Adds css styles to the pdf.
   *
   * @param string $styles
   *   CSS styles.
   */
  public function addCssStyles($styles);

  /**
   * Sets the HTML to be exported.
   *
   * @param string $html
   *   Final HTML string to be exported.
   */
  public function setHTML($html);

  /**
   * Enable debugging for troubleshooting.
   */
  public function enableDebug();

  /**
   * Save generated file to the filesystem.
   *
   * @param string $filename
   *   The path where the pdf should be exported.
   *
   * @return bool
   *   TRUE if successfully exported. FALSE otherwise.
   */
  public function save($filename);
}
