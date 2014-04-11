<?php
/**
 * @file
 * programme.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function programme_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "corresponding_entity_references" && $api == "default_corresponding_entity_references_presets") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function programme_node_info() {
  $items = array(
    'programme' => array(
      'name' => t('Programme'),
      'base' => 'node_content',
      'description' => t('Une sélection de thématiques diffusé lors d\'un rendez-vous'),
      'has_title' => '1',
      'title_label' => t('Titre'),
      'help' => '',
    ),
  );
  return $items;
}
