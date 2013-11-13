<?php

/**
 * @file
 * Definition of the 'default' panel style.
 */

// Plugin definition
$plugin = array(
  'title' => t('Minimum HTML'),
  'description' => t('The default panel rendering style; without separator.'),
  'render pane' => 'panels_minimum_style_render_pane',
  'render region' => 'panels_minimum_style_render_region',
);

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_panels_minimum_style_render_pane($vars) {
	return render($vars['content']->content);
}


function theme_panels_minimum_style_render_region($vars) {
	return implode($vars['panes']);
}

