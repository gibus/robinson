<?php 

function robinsonmod_ajax_thema(){

  // check if request is ajax, if not rediret to search_api_page page with right keys
  if (!$debug && (!isset($_SERVER['HTTP_X_REQUESTED_WITH']) || strtolower($_SERVER['HTTP_X_REQUESTED_WITH']) != 'xmlhttprequest')) {
    drupal_goto('/', array(), 301);
    exit ;
  }


  $query = new ThemaEntityFieldQuery;
    
  $themas = $query->execute();

  dsm($themas);


}