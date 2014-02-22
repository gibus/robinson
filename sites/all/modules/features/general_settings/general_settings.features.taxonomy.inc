<?php
/**
 * @file
 * general_settings.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function general_settings_taxonomy_default_vocabularies() {
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
  );
}
