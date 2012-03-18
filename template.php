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

/**
 * Implements theme_form_element().
 */
function OUT_guibik_form_element($variables) {
  $element = &$variables['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();
	
	dsm($element);

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
	if(!isset($element["#attributes"]['class']))
		$element["#attributes"]['class'] = array();
		
	$attributes['class'] = $element["#attributes"]['class'] + array('form-item');
  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= '<div class="description">' . $element['#description'] . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}



function guibik_form_node_form_alter(&$form, &$form_state){
	// dsm($form, 'guibik_form_node_form_alter | $form');
	// dsm($form_state, '$form_state');
	
	if(!isset($form['language']['#description']))
		$form['language']['#description'] = t('Please consider to leave language in neutral state <strong>if you dont plan to translate this node</strong>, even if your content is (obviously) writed in some non neutral language. Then this node will always be visible.');
	
}

