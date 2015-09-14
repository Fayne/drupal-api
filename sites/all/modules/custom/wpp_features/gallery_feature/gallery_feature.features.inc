<?php
/**
 * @file
 * gallery_feature.features.inc
 */

/**
 * Implements hook_node_info().
 */
function gallery_feature_node_info() {
  $items = array(
    'article' => array(
      'name' => t('Gallery'),
      'base' => 'node_content',
      'description' => t('Use <em>articles</em> for time-sensitive content like news, press releases or blog posts.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
