<?php
/**
 * @file
 * admin_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function admin_views_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'admin_contents';
  $view->description = 'Administrative view for content';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Admin Content';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Contenu';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'plus';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    4 => '4',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Filtrer';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'réinitialiser';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Trier par';
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Éléments par page';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Tout -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Décalage';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« premier';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ précédent';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'suivant ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'dernier »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'type' => 'title',
    'title' => 'title',
    'field_type_media' => 'title',
    'field_voisin_type' => 'title',
    'field_thema_date' => 'field_thema_date',
    'field_ref_thema' => 'field_ref_thema',
    'field_son' => 'field_son',
    'field_video' => 'field_son',
    'field_image' => 'field_son',
    'changed' => 'changed',
    'sid' => 'sid',
    'edit_node' => 'edit_node',
    'delete_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = 'changed';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '<br />',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '<br />',
      'empty_column' => 0,
    ),
    'field_type_media' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_voisin_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_thema_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ref_thema' => array(
      'align' => '',
      'separator' => '<br />',
      'empty_column' => 0,
    ),
    'field_son' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '<br />',
      'empty_column' => 0,
    ),
    'field_video' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_image' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = FALSE;
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Champ: Opérations en masse : Contenu */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::node_assign_owner_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::workflow_vbo_given_state_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::workflow_vbo_next_state_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::node_promote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_publish_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpromote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_save_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_by_keyword_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::pathauto_node_update_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Champ: Contenu : Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['type']['alter']['make_link'] = TRUE;
  /* Champ: Contenu : Titre */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<b>[type]</b> : [title]';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Champ: Champ : Type media */
  $handler->display->display_options['fields']['field_type_media']['id'] = 'field_type_media';
  $handler->display->display_options['fields']['field_type_media']['table'] = 'field_data_field_type_media';
  $handler->display->display_options['fields']['field_type_media']['field'] = 'field_type_media';
  $handler->display->display_options['fields']['field_type_media']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_type_media']['alter']['text'] = '<b>Media</b> : [field_type_media]';
  $handler->display->display_options['fields']['field_type_media']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_type_media']['type'] = 'taxonomy_term_reference_plain';
  /* Champ: Contenu : Comportement */
  $handler->display->display_options['fields']['field_voisin_type']['id'] = 'field_voisin_type';
  $handler->display->display_options['fields']['field_voisin_type']['table'] = 'field_data_field_voisin_type';
  $handler->display->display_options['fields']['field_voisin_type']['field'] = 'field_voisin_type';
  $handler->display->display_options['fields']['field_voisin_type']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_voisin_type']['alter']['text'] = '<b>Comportement</b> : [field_voisin_type]';
  $handler->display->display_options['fields']['field_voisin_type']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_voisin_type']['type'] = 'taxonomy_term_reference_plain';
  /* Champ: Contenu : Date de l'entretien  */
  $handler->display->display_options['fields']['field_thema_date']['id'] = 'field_thema_date';
  $handler->display->display_options['fields']['field_thema_date']['table'] = 'field_data_field_thema_date';
  $handler->display->display_options['fields']['field_thema_date']['field'] = 'field_thema_date';
  $handler->display->display_options['fields']['field_thema_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  /* Champ: Contenu : Est le voisin de  */
  $handler->display->display_options['fields']['field_ref_thema']['id'] = 'field_ref_thema';
  $handler->display->display_options['fields']['field_ref_thema']['table'] = 'field_data_field_ref_thema';
  $handler->display->display_options['fields']['field_ref_thema']['field'] = 'field_ref_thema';
  $handler->display->display_options['fields']['field_ref_thema']['label'] = 'Thématique(s)';
  $handler->display->display_options['fields']['field_ref_thema']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_ref_thema']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_ref_thema']['multi_type'] = 'ul';
  /* Champ: Contenu : Son */
  $handler->display->display_options['fields']['field_son']['id'] = 'field_son';
  $handler->display->display_options['fields']['field_son']['table'] = 'field_data_field_son';
  $handler->display->display_options['fields']['field_son']['field'] = 'field_son';
  $handler->display->display_options['fields']['field_son']['label'] = 'Son / Video / Image';
  $handler->display->display_options['fields']['field_son']['click_sort_column'] = 'url';
  /* Champ: Contenu : Vidéo de l'entretien */
  $handler->display->display_options['fields']['field_video']['id'] = 'field_video';
  $handler->display->display_options['fields']['field_video']['table'] = 'field_data_field_video';
  $handler->display->display_options['fields']['field_video']['field'] = 'field_video';
  $handler->display->display_options['fields']['field_video']['label'] = 'Vidéo';
  $handler->display->display_options['fields']['field_video']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_video']['alter']['text'] = '<a href="[field_video-video_url]">[field_video-video_url]</a>';
  $handler->display->display_options['fields']['field_video']['click_sort_column'] = 'video_url';
  $handler->display->display_options['fields']['field_video']['type'] = 'video_embed_field_thumbnail';
  $handler->display->display_options['fields']['field_video']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => '',
  );
  /* Champ: Contenu : image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_image']['delta_offset'] = '0';
  /* Champ: Contenu : Date de mise à jour */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  /* Champ: Processus : Current state */
  $handler->display->display_options['fields']['sid']['id'] = 'sid';
  $handler->display->display_options['fields']['sid']['table'] = 'workflow_node';
  $handler->display->display_options['fields']['sid']['field'] = 'sid';
  $handler->display->display_options['fields']['sid']['label'] = 'Publication';
  /* Champ: Contenu : Lien de modification */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['text'] = '<span class="node-edit">[edit_node]</span>';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['text'] = 'Modifier';
  /* Champ: Contenu : Lien de suppression */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['delete_node']['alter']['text'] = '<span class="node-delete">[delete_node]</span>';
  $handler->display->display_options['fields']['delete_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['delete_node']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['delete_node']['text'] = 'supprimer';
  /* Critère de filtrage: Contenu : Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'page' => 'page',
    'programme' => 'programme',
    'thematique' => 'thematique',
    'voisin' => 'voisin',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['type']['expose']['reduce'] = TRUE;
  /* Critère de filtrage: Global : Dependent filter */
  $handler->display->display_options['filters']['views_dependent_filter']['id'] = 'views_dependent_filter';
  $handler->display->display_options['filters']['views_dependent_filter']['table'] = 'views';
  $handler->display->display_options['filters']['views_dependent_filter']['field'] = 'views_dependent_filter';
  $handler->display->display_options['filters']['views_dependent_filter']['group'] = 1;
  $handler->display->display_options['filters']['views_dependent_filter']['controller_filter'] = 'type';
  $handler->display->display_options['filters']['views_dependent_filter']['controller_values'] = array(
    'voisin' => 'voisin',
    'page' => 0,
    'programme' => 0,
    'thematique' => 0,
  );
  $handler->display->display_options['filters']['views_dependent_filter']['dependent_filters'] = array(
    'field_type_media_tid' => 'field_type_media_tid',
    'field_voisin_type_tid' => 'field_voisin_type_tid',
    'sid' => 0,
  );
  /* Critère de filtrage: Champ : Type media (field_type_media) */
  $handler->display->display_options['filters']['field_type_media_tid']['id'] = 'field_type_media_tid';
  $handler->display->display_options['filters']['field_type_media_tid']['table'] = 'field_data_field_type_media';
  $handler->display->display_options['filters']['field_type_media_tid']['field'] = 'field_type_media_tid';
  $handler->display->display_options['filters']['field_type_media_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_type_media_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_type_media_tid']['expose']['operator_id'] = 'field_type_media_tid_op';
  $handler->display->display_options['filters']['field_type_media_tid']['expose']['label'] = 'Type de media';
  $handler->display->display_options['filters']['field_type_media_tid']['expose']['operator'] = 'field_type_media_tid_op';
  $handler->display->display_options['filters']['field_type_media_tid']['expose']['identifier'] = 'field_type_media_tid';
  $handler->display->display_options['filters']['field_type_media_tid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_type_media_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_type_media_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_type_media_tid']['vocabulary'] = 'type_de_media';
  /* Critère de filtrage: Contenu : Comportement (field_voisin_type) */
  $handler->display->display_options['filters']['field_voisin_type_tid']['id'] = 'field_voisin_type_tid';
  $handler->display->display_options['filters']['field_voisin_type_tid']['table'] = 'field_data_field_voisin_type';
  $handler->display->display_options['filters']['field_voisin_type_tid']['field'] = 'field_voisin_type_tid';
  $handler->display->display_options['filters']['field_voisin_type_tid']['value'] = '';
  $handler->display->display_options['filters']['field_voisin_type_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_voisin_type_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_voisin_type_tid']['expose']['operator_id'] = 'field_voisin_type_tid_op';
  $handler->display->display_options['filters']['field_voisin_type_tid']['expose']['label'] = 'Comportement';
  $handler->display->display_options['filters']['field_voisin_type_tid']['expose']['operator'] = 'field_voisin_type_tid_op';
  $handler->display->display_options['filters']['field_voisin_type_tid']['expose']['identifier'] = 'field_voisin_type_tid';
  $handler->display->display_options['filters']['field_voisin_type_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_voisin_type_tid']['group_info']['label'] = 'Type de voisin (field_voisin_type)';
  $handler->display->display_options['filters']['field_voisin_type_tid']['group_info']['identifier'] = 'field_voisin_type_tid';
  $handler->display->display_options['filters']['field_voisin_type_tid']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_voisin_type_tid']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  $handler->display->display_options['filters']['field_voisin_type_tid']['vocabulary'] = 'voc_type_voisin';
  /* Critère de filtrage: Processus : Current state */
  $handler->display->display_options['filters']['sid']['id'] = 'sid';
  $handler->display->display_options['filters']['sid']['table'] = 'workflow_node';
  $handler->display->display_options['filters']['sid']['field'] = 'sid';
  $handler->display->display_options['filters']['sid']['value'] = array(
    'all' => 'all',
    2 => '2',
    3 => '3',
  );
  $handler->display->display_options['filters']['sid']['group'] = 1;
  $handler->display->display_options['filters']['sid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['sid']['expose']['operator_id'] = 'sid_op';
  $handler->display->display_options['filters']['sid']['expose']['label'] = 'Publication';
  $handler->display->display_options['filters']['sid']['expose']['operator'] = 'sid_op';
  $handler->display->display_options['filters']['sid']['expose']['identifier'] = 'sid';
  $handler->display->display_options['filters']['sid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['sid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['sid']['expose']['reduce'] = TRUE;

  /* Display: Page : all */
  $handler = $view->new_display('page', 'Page : all', 'page');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Éléments par page';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Tout -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Décalage';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« premier';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ précédent';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'suivant ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'dernier »';
  $handler->display->display_options['path'] = 'admin/content/nodes';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Content';
  $handler->display->display_options['menu']['weight'] = '-100';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'dashboard';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Recent Content';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Champ: Contenu : Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['hide_alter_empty'] = FALSE;
  /* Champ: Contenu : Titre */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  /* Champ: Contenu : Lien de modification */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Modifier';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['text'] = '<span class="node-edit">[edit_node]</span>';
  $handler->display->display_options['fields']['edit_node']['hide_alter_empty'] = FALSE;
  /* Champ: Contenu : Publié */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['status']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Champ: Contenu : Langue */
  $handler->display->display_options['fields']['language']['id'] = 'language';
  $handler->display->display_options['fields']['language']['table'] = 'node';
  $handler->display->display_options['fields']['language']['field'] = 'language';
  $handler->display->display_options['fields']['language']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['language']['hide_alter_empty'] = FALSE;
  /* Champ: Traduction du contenu : Lien de traduction */
  $handler->display->display_options['fields']['translate_node']['id'] = 'translate_node';
  $handler->display->display_options['fields']['translate_node']['table'] = 'node';
  $handler->display->display_options['fields']['translate_node']['field'] = 'translate_node';
  $handler->display->display_options['fields']['translate_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['translate_node']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['translate_node']['text'] = 'Traduire';
  $translatables['admin_contents'] = array(
    t('Master'),
    t('Contenu'),
    t('plus'),
    t('Filtrer'),
    t('réinitialiser'),
    t('Trier par'),
    t('Asc'),
    t('Desc'),
    t('Éléments par page'),
    t('- Tout -'),
    t('Décalage'),
    t('« premier'),
    t('‹ précédent'),
    t('suivant ›'),
    t('dernier »'),
    t('Type'),
    t('Titre'),
    t('<b>[type]</b> : [title]'),
    t('Type media'),
    t('<b>Media</b> : [field_type_media]'),
    t('Comportement'),
    t('<b>Comportement</b> : [field_voisin_type]'),
    t('Date de l\'entretien '),
    t('Thématique(s)'),
    t('Son / Video / Image'),
    t('Vidéo'),
    t('<a href="[field_video-video_url]">[field_video-video_url]</a>'),
    t('Date de mise à jour'),
    t('Publication'),
    t('<span class="node-edit">[edit_node]</span>'),
    t('Modifier'),
    t('Lien de suppression'),
    t('<span class="node-delete">[delete_node]</span>'),
    t('supprimer'),
    t('Type de media'),
    t('Type de voisin (field_voisin_type)'),
    t('Page : all'),
    t('Block'),
    t('Recent Content'),
    t('Publié'),
    t('Langue'),
    t('Lien de traduction'),
    t('Traduire'),
  );
  $export['admin_contents'] = $view;

  return $export;
}
