<?php

// Plugin definition
$plugin = array(
	'title' => t('[Nav] [Article] [Aside]'),
	'category' => t('Columns: 2'),
	'icon' => 'html5-custom.png',
	'theme' => 'panels_html5_custom',
	'css' => 'html5-custom.css',
	'regions' => array(
		'nav' => t('Nav'),
		'article' => t('Article'),
		'aside-nav' => t('Aside >  Nav'),
		'aside-content' => t('Aside > Content'),
	),
);
