<?php
/**
 * @file
 * oaDOI badge admin options
 */
function islandora_oadoi_admin_form($form, $form_settings) {
  $form['islandora_oai_linktext'] = array(
    '#type' => 'textfield',
    '#title' => t('Link text'),
    '#description' => t('Text to use when generating external download link.'),
    '#default_value' => variable_get('islandora_oai_linktext', 'Link to PDF'),
  );
  return system_settings_form($form);
}
