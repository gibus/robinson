<?php
/**
 * @file
 * general_settings.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function general_settings_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  // Exported role: anonymous user.
  $roles['anonymous user'] = array(
    'name' => 'anonymous user',
    'weight' => 0,
  );

  // Exported role: authenticated user.
  $roles['authenticated user'] = array(
    'name' => 'authenticated user',
    'weight' => 1,
  );

  // Exported role: root.
  $roles['root'] = array(
    'name' => 'root',
    'weight' => 3,
  );

  return $roles;
}
