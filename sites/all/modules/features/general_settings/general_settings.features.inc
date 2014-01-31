<?php
/**
 * @file
 * general_settings.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function general_settings_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_workflow_default_workflows().
 */
function general_settings_workflow_default_workflows() {
  $workflows = array();

  // Exported workflow: Publication
  $workflows['Publication'] = array(
    'name' => 'Publication',
    'tab_roles' => '3,4',
    'options' => 'a:4:{s:16:"comment_log_node";s:1:"0";s:15:"comment_log_tab";s:1:"0";s:13:"name_as_title";s:1:"1";s:12:"watchdog_log";s:1:"0";}',
    'states' => array(
      0 => array(
        'state' => '(creation)',
        'weight' => -50,
        'sysid' => 1,
        'status' => 1,
        'name' => 'Publication',
      ),
      1 => array(
        'state' => 'Masqué',
        'weight' => -20,
        'sysid' => 0,
        'status' => 1,
        'name' => 'Publication',
      ),
      2 => array(
        'state' => 'Affiché',
        'weight' => -20,
        'sysid' => 0,
        'status' => 1,
        'name' => 'Publication',
      ),
    ),
    'transitions' => array(
      0 => array(
        'roles' => 'workflow_features_author_name,administrator,root',
        'state' => '(creation)',
        'target_state' => 'Masqué',
      ),
      1 => array(
        'roles' => 'workflow_features_author_name,administrator,root',
        'state' => '(creation)',
        'target_state' => 'Affiché',
      ),
      2 => array(
        'roles' => 'workflow_features_author_name,administrator,root',
        'state' => 'Masqué',
        'target_state' => 'Affiché',
      ),
      3 => array(
        'roles' => 'workflow_features_author_name,administrator,root',
        'state' => 'Affiché',
        'target_state' => 'Masqué',
      ),
    ),
    'node_types' => array(
      0 => 'page',
      1 => 'programme',
      2 => 'thematique',
      3 => 'voisin',
    ),
  );

  return $workflows;
}
