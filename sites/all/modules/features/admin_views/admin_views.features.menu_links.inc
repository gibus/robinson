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

  // Exported menu link: management_main-menu:admin/structure/menu/manage/main-menu
  $menu_links['management_main-menu:admin/structure/menu/manage/main-menu'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure/menu/manage/main-menu',
    'router_path' => 'admin/structure/menu/manage/%',
    'link_title' => 'Main menu',
    'options' => array(
      'identifier' => 'management_main-menu:admin/structure/menu/manage/main-menu',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_menus:admin/structure/menu',
  );
  // Exported menu link: management_menus:admin/structure/menu
  $menu_links['management_menus:admin/structure/menu'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure/menu',
    'router_path' => 'admin/structure/menu',
    'link_title' => 'Menus',
    'options' => array(
      'attributes' => array(
        'title' => 'Add new menus to your site, edit existing menus, and rename and reorganize menu links.',
      ),
      'identifier' => 'management_menus:admin/structure/menu',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_structure:admin/structure',
  );
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
  // Exported menu link: management_user-menu:admin/structure/menu/manage/user-menu
  $menu_links['management_user-menu:admin/structure/menu/manage/user-menu'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure/menu/manage/user-menu',
    'router_path' => 'admin/structure/menu/manage/%',
    'link_title' => 'User menu',
    'options' => array(
      'identifier' => 'management_user-menu:admin/structure/menu/manage/user-menu',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_menus:admin/structure/menu',
  );
  // Exported menu link: navigation_:node/%
  $menu_links['navigation_:node/%'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/%',
    'router_path' => 'node/%',
    'link_title' => '',
    'options' => array(
      'identifier' => 'navigation_:node/%',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
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
    'weight' => -46,
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
    'weight' => -44,
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
  // Exported menu link: navigation_les-pages:http://dev.beta.leprojetrobinson.org/admin/content/nodes?type=page&status=All
  $menu_links['navigation_les-pages:http://dev.beta.leprojetrobinson.org/admin/content/nodes?type=page&status=All'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'http://dev.beta.leprojetrobinson.org/admin/content/nodes?type=page&status=All',
    'router_path' => '',
    'link_title' => 'les pages',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'navigation_les-pages:http://dev.beta.leprojetrobinson.org/admin/content/nodes?type=page&status=All',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'navigation_lister-tous-les-contenus:admin/content/nodes',
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
    'weight' => -48,
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
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: navigation_page:node/add/page
  $menu_links['navigation_page:node/add/page'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add/page',
    'router_path' => 'node/add/page',
    'link_title' => 'Page',
    'options' => array(
      'attributes' => array(
        'title' => 'Use this content type to add static pages like "about" "contact" etc',
      ),
      'identifier' => 'navigation_page:node/add/page',
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
  // Exported menu link: navigation_thmatique:node/add/thematique
  $menu_links['navigation_thmatique:node/add/thematique'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add/thematique',
    'router_path' => 'node/add/thematique',
    'link_title' => 'Thématique',
    'options' => array(
      'attributes' => array(
        'title' => 'Un sujet abordé par Jacqueline Robinson lors d’un interview',
      ),
      'identifier' => 'navigation_thmatique:node/add/thematique',
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
  // Exported menu link: navigation_voisin:node/add/voisin
  $menu_links['navigation_voisin:node/add/voisin'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add/voisin',
    'router_path' => 'node/add/voisin',
    'link_title' => 'Voisin',
    'options' => array(
      'attributes' => array(
        'title' => 'Un média lié à une thématique (voisin) ou appelé aléatoirement (atmosphère)',
      ),
      'identifier' => 'navigation_voisin:node/add/voisin',
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
    'weight' => -43,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add content');
  t('Compose tips');
  t('Log out');
  t('Main menu');
  t('Media');
  t('Menus');
  t('Page');
  t('Programme');
  t('SimpleMenu');
  t('Thématique');
  t('User account');
  t('User menu');
  t('Voisin');
  t('Workflow summary');
  t('dashboard');
  t('les pages');


  return $menu_links;
}
