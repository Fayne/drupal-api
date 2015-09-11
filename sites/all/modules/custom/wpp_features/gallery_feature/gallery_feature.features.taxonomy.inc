<?php
/**
 * @file
 * gallery_feature.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function gallery_feature_taxonomy_default_vocabularies() {
  return array(
    'gallery_type' => array(
      'name' => 'Gallery type',
      'machine_name' => 'gallery_type',
      'description' => 'This is an enum for gallery type.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
