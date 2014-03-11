<?php
/**
 * @file
 * themas_and_voisins.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function themas_and_voisins_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_thematique';
  $strongarm->value = 'edit-submission';
  $export['additional_settings__active_tab_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_voisin';
  $strongarm->value = 'edit-submission';
  $export['additional_settings__active_tab_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_pattern_thematique';
  $strongarm->value = '';
  $export['ant_pattern_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_php_thematique';
  $strongarm->value = 0;
  $export['ant_php_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_thematique';
  $strongarm->value = '0';
  $export['ant_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_cancel_thematique';
  $strongarm->value = '0';
  $export['content_type_extras_cancel_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_cancel_voisin';
  $strongarm->value = '0';
  $export['content_type_extras_cancel_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_preview_button_thematique';
  $strongarm->value = 'Aperçu';
  $export['content_type_extras_preview_button_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_preview_button_voisin';
  $strongarm->value = 'Aperçu';
  $export['content_type_extras_preview_button_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_remove_body_thematique';
  $strongarm->value = 0;
  $export['content_type_extras_remove_body_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_remove_body_voisin';
  $strongarm->value = 1;
  $export['content_type_extras_remove_body_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_save_and_edit_button_thematique';
  $strongarm->value = 'Save and Edit';
  $export['content_type_extras_save_and_edit_button_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_save_and_edit_button_voisin';
  $strongarm->value = 'Save and Edit';
  $export['content_type_extras_save_and_edit_button_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_save_and_edit_thematique';
  $strongarm->value = '0';
  $export['content_type_extras_save_and_edit_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_save_and_edit_voisin';
  $strongarm->value = '0';
  $export['content_type_extras_save_and_edit_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_save_and_new_button_thematique';
  $strongarm->value = 'Enregistrer et Nouveau';
  $export['content_type_extras_save_and_new_button_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_save_and_new_button_voisin';
  $strongarm->value = 'Enregistrer et Nouveau';
  $export['content_type_extras_save_and_new_button_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_save_and_new_thematique';
  $strongarm->value = '1';
  $export['content_type_extras_save_and_new_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_save_and_new_voisin';
  $strongarm->value = '1';
  $export['content_type_extras_save_and_new_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_title_hide_thematique';
  $strongarm->value = 0;
  $export['content_type_extras_title_hide_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_type_extras_title_hide_voisin';
  $strongarm->value = 0;
  $export['content_type_extras_title_hide_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'default_field_group';
  $strongarm->value = array(
    'group_contenu|node|voisin|form' => TRUE,
    'group_annexes|node|voisin|form' => FALSE,
    'group_media|node|voisin|form' => FALSE,
    'group_htabs|node|voisin|form' => FALSE,
    'group_htabs|taxonomy_term|voc_type_voisin|form' => FALSE,
    'group_general|taxonomy_term|voc_type_voisin|form' => FALSE,
    'group_tailles_et_positions|taxonomy_term|voc_type_voisin|form' => FALSE,
    'group_temps|taxonomy_term|voc_type_voisin|form' => FALSE,
    'group_divers|taxonomy_term|voc_type_voisin|form' => FALSE,
    'group_htabs|node|programme|form' => FALSE,
    'group_sequence|node|programme|form' => FALSE,
    'group_dates|node|programme|form' => FALSE,
  );
  $export['default_field_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__thematique';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '6',
        ),
        'workflow' => array(
          'weight' => '7',
        ),
      ),
      'display' => array(
        'workflow_current_state' => array(
          'stream' => array(
            'weight' => '5',
            'visible' => FALSE,
          ),
        ),
        'workflow' => array(
          'stream' => array(
            'weight' => '4',
            'visible' => FALSE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_node__thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__voisin';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
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
      'stream' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_atmosphere' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_contrib_image' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_contrib_son' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_contrib_txt' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_contrib_video' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_danse_son' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_danse_video' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_lettrage_image' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_lettrage_video' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_nature' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_audio' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_video' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_image' => array(
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
      'voisin_contrib_audio' => array(
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
      'voisin_image_t1' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_image_t2' => array(
        'custom_settings' => TRUE,
      ),
      'voisin_image_t3' => array(
        'custom_settings' => TRUE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '5',
        ),
        'workflow' => array(
          'weight' => '4',
        ),
      ),
      'display' => array(
        'workflow_current_state' => array(
          'voisin_video' => array(
            'weight' => '-99',
            'visible' => FALSE,
          ),
          'voisin_audio' => array(
            'weight' => '-99',
            'visible' => FALSE,
          ),
          'voisin_image' => array(
            'weight' => '-99',
            'visible' => FALSE,
          ),
          'voisin_text' => array(
            'weight' => '-99',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '7',
            'visible' => FALSE,
          ),
          'voisin_video_t1' => array(
            'weight' => '-99',
            'visible' => FALSE,
          ),
          'voisin_video_t2' => array(
            'weight' => '-99',
            'visible' => FALSE,
          ),
          'voisin_video_t3' => array(
            'weight' => '-99',
            'visible' => FALSE,
          ),
          'voisin_image_t1' => array(
            'weight' => '-99',
            'visible' => FALSE,
          ),
          'voisin_image_t2' => array(
            'weight' => '-99',
            'visible' => FALSE,
          ),
          'voisin_image_t3' => array(
            'weight' => '-99',
            'visible' => FALSE,
          ),
          'voisin_video_t1_16_9' => array(
            'weight' => '-99',
            'visible' => FALSE,
          ),
          'voisin_video_t2_16_9' => array(
            'weight' => '-99',
            'visible' => FALSE,
          ),
          'voisin_video_t3_16_9' => array(
            'weight' => '-99',
            'visible' => FALSE,
          ),
          'voisin_video_t1_4_3' => array(
            'weight' => '-99',
            'visible' => FALSE,
          ),
          'voisin_video_t2_4_3' => array(
            'weight' => '-99',
            'visible' => FALSE,
          ),
          'voisin_video_t3_4_3' => array(
            'weight' => '-99',
            'visible' => FALSE,
          ),
        ),
        'workflow' => array(
          'voisin_video' => array(
            'weight' => '99',
            'visible' => FALSE,
          ),
          'voisin_audio' => array(
            'weight' => '99',
            'visible' => FALSE,
          ),
          'voisin_image' => array(
            'weight' => '99',
            'visible' => FALSE,
          ),
          'voisin_text' => array(
            'weight' => '99',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '10',
            'visible' => FALSE,
          ),
          'voisin_video_t1' => array(
            'weight' => '99',
            'visible' => FALSE,
          ),
          'voisin_video_t2' => array(
            'weight' => '99',
            'visible' => FALSE,
          ),
          'voisin_video_t3' => array(
            'weight' => '99',
            'visible' => FALSE,
          ),
          'voisin_image_t1' => array(
            'weight' => '99',
            'visible' => FALSE,
          ),
          'voisin_image_t2' => array(
            'weight' => '99',
            'visible' => FALSE,
          ),
          'voisin_image_t3' => array(
            'weight' => '99',
            'visible' => FALSE,
          ),
          'voisin_video_t1_16_9' => array(
            'weight' => '99',
            'visible' => FALSE,
          ),
          'voisin_video_t2_16_9' => array(
            'weight' => '99',
            'visible' => FALSE,
          ),
          'voisin_video_t3_16_9' => array(
            'weight' => '99',
            'visible' => FALSE,
          ),
          'voisin_video_t1_4_3' => array(
            'weight' => '99',
            'visible' => FALSE,
          ),
          'voisin_video_t2_4_3' => array(
            'weight' => '99',
            'visible' => FALSE,
          ),
          'voisin_video_t3_4_3' => array(
            'weight' => '99',
            'visible' => FALSE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_node__voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_node_extended_voisin';
  $strongarm->value = 1;
  $export['i18n_node_extended_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_node_options_voisin';
  $strongarm->value = array();
  $export['i18n_node_options_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_thematique';
  $strongarm->value = '0';
  $export['language_content_type_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_voisin';
  $strongarm->value = '0';
  $export['language_content_type_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_thematique';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_voisin';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_thematique';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_voisin';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nodeformscols_field_placements_thematique_default';
  $strongarm->value = array(
    'title' => array(
      'region' => 'main',
      'weight' => '0',
      'has_required' => TRUE,
      'title' => 'Titre',
    ),
    'additional_settings' => array(
      'region' => 'main',
      'weight' => '4',
      'has_required' => FALSE,
      'title' => 'Vertical tabs',
      'hidden' => 0,
    ),
    'actions' => array(
      'region' => 'right',
      'weight' => '2',
      'has_required' => FALSE,
      'title' => 'Save',
      'hidden' => 0,
    ),
    'field_thema_date' => array(
      'region' => 'right',
      'weight' => '0',
      'has_required' => FALSE,
      'title' => 'Date de l&#039;entretien ',
      'hidden' => 0,
    ),
    'field_video' => array(
      'region' => 'main',
      'weight' => '2',
      'has_required' => FALSE,
      'title' => 'Vidéo de l&#039;entretien',
      'hidden' => 0,
    ),
    'field_ref_voisin' => array(
      'region' => 'main',
      'weight' => '3',
      'has_required' => FALSE,
      'title' => 'Voisins',
      'hidden' => 0,
    ),
    'field_titre__lettrage_' => array(
      'region' => 'main',
      'weight' => '1',
      'has_required' => FALSE,
      'title' => 'Titre video ( lettrage )',
      'hidden' => 0,
    ),
    'title_field' => array(
      'region' => 'main',
      'weight' => '-5',
      'has_required' => TRUE,
      'title' => 'Title',
    ),
    'workflow' => array(
      'region' => 'right',
      'weight' => '1',
      'has_required' => FALSE,
      'title' => 'Change Publication state',
      'hidden' => 0,
    ),
  );
  $export['nodeformscols_field_placements_thematique_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nodeformscols_field_placements_voisin_default';
  $strongarm->value = array(
    'title' => array(
      'region' => 'main',
      'weight' => '0',
      'has_required' => TRUE,
      'title' => 'Titre',
    ),
    'additional_settings' => array(
      'region' => 'footer',
      'weight' => '1',
      'has_required' => FALSE,
      'title' => 'Vertical tabs',
      'hidden' => 0,
    ),
    'actions' => array(
      'region' => 'right',
      'weight' => '5',
      'has_required' => FALSE,
      'title' => 'Enregistrer',
      'hidden' => 0,
    ),
    'field_voisin_type' => array(
      'region' => 'footer',
      'weight' => '0',
      'has_required' => TRUE,
      'title' => 'Type de voisin (deprecated)',
      'hidden' => 0,
    ),
    'field_voisin_credit' => array(
      'region' => 'right',
      'weight' => '3',
      'has_required' => FALSE,
      'title' => 'Crédits',
      'hidden' => 0,
    ),
    'field_video' => array(
      'region' => 'main',
      'weight' => '3',
      'has_required' => FALSE,
      'title' => 'Video',
      'hidden' => 0,
    ),
    'field_son' => array(
      'region' => 'main',
      'weight' => '5',
      'has_required' => FALSE,
      'title' => 'Son',
      'hidden' => 0,
    ),
    'field_image' => array(
      'region' => 'main',
      'weight' => '4',
      'has_required' => FALSE,
      'title' => 'image',
      'hidden' => 0,
    ),
    'field_ref_thema' => array(
      'region' => 'right',
      'weight' => '2',
      'has_required' => FALSE,
      'title' => 'Est le voisin de ',
      'hidden' => 0,
    ),
    'field_texte' => array(
      'region' => 'main',
      'weight' => '6',
      'has_required' => FALSE,
      'title' => 'Citation',
      'hidden' => 0,
    ),
    'field_type_media' => array(
      'region' => 'main',
      'weight' => '1',
      'has_required' => TRUE,
      'title' => 'Type media',
    ),
    'workflow' => array(
      'region' => 'right',
      'weight' => '4',
      'has_required' => FALSE,
      'title' => 'Change Publication state',
      'hidden' => 0,
    ),
    'field_comportement' => array(
      'region' => 'right',
      'weight' => '0',
      'has_required' => FALSE,
      'title' => 'Comportement',
      'hidden' => 0,
    ),
  );
  $export['nodeformscols_field_placements_voisin_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_thematique';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_voisin';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_thematique';
  $strongarm->value = '0';
  $export['node_preview_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_voisin';
  $strongarm->value = '0';
  $export['node_preview_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_thematique';
  $strongarm->value = 0;
  $export['node_submitted_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_voisin';
  $strongarm->value = 0;
  $export['node_submitted_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'save_continue_thematique';
  $strongarm->value = 'Enregistrer et ajouter les champs';
  $export['save_continue_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'save_continue_voisin';
  $strongarm->value = 'Enregistrer et ajouter les champs';
  $export['save_continue_voisin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_permissions_thematique';
  $strongarm->value = array(
    0 => 'create_roles',
    1 => 'edit_roles',
    2 => 'delete_roles',
  );
  $export['user_permissions_thematique'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_permissions_voisin';
  $strongarm->value = array(
    0 => 'create_roles',
    1 => 'edit_roles',
    2 => 'delete_roles',
  );
  $export['user_permissions_voisin'] = $strongarm;

  return $export;
}
