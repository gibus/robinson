<?php
/**
 * @file
 * programme.default_corresponding_entity_references_presets.inc
 */

/**
 * Implements hook_default_corresponding_entity_references().
 */
function programme_default_corresponding_entity_references() {
  $export = array();

  $cnr_obj = new stdClass();
  $cnr_obj->disabled = FALSE; /* Edit this to true to make a default cnr_obj disabled initially */
  $cnr_obj->api_version = 1;
  $cnr_obj->entity_types_content_fields = 'node*programme*field_prog_element*node*programme*field_prog_element';
  $cnr_obj->enabled = 0;
  $export['node*programme*field_prog_element*node*programme*field_prog_element'] = $cnr_obj;

  return $export;
}
