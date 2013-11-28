<?php
/**
 * @file
 * admin_views.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function admin_views_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_page';
  $strongarm->value = array();
  $export['menu_options_page'] = $strongarm;

  return $export;
}
