<?php
/**
 * @file
 * themas_and_voisins.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function themas_and_voisins_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create voisin content'.
  $permissions['create voisin content'] = array(
    'name' => 'create voisin content',
    'roles' => array(
      'administrator' => 'administrator',
      'root' => 'root',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any voisin content'.
  $permissions['delete any voisin content'] = array(
    'name' => 'delete any voisin content',
    'roles' => array(
      'administrator' => 'administrator',
      'root' => 'root',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own voisin content'.
  $permissions['delete own voisin content'] = array(
    'name' => 'delete own voisin content',
    'roles' => array(
      'administrator' => 'administrator',
      'root' => 'root',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any voisin content'.
  $permissions['edit any voisin content'] = array(
    'name' => 'edit any voisin content',
    'roles' => array(
      'administrator' => 'administrator',
      'root' => 'root',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own voisin content'.
  $permissions['edit own voisin content'] = array(
    'name' => 'edit own voisin content',
    'roles' => array(
      'administrator' => 'administrator',
      'root' => 'root',
    ),
    'module' => 'node',
  );

  return $permissions;
}
