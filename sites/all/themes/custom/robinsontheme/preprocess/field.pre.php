<?php 

//dsm($vars);

$vars['theme_hook_suggestions'][] = 'field__' . $vars['element']['#view_mode'];
$vars['theme_hook_suggestions'][] = 'field__' . $vars['element']['#field_type'] . '__' . $vars['element']['#view_mode'];
$vars['theme_hook_suggestions'][] = 'field__' . $vars['element']['#field_name'] . '__' . $vars['element']['#view_mode'];

