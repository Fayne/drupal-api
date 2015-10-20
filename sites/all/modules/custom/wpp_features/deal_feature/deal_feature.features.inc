<?php
/**
 * @file
 * deal_feature.features.inc
 */

/**
 * Implements hook_node_info().
 */
function deal_feature_node_info() {
  $items = array(
    'deal' => array(
      'name' => t('Deal'),
      'base' => 'node_content',
      'description' => t('This content type is working for Deal.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
