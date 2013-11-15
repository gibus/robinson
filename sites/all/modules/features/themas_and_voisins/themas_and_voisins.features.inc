<?php
/**
 * @file
 * themas_and_voisins.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function themas_and_voisins_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "corresponding_entity_references" && $api == "default_corresponding_entity_references_presets") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
  if ($module == "video_embed_field" && $api == "default_video_embed_styles") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function themas_and_voisins_node_info() {
  $items = array(
    'thematique' => array(
      'name' => t('Thématique'),
      'base' => 'node_content',
      'description' => t('Un sujet abordé par Jacqueline Robinson lors d’un interview'),
      'has_title' => '1',
      'title_label' => t('Titre'),
      'help' => '',
    ),
    'voisin' => array(
      'name' => t('Voisin'),
      'base' => 'node_content',
      'description' => t('Un média lié à une thématique (voisin) ou appelé aléatoirement (atmosphère)'),
      'has_title' => '1',
      'title_label' => t('Titre'),
      'help' => '',
    ),
  );
  return $items;
}
