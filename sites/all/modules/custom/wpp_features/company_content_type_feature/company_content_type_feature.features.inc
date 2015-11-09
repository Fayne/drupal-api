<?php
/**
 * @file
 * company_content_type_feature.features.inc
 */

/**
 * Implements hook_node_info().
 */
function company_content_type_feature_node_info() {
  $items = array(
    'company' => array(
      'name' => t('Company'),
      'base' => 'node_content',
      'description' => t('This content type is working for Company.'),
      'has_title' => '1',
      'title_label' => t('Title (English)'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
