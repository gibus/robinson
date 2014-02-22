<?php
/**
 * @file
 * general_settings.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function general_settings_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'taxonomy_term-comportement-field_discursif'
  $field_instances['taxonomy_term-comportement-field_discursif'] = array(
    'bundle' => 'comportement',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_discursif',
    'label' => 'Discursif',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'taxonomy_term-comportement-field_duree_mini'
  $field_instances['taxonomy_term-comportement-field_duree_mini'] = array(
    'bundle' => 'comportement',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'hms_field',
        'settings' => array(
          'format' => 'h:mm',
          'leading_zero' => TRUE,
        ),
        'type' => 'hms_default_formatter',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_duree_mini',
    'label' => 'Durée mini',
    'required' => 0,
    'settings' => array(
      'default_description' => 1,
      'format' => 'h:mm',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'hms_field',
      'settings' => array(),
      'type' => 'hms_default_widget',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'taxonomy_term-comportement-field_post_pause'
  $field_instances['taxonomy_term-comportement-field_post_pause'] = array(
    'bundle' => 'comportement',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'hms_field',
        'settings' => array(
          'format' => 'h:mm',
          'leading_zero' => TRUE,
        ),
        'type' => 'hms_default_formatter',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_post_pause',
    'label' => 'Attente en fin de diffusion ( min — max )',
    'required' => 0,
    'settings' => array(
      'default_description' => 1,
      'format' => 'h:mm',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'hms_field',
      'settings' => array(),
      'type' => 'hms_default_widget',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'taxonomy_term-comportement-field_proba'
  $field_instances['taxonomy_term-comportement-field_proba'] = array(
    'bundle' => 'comportement',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_proba',
    'label' => 'Fréquence d\'apparition',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'taxonomy_term-comportement-field_taille'
  $field_instances['taxonomy_term-comportement-field_taille'] = array(
    'bundle' => 'comportement',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_taille',
    'label' => 'Taille ( mini — maxi )',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'taxonomy_term-comportement-field_type_media'
  $field_instances['taxonomy_term-comportement-field_type_media'] = array(
    'bundle' => 'comportement',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'i18n_taxonomy',
        'settings' => array(),
        'type' => 'i18n_taxonomy_term_reference_link',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_type_media',
    'label' => 'Type media',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Attente en fin de diffusion ( min — max )');
  t('Discursif');
  t('Durée mini');
  t('Fréquence d\'apparition');
  t('Taille ( mini — maxi )');
  t('Type media');

  return $field_instances;
}
