<?php
/**
 * @file
 * Admin forms
 */

function islandora_altmetrics_admin_form($form, &$form_state) {

  drupal_add_js('https://d1bxh8uas1mnw7.cloudfront.net/assets/embed.js', 'external');
  drupal_add_js(drupal_get_path('module', 'islandora_altmetrics') . '/js/altmetric.js');


  $badge_styles = array(
    "4" => "small badge",
    "2" => "medium badge",
    "1" => "large badge",
    "donut" => "small donut",
    "medium-donut" => "medium donut",
    "large-donut" => "large donut",
    "bar" => "small bar",
    "medium-bar" => "medium bar",
    "large-bar" => "large bar",
  );

  $form['islandora_altmetrics_badge'] = array(
    '#type' => 'select',
    '#title' => t('Altmetrics Badge'),
    '#options' => $badge_styles,
    '#description' => t('Name of the badge style to use when displaying the Altmetrics information.'),
    '#default_value' => variable_get('islandora_altmetrics_badge', '2'),
    '#ajax' => array(
      'wrapper' => 'badge-preview',
      'callback' => 'islandora_altmetrics_preview_badge',
      'method' => 'replace',
      'event' => 'change',
    ),
  );

  $form['islandora_altmetrics_popover'] = array(
    '#type' => 'select',
    '#title' => t('Altmetrics Popover'),
    '#description' => t('Popover direction for extra information.'),
    '#options' => array(
      "" => "None",
      "top" => "Top",
      "right" => "Right",
      "bottom" => "Bottom",
      "left" => "Left",
    ),
    '#default_value' => variable_get('islandora_altmetrics_popover', 'right'),
    '#ajax' => array(
      'wrapper' => 'badge-preview',
      'callback' => 'islandora_altmetrics_preview_badge',
      'method' => 'replace',
      'event' => 'change',
    ),
  );

  $form['islandora_altmetrics_wrapper'] = array(
    '#type' => 'item',
    '#title' => t('Example badge'),
    '#prefix' => '<div id="badge-preview">',
    '#suffix' => '</div>',
  );

  $badge = !empty($form_state['values']['islandora_altmetrics_badge']) ?
    $form_state['values']['islandora_altmetrics_badge'] :
    variable_get('islandora_altmetrics_badge', '2');
  $popover = !empty($form_state['values']['islandora_altmetrics_popover']) ?
    $form_state['values']['islandora_altmetrics_popover'] :
    variable_get('islandora_altmetrics_popover', 'right');
  $sample_doi = "10.1038/nature.2014.14583";

  $form['islandora_altmetrics_wrapper']['islandora_altmetrics_badge_preview'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('altmetric-embed'),
      'data-badge-popover' => $popover,
      'data-badge-type' => $badge,
      'data-doi' => $sample_doi,
      'data-hide-no-mentions' => "true",
    ),
  );
  return system_settings_form($form);
}

/**
 * Admin form Ajax callback.
 *
 * @param $form
 *   The Drupal form object.
 * @param $form_state
 *   The Drupal form state.
 *
 * @return array
 *   The render array.
 */
function islandora_altmetrics_preview_badge($form, $form_state) {
  $commands = array();
  // This is the replacement for "return $form['islandora_altmetrics_wrapper'];"
  // This also just specifies the same id in $form['islandora_altmetrics_wrapper']['#prefix']
  $commands[] = ajax_command_html('#badge-preview' , render($form['islandora_altmetrics_wrapper']));

  // This is what will call our JS command
  $commands[] = array (
    // The command in my JS file
    'command' => 'islandoraAltmetricsRenderBadge',
  );

  return array('#type' => 'ajax', '#commands' => $commands);
}