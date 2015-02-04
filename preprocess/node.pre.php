<?php

// dsm("3");
// dsm($vars);

if ($vars["is_front"])
  $vars["theme_hook_suggestions"][] = "node__front";

$vars['theme_hook_suggestions'][] = 'node__'.$vars['view_mode'];
$vars['theme_hook_suggestions'][] = 'node__' . $vars['type'] . '__' . $vars['view_mode'];
$vars['classes_array'][] = 'view-mode-' . $vars['view_mode'];