<?php
/**
 * @file
 * general_settings.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function general_settings_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'root' => 'root',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access content overview'.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access workflow summary views'.
  $permissions['access workflow summary views'] = array(
    'name' => 'access workflow summary views',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'workflow_views',
  );

  // Exported permission: 'add terms in comportement'.
  $permissions['add terms in comportement'] = array(
    'name' => 'add terms in comportement',
    'roles' => array(
      'administrator' => 'administrator',
      'root' => 'root',
    ),
    'module' => 'taxonomy_access_fix',
  );

  // Exported permission: 'add terms in tags'.
  $permissions['add terms in tags'] = array(
    'name' => 'add terms in tags',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'taxonomy_access_fix',
  );

  // Exported permission: 'add terms in type_de_media'.
  $permissions['add terms in type_de_media'] = array(
    'name' => 'add terms in type_de_media',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'taxonomy_access_fix',
  );

  // Exported permission: 'add terms in voc_type_voisin'.
  $permissions['add terms in voc_type_voisin'] = array(
    'name' => 'add terms in voc_type_voisin',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'taxonomy_access_fix',
  );

  // Exported permission: 'administer content type defaults'.
  $permissions['administer content type defaults'] = array(
    'name' => 'administer content type defaults',
    'roles' => array(),
    'module' => 'content_type_extras',
  );

  // Exported permission: 'administer content types'.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer dependencies'.
  $permissions['administer dependencies'] = array(
    'name' => 'administer dependencies',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'conditional_fields',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer taxonomy'.
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'administer workflow'.
  $permissions['administer workflow'] = array(
    'name' => 'administer workflow',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'workflow_admin_ui',
  );

  // Exported permission: 'bypass node access'.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete revisions'.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'root' => 'root',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in tags'.
  $permissions['delete terms in tags'] = array(
    'name' => 'delete terms in tags',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in type_de_media'.
  $permissions['delete terms in type_de_media'] = array(
    'name' => 'delete terms in type_de_media',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in voc_type_voisin'.
  $permissions['delete terms in voc_type_voisin'] = array(
    'name' => 'delete terms in voc_type_voisin',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in tags'.
  $permissions['edit terms in tags'] = array(
    'name' => 'edit terms in tags',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in type_de_media'.
  $permissions['edit terms in type_de_media'] = array(
    'name' => 'edit terms in type_de_media',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in voc_type_voisin'.
  $permissions['edit terms in voc_type_voisin'] = array(
    'name' => 'edit terms in voc_type_voisin',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'override content type title display'.
  $permissions['override content type title display'] = array(
    'name' => 'override content type title display',
    'roles' => array(),
    'module' => 'content_type_extras',
  );

  // Exported permission: 'participate in workflow'.
  $permissions['participate in workflow'] = array(
    'name' => 'participate in workflow',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'root' => 'root',
    ),
    'module' => 'workflow_admin_ui',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'root' => 'root',
    ),
    'module' => 'node',
  );

  // Exported permission: 'schedule workflow transitions'.
  $permissions['schedule workflow transitions'] = array(
    'name' => 'schedule workflow transitions',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'workflow',
  );

  // Exported permission: 'show workflow state form'.
  $permissions['show workflow state form'] = array(
    'name' => 'show workflow state form',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'workflow',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'administrator' => 'administrator',
      'root' => 'root',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'root' => 'root',
    ),
    'module' => 'node',
  );

  return $permissions;
}
