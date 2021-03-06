<?php

if (module_exists('rdf')) {
  $vars['doctype'] = '<!DOCTYPE html PUBLIC "-//W3C//DTD HTML+RDFa 1.1//EN">' . "\n";
  $vars['rdf_profile'] = ' profile="' . $vars['grddl_profile'] . '"';
}
else {
  $vars['doctype'] = '<!DOCTYPE html>' . "\n";
  $vars['rdf_profile'] = '';
}


# Add mobile meta tags to $head ADD this to your subtheme
$heads = array();

$heads['HandheldFriendly'] = array(
  '#tag' => 'meta',
  '#attributes' => array(
    'name' => 'HandheldFriendly',
    'content' => 'true',
  ),
);



#  Mobile Viewport Fix
# j.mp/mobileviewport & davidbcalhoun.com/2010/viewport-metatag
# device-width : Occupy full width of the screen in its current orientation
# initial-scale = 1.0 retains dimensions instead of zooming out if page height > device height
# maximum-scale = 1.0 retains dimensions instead of zooming in if page width < device width

$heads['viewport'] = array(
  '#tag' => 'meta',
  '#attributes' => array(
    'name' => 'viewport',
    'content' => 'width=device-width,initial-scale=1',
  ),
);

foreach ($heads as $type=>$head)
	drupal_add_html_head($head, $type);


# add body classes
if(isset($vars['node'])){

	# from taxonomy
	foreach ($vars['node']->taxonomy as $tid => $term) {
		$vars['classes_array'][] = 'term-vid-'. $term->vid .' term-tid-'. $tid;
	}

}
