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
    'comportement' => array(
      'name' => 'Comportement',
      'machine_name' => 'comportement',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 0,
    ),
    'type_de_media' => array(
      'name' => 'Type de média',
      'machine_name' => 'type_de_media',
      'description' => 'Le type de media d\'un voisin',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -9,
      'language' => 'und',
      'i18n_mode' => 0,
    ),
    'voc_type_voisin' => array(
      'name' => 'Voisin type (deprecated)',
      'machine_name' => 'voc_type_voisin',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -8,
      'language' => 'und',
      'i18n_mode' => 0,
    ),
  );
}
