<?php
/**
 * @file
 * programme.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function programme_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: navigation_programme:node/add/programme
  $menu_links['navigation_programme:node/add/programme'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add/programme',
    'router_path' => 'node/add/programme',
    'link_title' => 'Programme',
    'options' => array(
      'attributes' => array(
        'title' => 'Une sélection de thématiques diffusé lors d\'un rendez-vous',
      ),
      'identifier' => 'navigation_programme:node/add/programme',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'navigation_ajouter-du-contenu:node/add',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Programme');


  return $menu_links;
}
