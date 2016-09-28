<?php

// Plugin definition
$plugin = array(
	'title' => t('[Article] [Aside]'),
	'category' => t('Columns: 2'),
	'icon' => 'html5-2-col.png',
	'theme' => 'panels_html5_2_col',
	'css' => 'html5-2-col.css',
	'regions' => array(
		'article' => t('Article'),
		'aside' => t('Aside'),
	),
);
