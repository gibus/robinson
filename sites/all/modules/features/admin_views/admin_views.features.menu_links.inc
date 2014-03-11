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

  // Exported menu link: navigation_add-content:node/add
  $menu_links['navigation_add-content:node/add'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add',
    'router_path' => 'node/add',
    'link_title' => 'Add content',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'navigation_add-content:node/add',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: navigation_ajouter-un-comportement:http://dev.leprojetrobinson.org/admin/structure/taxonomy/comportement/add
  $menu_links['navigation_ajouter-un-comportement:http://dev.leprojetrobinson.org/admin/structure/taxonomy/comportement/add'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'http://dev.leprojetrobinson.org/admin/structure/taxonomy/comportement/add',
    'router_path' => '',
    'link_title' => 'Ajouter un comportement',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'navigation_ajouter-un-comportement:http://dev.leprojetrobinson.org/admin/structure/taxonomy/comportement/add',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'navigation_comportements:admin/structure/taxonomy/comportement',
  );
  // Exported menu link: navigation_comportements:admin/structure/taxonomy/comportement
  $menu_links['navigation_comportements:admin/structure/taxonomy/comportement'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'admin/structure/taxonomy/comportement',
    'router_path' => 'admin/structure/taxonomy/%',
    'link_title' => 'Comportements',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'navigation_comportements:admin/structure/taxonomy/comportement',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: navigation_compose-tips:filter/tips
  $menu_links['navigation_compose-tips:filter/tips'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'filter/tips',
    'router_path' => 'filter/tips',
    'link_title' => 'Compose tips',
    'options' => array(
      'identifier' => 'navigation_compose-tips:filter/tips',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -43,
    'customized' => 1,
  );
  // Exported menu link: navigation_dashboard:admin/dashboard
  $menu_links['navigation_dashboard:admin/dashboard'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'admin/dashboard',
    'router_path' => 'admin/dashboard',
    'link_title' => 'dashboard',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'navigation_dashboard:admin/dashboard',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: navigation_log-out:user/logout
  $menu_links['navigation_log-out:user/logout'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Log out',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'navigation_log-out:user/logout',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: navigation_media:admin/content/medias
  $menu_links['navigation_media:admin/content/medias'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'admin/content/medias',
    'router_path' => 'admin/content',
    'link_title' => 'Media',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'navigation_media:admin/content/medias',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
  );
  // Exported menu link: navigation_user-account:user
  $menu_links['navigation_user-account:user'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'User account',
    'options' => array(
      'alter' => TRUE,
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'navigation_user-account:user',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: navigation_workflow-summary:workflow
  $menu_links['navigation_workflow-summary:workflow'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'workflow',
    'router_path' => 'workflow',
    'link_title' => 'Workflow summary',
    'options' => array(
      'identifier' => 'navigation_workflow-summary:workflow',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -42,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add content');
  t('Ajouter un comportement');
  t('Comportements');
  t('Compose tips');
  t('Log out');
  t('Media');
  t('User account');
  t('Workflow summary');
  t('dashboard');


  return $menu_links;
}
