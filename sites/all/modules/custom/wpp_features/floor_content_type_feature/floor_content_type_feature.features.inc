<?php
/**
 * @file
 * floor_content_type_feature.features.inc
 */

/**
 * Implements hook_node_info().
 */
function floor_content_type_feature_node_info() {
  $items = array(
    'floor' => array(
      'name' => t('Floor'),
      'base' => 'node_content',
      'description' => t('Display all information of this floor.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
