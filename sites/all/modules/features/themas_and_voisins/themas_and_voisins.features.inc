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
 * Implements hook_image_default_styles().
 */
function themas_and_voisins_image_default_styles() {
  $styles = array();

  // Exported image style: voisin.
  $styles['voisin'] = array(
    'name' => 'voisin',
    'label' => 'Voisin',
    'effects' => array(
      1 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 680,
          'height' => 498,
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
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
