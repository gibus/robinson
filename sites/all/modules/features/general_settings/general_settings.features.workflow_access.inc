<?php
/**
 * @file
 * general_settings.features.workflow_access.inc
 */

/**
 * Implements hook_workflow_access_features_default_settings().
 */
function general_settings_workflow_access_features_default_settings() {
  $workflows = array();

  $workflows['Publication'] = array();
  $workflows['Publication']['Masqué'] = array();
  $workflows['Publication']['Masqué']['administrator'] = array(
    'grant_view' => 1,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['Publication']['Masqué']['root'] = array(
    'grant_view' => 1,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['Publication']['Masqué']['workflow_features_author_name'] = array(
    'grant_view' => 1,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['Publication']['Masqué']['anonymous user'] = array(
    'grant_view' => 0,
    'grant_update' => 0,
    'grant_delete' => 0,
  );
  $workflows['Publication']['Masqué']['authenticated user'] = array(
    'grant_view' => 0,
    'grant_update' => 0,
    'grant_delete' => 0,
  );
  $workflows['Publication']['Affiché'] = array();
  $workflows['Publication']['Affiché']['anonymous user'] = array(
    'grant_view' => 1,
    'grant_update' => 0,
    'grant_delete' => 0,
  );
  $workflows['Publication']['Affiché']['authenticated user'] = array(
    'grant_view' => 1,
    'grant_update' => 0,
    'grant_delete' => 0,
  );
  $workflows['Publication']['Affiché']['administrator'] = array(
    'grant_view' => 0,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['Publication']['Affiché']['root'] = array(
    'grant_view' => 0,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['Publication']['Affiché']['workflow_features_author_name'] = array(
    'grant_view' => 0,
    'grant_update' => 1,
    'grant_delete' => 1,
  );

  return $workflows;
}
