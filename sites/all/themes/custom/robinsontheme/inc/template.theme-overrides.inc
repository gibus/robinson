<?php

/* Put Breadcrumbs in a ol li structure */
function robinsontheme_breadcrumb($vars) {

  // dsm($vars,'$vars in *robinsonthememeta_breadcrumb*');

  // Limit the breadcrumb to thematiques and rendez-vous pages.
  $display_close_btn = drupal_match_path(current_path(), "rendez-vous/*\nthematiques/*");

  if ( !empty($vars['breadcrumb']) && $display_close_btn ) {

    $output = '<ol class="breadcrumb">';

    foreach ($vars['breadcrumb'] as $link)
      $output .= "<li>$link</li>";

    // Add current page onto the end for thematiques or rendez-vous pages.
    $item = menu_get_item();
    $end = end($vars['breadcrumb']);
    if ($end && strip_tags($end) !== $item['title']) {
      if ( count($item['page_arguments']) == 0 ) :
        $output .= '<li class="active">' . check_plain($item['title']) . '</li>';
      else:
        $output .= '<li>' . l($item['title'],$item['path']) . '</li>';
      endif;
    }

    $output .= '</ol>';

    return $output;

  }

}