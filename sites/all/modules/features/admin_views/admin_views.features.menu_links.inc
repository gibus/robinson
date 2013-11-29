<?php
/**
 * @file
 * admin_views.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function admin_views_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_simplemenu:admin/config/simplemenu
  $menu_links['management_simplemenu:admin/config/simplemenu'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/simplemenu',
    'router_path' => 'admin/config/simplemenu',
    'link_title' => 'SimpleMenu',
    'options' => array(
      'attributes' => array(
        'title' => 'Select the menu to display.',
      ),
      'identifier' => 'management_simplemenu:admin/config/simplemenu',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_configuration:admin/config',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('SimpleMenu');


  return $menu_links;
}
