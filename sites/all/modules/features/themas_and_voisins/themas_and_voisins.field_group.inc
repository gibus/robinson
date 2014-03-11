<?php
/**
 * @file
 * themas_and_voisins.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function themas_and_voisins_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_annexes|node|voisin|form';
  $field_group->group_name = 'group_annexes';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'voisin';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_htabs';
  $field_group->data = array(
    'label' => 'annexes',
    'weight' => '3',
    'children' => array(
      0 => 'field_voisin_credit',
      1 => 'field_ref_thema',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_annexes|node|voisin|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_htabs|node|voisin|form';
  $field_group->group_name = 'group_htabs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'voisin';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'htabs',
    'weight' => '1',
    'children' => array(
      0 => 'group_annexes',
      1 => 'group_media',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => '',
      ),
    ),
  );
  $export['group_htabs|node|voisin|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_media|node|voisin|form';
  $field_group->group_name = 'group_media';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'voisin';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_htabs';
  $field_group->data = array(
    'label' => 'media',
    'weight' => '2',
    'children' => array(
      0 => 'field_son',
      1 => 'field_image',
      2 => 'field_video',
      3 => 'field_texte',
      4 => 'field_type_media',
      5 => 'field_format_video',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_media|node|voisin|form'] = $field_group;

  return $export;
}
