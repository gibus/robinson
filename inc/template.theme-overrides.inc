<?php

/* Put Breadcrumbs in a ol li structure */
function robinsontheme_breadcrumb($vars) {

  // dsm($vars,'$vars in *robinsonthememeta_breadcrumb*');

  if ( !empty($vars['breadcrumb']) ) {

    $output = '<ol class="breadcrumb">';

    // Optional: Add the site name to the front of the stack.
    if (!empty($vars['prepend'])) {
      $site_name = empty($vars['breadcrumb']) ? '<li class="active">'. check_plain(variable_get('site_name', '')) .'</li>' : l(variable_get('site_name', ''), '<front>', array('purl' => array('disabled' => TRUE)));
      array_unshift($vars['breadcrumb'], $site_name);
    }

    foreach ($vars['breadcrumb'] as $link)
      $output .= "<li>$link</li>";

    // Add current page onto the end.
    if (!drupal_is_front_page()) {
      $item = menu_get_item();
      $end = end($vars['breadcrumb']);
      if ($end && strip_tags($end) !== $item['title']) {
        if ( count($item['page_arguments']) == 0 ) :
          $output .= '<li class="active">' . check_plain($item['title']) . '</li>';
        else:
          $output .= '<li>' . l($item['title'],$item['path']) . '</li>';
        endif;
      }
    }

    $output .= '</ol>';

    return $output;

  }

}