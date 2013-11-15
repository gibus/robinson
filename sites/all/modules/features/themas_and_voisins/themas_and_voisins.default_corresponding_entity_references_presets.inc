<?php
/**
 * @file
 * themas_and_voisins.default_corresponding_entity_references_presets.inc
 */

/**
 * Implements hook_default_corresponding_entity_references().
 */
function themas_and_voisins_default_corresponding_entity_references() {
  $export = array();

  $cnr_obj = new stdClass();
  $cnr_obj->disabled = FALSE; /* Edit this to true to make a default cnr_obj disabled initially */
  $cnr_obj->api_version = 1;
  $cnr_obj->entity_types_content_fields = 'node*voisin*field_ref_thema*node*thematique*field_ref_voisin';
  $cnr_obj->enabled = 1;
  $export['node*voisin*field_ref_thema*node*thematique*field_ref_voisin'] = $cnr_obj;

  return $export;
}
