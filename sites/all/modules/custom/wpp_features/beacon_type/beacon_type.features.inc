<?php
/**
 * @file
 * beacon_type.features.inc
 */

/**
 * Implements hook_node_info().
 */
function beacon_type_node_info() {
  $items = array(
    'beacon' => array(
      'name' => t('Beacon'),
      'base' => 'node_content',
      'description' => t('This content type is working for iBeacon.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
