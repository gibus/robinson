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

  // Exported permission: 'access workflow summary views'.
  $permissions['access workflow summary views'] = array(
    'name' => 'access workflow summary views',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'workflow_views',
  );

  // Exported permission: 'administer workflow'.
  $permissions['administer workflow'] = array(
    'name' => 'administer workflow',
    'roles' => array(
      'root' => 'root',
    ),
    'module' => 'workflow_admin_ui',
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

  return $permissions;
}
