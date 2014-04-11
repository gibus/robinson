<?php
/**
 * @file
 * programme.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function programme_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_dates|node|programme|form';
  $field_group->group_name = 'group_dates';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'programme';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_htabs';
  $field_group->data = array(
    'label' => 'Dates',
    'weight' => '9',
    'children' => array(
      0 => 'field_prog_plage',
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
  $export['group_dates|node|programme|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_htabs|node|programme|form';
  $field_group->group_name = 'group_htabs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'programme';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'htabs',
    'weight' => '1',
    'children' => array(
      0 => 'group_dates',
      1 => 'group_sequence',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => '',
      ),
    ),
  );
  $export['group_htabs|node|programme|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sequence|node|programme|form';
  $field_group->group_name = 'group_sequence';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'programme';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_htabs';
  $field_group->data = array(
    'label' => 'Séquence',
    'weight' => '8',
    'children' => array(
      0 => 'field_prog_element',
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
  $export['group_sequence|node|programme|form'] = $field_group;

  return $export;
}
