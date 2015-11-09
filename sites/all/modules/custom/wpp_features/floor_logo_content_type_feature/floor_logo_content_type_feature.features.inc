<?php
/**
 * @file
 * floor_logo_content_type_feature.features.inc
 */

/**
 * Implements hook_node_info().
 */
function floor_logo_content_type_feature_node_info() {
  $items = array(
    'floor_logos' => array(
      'name' => t('Company/Brand'),
      'base' => 'node_content',
      'description' => t('This content type works for manager who can specific logo for each floor.'),
      'has_title' => '1',
      'title_label' => t('Company (English)'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
