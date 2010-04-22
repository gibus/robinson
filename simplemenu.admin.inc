<?php
// $Id$

/**
 * @file
 * Settings of the simplemenu.
 */

/**
 * SimpleMenu settings page.
 */
function simplemenu_admin_settings() {
  // menu selection
  $form['default_menu'] = array(
    '#type' => 'fieldset',
    '#title' => t('Menu settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  if (module_exists('menu')) {
    $form['default_menu']['simplemenu_menu'] = array(
      '#type' => 'select',
      '#title' => t('Menu'),
      '#options' => menu_parent_options(menu_get_menus(), array( 'mlid' => 0 )), // return complete tree;
      '#default_value' => variable_get('simplemenu_menu', 'navigation:0'),
      '#description' => t('Select the menu to display.'),
    );
  }

  if (module_exists('devel')) {
    $form['default_menu']['simplemenu_devel'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add devel module links'),
      '#default_value' => variable_get('simplemenu_devel', 0),
      '#description' => t('Add devel module links for those users that can access the devel module.'),
    );
  }

  $form['default_menu']['simplemenu_theme'] = array(
    '#type' => 'select',
    '#title' => t('Theme'),
    '#options' => array(
      'original' => t('original'),
      'blackblue' => t('black & blue'),
      'custom' => t('custom'),
    ),
    '#default_value' => variable_get('simplemenu_theme', 'original'),
    '#description' => t('Select which theme to use. If you specify custom, you need to define CSS in your theme.'),
  );


  // standard settings
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Simplemenu settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['settings']['simplemenu_hide_delay'] = array(
    '#type' => 'textfield',
    '#title' => t('Hide delay'),
    '#size' => 4,
    '#default_value' => variable_get('simplemenu_hide_delay', 800),
    '#description' => t('How long (in milliseconds) should a menu still appear after losing focus.'),
  );

  $form['settings']['simplemenu_scroll_effect'] = array(
    '#type' => 'radios',
    '#title' => t('Scroll effect'),
    '#options' => array(
      'scroll' => t('Scroll with the page'),
      'fixed' => t('Fixed'),
    ),
    '#default_value' => variable_get('simplemenu_scroll_effect', 'scroll'),
    '#description' => t('Whether the menu scrolls with the page or stays at the top or bottom (this should only be used when the menu is attached to the &lt;body&gt; tag.)'),
  );

  $form['settings']['simplemenu_effect'] = array(
    '#type' => 'radios',
    '#title' => t('Show effect'),
    '#options' => array(
      'opacity' => t('Fade'),
      'height' => t('Slide'),
      'none' => t('None')
    ),
    '#default_value' => variable_get('simplemenu_effect', 'opacity'),
    '#description' => t('The effect used when displaying a menu.'),
  );

  $form['settings']['simplemenu_effect_speed'] = array(
    '#type' => 'radios',
    '#title' => t('Show speed'),
    '#options' => array('slow' => t('Slow'), 'medium' => t('Medium'), 'fast' => t('Fast')),
    '#default_value' => variable_get('simplemenu_effect_speed', 'fast'),
    '#description' => t('The speed of the effect, not used when "none" is set to show effect.'),
  );


  // advanced options
  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['advanced']['simplemenu_uid1'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show to User ID 1'),
    '#description' => t('Check this option to enable simplemenu for user 1 (superuser/administration). This is useful if you want to use a different menu (such as admin_menu) for the superuser/admin and simplemenu for others.'),
    '#default_value' => variable_get('simplemenu_uid1', 1),
  );

  $form['advanced']['simplemenu_element'] = array(
    '#type' => 'textfield',
    '#title' => t('CSS selector to attach menu to'),
    '#default_value' => variable_get('simplemenu_element', 'body'),
    '#description' => t('A valid CSS selector to attach the menu to. <em>Example: body, #primary, div.my-class</em>'),
    '#required' => TRUE,
  );

  $form['advanced']['simplemenu_element_method'] = array(
    '#type' => 'radios',
    '#title' => t('Attach method'),
    '#options' => array(
      'prepend' => t('Prepend'),
      'append' => t('Append'),
    ),
    '#default_value' => variable_get('simplemenu_element_method', 'prepend'),
    '#description' => t('Choose how the menu should be attached to the above selector.'),
    '#required' => TRUE,
  );

  // when someone has many themes, this list grows big!
  $themes = list_themes();
  $use_list = count($themes) > 15;
  $form['advanced']['simplemenu_exclusions'] = array(
    '#type' => $use_list ? 'select' : 'checkboxes',
    '#title' => t('Theme exclusions'),
    '#options' => drupal_map_assoc(array_keys($themes)),
    '#multiple' => $use_list,
    '#default_value' => variable_get('simplemenu_exclusions', array()),
    '#description' => t('Select which themes to <strong>not</strong> display the menu. Use this when you have a theme that displays its own admin navigation.'),
  );

  $form['advanced']['simplemenu_detect_popop'] = array(
    '#type' => 'checkbox',
    '#title' => t('Detect pop-up windows'),
    '#default_value' => variable_get('simplemenu_detect_popop', 1),
    '#description' => t("Choose whether SimpleMenu should attempt to detect if it is inside of a pop-up window.  If enabled, SimpleMenu will not display if it is inside of a pop-up window."),
  );

  $form['advanced']['simplemenu_visibility_operator'] = array(
    '#type' => 'radios',
    '#title' => t('Show block on specific pages'),
    '#default_value' => variable_get('simplemenu_visibility_operator', 0),
    '#options' => array(
      0 => t('Show on every page except the listed pages.'),
      1 => t('Show on only the listed pages.'),
    ),
  );

  $form['advanced']['simplemenu_visibility_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Pages'),
    '#default_value' => variable_get('simplemenu_visibility_pages', ''),
    '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.",
      array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
    '#wysiwyg' => FALSE,
  );

  return system_settings_form($form);
}


