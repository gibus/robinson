<?php
function robinsonmod_ajax_getcontent(){
  $debug = true;
  $json = true;
  $rep = array();

  # check if request is ajax, if not rediret to search_api_page page with right keys
  if ((!isset($_SERVER['HTTP_X_REQUESTED_WITH']) || strtolower($_SERVER['HTTP_X_REQUESTED_WITH']) != 'xmlhttprequest')) {
    if(!$debug){
      drupal_goto('/', array(), 301);
      exit ;
    }else{
      $json = false;
    }
  }

  if($debug)
    $rep['$_GET'] = $_GET;

  $rep['displayed_thema'] = $_GET['displayed_thema'];
  if(isset($_GET['currentTime'])){
    $rep['currentTime'] = $_GET['currentTime'];
    rodinsonmod_checkPrograme($rep);
  }else{
    robinsonmod_randomThema($rep);
  }

  if (!$json) {
    dsm($rep, 'rep');
    return "debug display";
  }else{
    drupal_json_output($rep);
  }
}

function robinsonmod_ajax_thema(){
  $debug = true;
  $json = true;
  $rep = array();

  # check if request is ajax, if not rediret to search_api_page page with right keys
  if ((!isset($_SERVER['HTTP_X_REQUESTED_WITH']) || strtolower($_SERVER['HTTP_X_REQUESTED_WITH']) != 'xmlhttprequest')) {
    if(!$debug){
      drupal_goto('/', array(), 301);
      exit ;
    }else{
      $json = false;
    }
  }


  if($debug)
    $rep['$_GET'] = $_GET;

  if(!isset($_GET['thema_nid'])){
    $rep['error'] = "no id (we need thema nid to load voisin node)";
  }else{


    $thema_node = node_load($_GET['thema_nid']);
    // dsm($thema_node, 'thema_node');

    $voisins = $thema_node->field_ref_voisin['und'];
    $rep["voisins_list"] = $voisins;

    $viewmode = "stream";
    $node_view = node_view($thema_node, $viewmode);
    $rep['rendered_thema'] =   drupal_render($node_view);
  }

  if (!$json) {
    dsm($rep, 'rep');
    return "debug display";
  }else{
    drupal_json_output($rep);
  }
}

function robinsonmod_ajax_voisin(){
  $debug = true;
  $json = true;
  $rep = array();

  # check if request is ajax, if not rediret to search_api_page page with right keys
  if ((!isset($_SERVER['HTTP_X_REQUESTED_WITH']) || strtolower($_SERVER['HTTP_X_REQUESTED_WITH']) != 'xmlhttprequest')) {
    if(!$debug){
      drupal_goto('/', array(), 301);
      exit ;
    }else{
      $json = false;
    }
  }

  if($debug)
    $rep['$_GET'] = $_GET;

  if(isset($_GET['voisin'])){
    $rep["voisin"] = robinsonmod_renderVoisin($_GET['voisin']['nid']);

  }else if(isset($_GET['thema'])){

    $thema = $_GET['thema'];
    $rep['thema'] = $thema;

    $all_voisins_by_space = robinsonmod_getAllVoisinsBySpace();
    if($debug)
      $rep['all_voisins_by_space'] = $all_voisins_by_space;

    $voisins = array();
    foreach ($all_voisins_by_space as $space => $voisins_by_media) {
      # filter voisin by space
      if($space > $thema["availablespace"])
        continue;

      foreach ($voisins_by_media as $media => $voisins_by_discursif) {
        # remove audio voisin if already one audio is playing
        if($media == "audio" && $thema["is_playing_audio"])
          continue;

        // if($media != "image")
        //   continue;

        foreach ($voisins_by_discursif as $d => $vs)
          # remove discursif voisins since we are on a thema
          if($d == "no-discursif")
            $voisins += $vs;
      }
    }

    $rep['voisins'] = $voisins;

    // remove form all voisins those who were already displayed
    if(isset($thema['played_voisins_nids']))
      foreach ($thema['played_voisins_nids'] as $nid)
        unset($voisins[$nid]);

    $rep["voisin"] = count($voisins) ? $voisins[array_rand($voisins)] : 0;

  }

  if (!$json) {
    dsm($rep, 'rep');
    return "debug display";
  }else{
    drupal_json_output($rep);
  }
}