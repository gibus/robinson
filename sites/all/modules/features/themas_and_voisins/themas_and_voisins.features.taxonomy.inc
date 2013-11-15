<?php
/**
 * @file
 * themas_and_voisins.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function themas_and_voisins_taxonomy_default_vocabularies() {
  return array(
    'voc_type_voisin' => array(
      'name' => 'Type de voisin',
      'machine_name' => 'voc_type_voisin',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 0,
    ),
  );
}
