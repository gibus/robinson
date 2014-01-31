<?php
/**
 * @file
 * general_settings.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function general_settings_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_workflow:admin/config/workflow
  $menu_links['management_workflow:admin/config/workflow'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/workflow',
    'router_path' => 'admin/config/workflow',
    'link_title' => 'Workflow',
    'options' => array(
      'attributes' => array(
        'title' => 'Content workflow, editorial workflow tools.',
      ),
      'identifier' => 'management_workflow:admin/config/workflow',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 5,
    'customized' => 0,
    'parent_identifier' => 'management_configuration:admin/config',
  );
  // Exported menu link: management_workflow:admin/config/workflow/workflow
  $menu_links['management_workflow:admin/config/workflow/workflow'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/workflow/workflow',
    'router_path' => 'admin/config/workflow/workflow',
    'link_title' => 'Workflow',
    'options' => array(
      'attributes' => array(
        'title' => 'Allows the creation and assignment of arbitrary workflows to node types.',
      ),
      'identifier' => 'management_workflow:admin/config/workflow/workflow',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_workflow:admin/config/workflow',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Workflow');


  return $menu_links;
}
