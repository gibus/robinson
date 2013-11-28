<?php
/**
 * @file
 * admin_views.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function admin_views_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer menu'.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'menu',
  );

  // Exported permission: 'administer simplemenu'.
  $permissions['administer simplemenu'] = array(
    'name' => 'administer simplemenu',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'simplemenu',
  );

  // Exported permission: 'view simplemenu'.
  $permissions['view simplemenu'] = array(
    'name' => 'view simplemenu',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'simplemenu',
  );

  return $permissions;
}
