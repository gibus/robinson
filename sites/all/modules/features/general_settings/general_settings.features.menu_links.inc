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

  // Exported menu link: navigation_ajouter-un-comportement:http://dev.leprojetrobinson.org/admin/structure/taxonomy/voc_type_voisin/add
  $menu_links['navigation_ajouter-un-comportement:http://dev.leprojetrobinson.org/admin/structure/taxonomy/voc_type_voisin/add'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'http://dev.leprojetrobinson.org/admin/structure/taxonomy/voc_type_voisin/add',
    'router_path' => '',
    'link_title' => 'Ajouter un comportement',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'navigation_ajouter-un-comportement:http://dev.leprojetrobinson.org/admin/structure/taxonomy/voc_type_voisin/add',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'navigation_comportements:admin/structure/taxonomy/voc_type_voisin',
  );
  // Exported menu link: navigation_comportements:admin/structure/taxonomy/voc_type_voisin
  $menu_links['navigation_comportements:admin/structure/taxonomy/voc_type_voisin'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'admin/structure/taxonomy/voc_type_voisin',
    'router_path' => 'admin/structure/taxonomy/%',
    'link_title' => 'Comportements',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'navigation_comportements:admin/structure/taxonomy/voc_type_voisin',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Ajouter un comportement');
  t('Comportements');


  return $menu_links;
}
