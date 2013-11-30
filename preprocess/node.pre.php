<?php 

// dsm($vars);

$vars['theme_hook_suggestions'][] = 'node__'.$vars['view_mode'];
$vars['theme_hook_suggestions'][] = 'node__' . $vars['type'] . '__' . $vars['view_mode'];

