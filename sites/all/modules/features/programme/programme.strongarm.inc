<?php
/**
 * @file
 * programme.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function programme_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_programme';
  $strongarm->value = 'edit-extras';
  $export['additional_settings__active_tab_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_pattern_programme';
  $strongarm->value = '';
  $export['ant_pattern_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_php_programme';
  $strongarm->value = 0;
  $export['ant_php_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_programme';
  $strongarm->value = '0';
  $export['ant_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_cancel_programme';
  $strongarm->value = '0';
  $export['content_type_extras_cancel_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_preview_button_programme';
  $strongarm->value = 'Aperçu';
  $export['content_type_extras_preview_button_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_remove_body_programme';
  $strongarm->value = 1;
  $export['content_type_extras_remove_body_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_save_and_edit_button_programme';
  $strongarm->value = 'Save and Edit';
  $export['content_type_extras_save_and_edit_button_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_save_and_edit_programme';
  $strongarm->value = '0';
  $export['content_type_extras_save_and_edit_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_save_and_new_button_programme';
  $strongarm->value = 'Save and New';
  $export['content_type_extras_save_and_new_button_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_save_and_new_programme';
  $strongarm->value = '0';
  $export['content_type_extras_save_and_new_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_title_hide_programme';
  $strongarm->value = 0;
  $export['content_type_extras_title_hide_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__programme';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'stream' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_audio' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_video' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_video_t1_16_9' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_video_t2_16_9' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_video_t3_16_9' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_video_t1_4_3' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_video_t2_4_3' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_video_t3_4_3' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_video_t1' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_video_t2' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_video_t3' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_image' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_image_t1' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_image_t2' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_image_t3' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_text' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_atmosphere_audio' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_atmosphere_video' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_atmosphere_image' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_discursif' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_contrib_txt' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_contrib_video' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_contrib_audio' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_contrib_image' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '2',
        ),
        'workflow' => array(
          'weight' => '4',
        ),
      ),
      'display' => array(
        'workflow_current_state' => array(
          'default' => array(
            'weight' => '-99',
            'visible' => FALSE,
          ),
        ),
        'workflow' => array(
          'default' => array(
            'weight' => '99',
            'visible' => FALSE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_node__programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_programme';
  $strongarm->value = '0';
  $export['language_content_type_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_programme';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_programme';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nodeformscols_field_placements_programme_default';
  $strongarm->value = array(
    'title' => array(
      'region' => 'main',
      'weight' => '0',
      'has_required' => TRUE,
      'title' => 'Titre',
    ),
    'additional_settings' => array(
      'region' => 'main',
      'weight' => '3',
      'has_required' => FALSE,
      'title' => 'Vertical tabs',
      'hidden' => 0,
    ),
    'actions' => array(
      'region' => 'right',
      'weight' => '2',
      'has_required' => FALSE,
      'title' => 'Enregistrer',
      'hidden' => 0,
    ),
    'field_prog_plage' => array(
      'region' => 'main',
      'weight' => '1',
      'has_required' => FALSE,
      'title' => 'Plage du programme',
      'hidden' => 0,
    ),
    'field_prog_element' => array(
      'region' => 'main',
      'weight' => '2',
      'has_required' => FALSE,
      'title' => 'Séquences',
      'hidden' => 0,
    ),
    'field_memo' => array(
      'region' => 'right',
      'weight' => '0',
      'has_required' => FALSE,
      'title' => 'Mémo',
      'hidden' => 0,
    ),
    'workflow' => array(
      'region' => 'right',
      'weight' => '1',
      'has_required' => FALSE,
      'title' => 'Change Publication state',
      'hidden' => 0,
    ),
  );
  $export['nodeformscols_field_placements_programme_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_programme';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_programme';
  $strongarm->value = '0';
  $export['node_preview_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_programme';
  $strongarm->value = 1;
  $export['node_submitted_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'save_continue_programme';
  $strongarm->value = 'Enregistrer et ajouter les champs';
  $export['save_continue_programme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_permissions_programme';
  $strongarm->value = array(
    0 => 'create_roles',
    1 => 'edit_roles',
    2 => 'delete_roles',
  );
  $export['user_permissions_programme'] = $strongarm;

  return $export;
}
