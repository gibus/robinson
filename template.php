<?php
/**
 * Implementation of hook_theme().
 */
function guibik_theme() {
  $items = array();

  // Content theming.
  $items['help'] =
  $items['node'] =
  $items['comment'] =
  $items['comment_wrapper'] = array(
    'path' => drupal_get_path('theme', 'rubik') .'/templates',
    'template' => 'object',
  );
  $items['node']['template'] = 'node';

  // Help pages really need help. See preprocess_page().
  $items['help_page'] = array(
    'variables' => array('content' => array()),
    'path' => drupal_get_path('theme', 'rubik') .'/templates',
    'template' => 'object',
    'preprocess functions' => array(
      'template_preprocess',
      'rubik_preprocess_help_page',
    ),
    'process functions' => array('template_process'),
  );

  // Form layout: default (2 column).
  $items['block_add_block_form'] =
  $items['block_admin_configure'] =
  $items['comment_form'] =
  $items['contact_admin_edit'] =
  $items['contact_mail_page'] =
  $items['contact_mail_user'] =
  $items['filter_admin_format_form'] =
  $items['forum_form'] =
  $items['locale_languages_edit_form'] =
  $items['menu_edit_menu'] =
  $items['menu_edit_item'] =
  $items['node_type_form'] =
  $items['path_admin_form'] =
  $items['system_settings_form'] =
  $items['system_themes_form'] =
  $items['system_modules'] =
  $items['system_actions_configure'] =
  $items['taxonomy_form_term'] =
  $items['taxonomy_form_vocabulary'] =
  $items['user_profile_form'] =
  $items['user_admin_access_add_form'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'guibik') .'/templates',
    'template' => 'form-default',
    'preprocess functions' => array(
      'rubik_preprocess_form_buttons',
    ),
  );

  // These forms require additional massaging.
  $items['confirm_form'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'rubik') .'/templates',
    'template' => 'form-simple',
    'preprocess functions' => array(
      'rubik_preprocess_form_confirm'
    ),
  );
  $items['node_form'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'guibik') .'/templates',
    'template' => 'form-default',
    'preprocess functions' => array(
      'rubik_preprocess_form_buttons',
      'rubik_preprocess_form_node',
    ),
  );

  return $items;
}



/**
 * Preprocessor for theme('page').
 */
function guibik_preprocess_page(&$vars) {
  // Show a warning if base theme is not present.
  if (!function_exists('rubik_theme') && user_access('administer site configuration')) {
    drupal_set_message(t('The Guibik theme requires the !rubik base theme in order to work properly.', array('!rubik' => l('Rubik', 'http://code.developmentseed.org/tao'))), 'warning');
  }

  // Process local tasks. Only do this processing if the current theme is
  // indeed Rubik. Subthemes must reimplement this call.
  global $theme;
  if ($theme === 'guibik')
    _rubik_local_tasks($vars);
	
}

function guibik_preprocess_html(&$vars){
	
	$heads['icon'] = array(
	  '#tag' => 'link',
	  '#attributes' => array(
	    'href' => base_path() . path_to_theme() .'/icon.png', 
	    'rel' => 'shortcut icon',
	    'type' => 'image/png',
	  ),
	);
	
	
	$heads['apple-touch-icon'] = array(
	  '#tag' => 'link',
	  '#attributes' => array(
	    'href' => base_path() . path_to_theme() .'/apple-touch-icon.png', 
	    'rel' => 'apple-touch-icon',
	  ),
	);

	foreach ($heads as $type=>$head)
		drupal_add_html_head($head, $type);
	
	
}
