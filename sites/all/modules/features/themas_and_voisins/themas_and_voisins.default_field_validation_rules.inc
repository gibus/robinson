<?php
/**
 * @file
 * themas_and_voisins.default_field_validation_rules.inc
 */

/**
 * Implements hook_default_field_validation_rule().
 */
function themas_and_voisins_default_field_validation_rule() {
  $export = array();

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'match durée min/max pattern';
  $rule->name = 'match_dur_e_min_max_pattern';
  $rule->field_name = 'field_duree_sec_minmax';
  $rule->col = 'value';
  $rule->entity_type = 'taxonomy_term';
  $rule->bundle = 'comportement';
  $rule->validator = 'field_validation_pcre_validator';
  $rule->settings = array(
    'data' => '/\\d{1,3}\\/\\d{1,3}/',
    'bypass' => 0,
    'roles' => array(
      1 => 0,
      2 => 0,
      3 => 0,
      4 => 0,
    ),
    'errors' => 1,
  );
  $rule->error_message = 'Durée doit etre de la forme min/max. ex : 10/300 ou 200/786 (max : 999)';
  $export['match_dur_e_min_max_pattern'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'match taille min/max pattern';
  $rule->name = 'match_taille_min_max_pattern';
  $rule->field_name = 'field_taille_minmax';
  $rule->col = 'value';
  $rule->entity_type = 'taxonomy_term';
  $rule->bundle = 'comportement';
  $rule->validator = 'field_validation_pcre_validator';
  $rule->settings = array(
    'data' => '/[1-3]\\/[1-3]/',
    'bypass' => 0,
    'roles' => array(
      1 => 0,
      2 => 0,
      3 => 0,
      4 => 0,
    ),
    'errors' => 1,
  );
  $rule->error_message = 'Taille doit etre de la forme min/max. ex:1/3 ou 3/3';
  $export['match_taille_min_max_pattern'] = $rule;

  return $export;
}
