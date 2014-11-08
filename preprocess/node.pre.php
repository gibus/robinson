<?php

dsm("2");
dsm($vars);

$vars['theme_hook_suggestions'][] = 'node__'.$vars['view_mode'];
$vars['theme_hook_suggestions'][] = 'node__' . $vars['type'] . '__' . $vars['view_mode'];
$vars['classes_array'][] = 'view-mode-' . $vars['view_mode'];
$vars['content_classes'] = "";

// if ( $vars['type'] == "voisin" ) {
//   $vars['classes_array'][] = 'row';
// }

// $gridColumnsBootstrap = 12;
// $gridColumnsSm = 3;
// $gridColumnsMd = 4;
// $gridColumnsLg = 6;
// $ratioSm = $gridColumnsBootstrap/$gridColumnsSm;
// $ratioMd = $gridColumnsBootstrap/$gridColumnsMd;
// $ratioLg = $gridColumnsBootstrap/$gridColumnsLg;
// $col = null;

// switch ($vars['view_mode']) {
//   case 'voisin_text':
//   case 'voisin_image_t1':
//   case 'voisin_video_t1':
//     $col = 1;
//     break;
//   case 'voisin_image_t2':
//   case 'voisin_video_t2':
//     $col = 2;
//     break;
//   case 'voisin_image_t3':
//   case 'voisin_video_t3':
//     $col = 3;
//     break;
//   case 'voisin_audio':
//     $vars['content_classes'] = 'hidden';
//     break;
// }

// if ($col != null && $col < 3) {

//   $colSm  = $col * $ratioSm;
//   $offset = $ratioSm * mt_rand(1, ($gridColumnsSm-$col));
//   $content_classes[] = 'col-sm-offset-'.$offset;
//   $content_classes[] = 'col-sm-'.$colSm;

//   $colMd  = $col * $ratioMd;
//   $offset = $ratioMd * mt_rand(1, ($gridColumnsMd-$col));
//   $content_classes[] = 'col-md-offset-'.$offset;
//   $content_classes[] = 'col-md-'.$colMd;

//   $colLg  = $col * $ratioLg;
//   $offset = $ratioLg * mt_rand(1, ($gridColumnsLg-$col));
//   $content_classes[] = 'col-lg-offset-'.$offset;
//   $content_classes[] = 'col-lg-'.$colLg;

//   $vars['content_classes'] = implode(' ', $content_classes);
// }else if( $col == 3 ) {
//   $vars['content_classes'] = 'col-sm-12';
// }