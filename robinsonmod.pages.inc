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

/* RENDEZ-VOUS */
function robinsonmod_rendez_vous_getcontent($arg=FALSE,$arg2=FALSE){
  // dsm($arg,'$arg');
  $ret = preg_match('/\d+/', $arg) ? robinsonmod_rendez_vous_getNode($arg,$arg2) : robinsonmod_rendez_vous_getAll();
  return $ret;
}

function robinsonmod_rendez_vous_getAll(){
  $query = new EntityFieldQuery();

  // $starttime = time();
  // $endtime   = strtotime( "+1 month", $starttime );
  $starttime = '1401621300';
  $endtime   = strtotime( "+15 day", $starttime );

  $entities = $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', array('programme'))
    ->propertyCondition('status', 1)
    ->fieldCondition('field_prog_plage', 'value', array($starttime, $endtime), 'BETWEEN')
    ->execute();

  // -- create an array with one cell per day for the period.
  $data = array();

  if (isset($entities['node'])) :

    $weight = 0;
    $nodes = entity_load('node', array_keys($entities['node']));

    /* // -- activate this part of the code to display the empty days.
    $i = $starttime;
    while ( $i <= $endtime) :
      $day = timestampDay($i);
      $data[$day] = [];
      $i = strtotime( "+1 day", $i );
    endwhile;*/

    // -- save node(s) for each day.
    foreach ($nodes as $node) :
      $fieldvalues = field_get_items('node', $node, 'field_prog_plage');
      foreach ($fieldvalues as $fieldvalue)
        if( $fieldvalue['value'] >= $starttime && $fieldvalue['value'] <= $endtime ) :
          $day = timestampDay($fieldvalue['value']);
          $data[$day][] = $node;
        endif;
    endforeach;

    // dsm($data,'$data in *robinsonmod_rendez_vous_getcontent*');

  endif;

  return theme('robinsonmod_rendez_vous', array('data' => $data) );
}

function robinsonmod_rendez_vous_getNode($nid,$date){
  $node = node_load($nid);
  return theme('robinsonmod_rendez_vous_node', array('node' => $node, 'date' => $date));
}

/* RESSOURCES */
function robinsonmod_ressources_getcontent($arg=FALSE){
  // dsm($arg,'$arg');
  $ret = preg_match('/\d+/', $arg) ? robinsonmod_ressources_getNode($arg) : robinsonmod_ressources_getAll();
  return $ret;
}

function robinsonmod_ressources_getAll(){
  $query = new EntityFieldQuery();

  $entities = $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', array('thematique'))
    ->propertyCondition('status', 1)
    ->execute();

  $data = array();

  if (isset($entities['node'])) :

    $data = entity_load('node', array_keys($entities['node']));

  endif;

  return theme('robinsonmod_ressources', array('data' => $data) );
}

function robinsonmod_ressources_getNode($nid){
  $node = node_load($nid);
  return theme('robinsonmod_ressources_node', array('node' => $node));
}