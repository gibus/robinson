<?php
function robinsonmod_ajax_getcontent() {
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

/* TV SHOW */
function robinsonmod_tv_show_giveMeATheme(){

  $opt = $_GET;
  $query = new ProgramEntityFieldQuery();

  $starttime = time();

  $entities = $query
    ->fieldCondition('field_prog_plage', 'value', $starttime, '<')
    ->fieldCondition('field_prog_plage', 'value2', $starttime, '>')
    ->execute();

  $ret = isset($entities['node']) ? robinsonmod_tv_show_program($entities) : robinsonmod_tv_show_random($opt);

  // return $ret;
  return drupal_json_output($ret);

}

function robinsonmod_tv_show_program($entities){

  // -- create an array contains datas.
  $data = array();
  $data['mode'] = 'program';

  // -- get node nid.
  $entity = $entities['node'][0];
  $data["nid"] = $entity->nid;

  return $data;

}

function robinsonmod_tv_show_random($opt = array()){

  $query = new ThemaEntityFieldQuery();

  // -- create an array contains datas.
  $data = array();
  $data['mode'] = 'random';

  // -- exclude played theme.
  if( isset($opt['loaded']) )
    $query->entityCondition('entity_id', $opt['loaded'], 'NOT IN');

  $entities = $query
    ->addTag('random')
    ->range(0, 1)
    ->execute();

  if( isset($entities['node']) ) :
    // -- get node nid.
    $entity = array_pop($entities['node']);
    $data["nid"] = $entity->nid;

  endif;

  return $data;

}

function robinsonmod_tv_show_giveMeANeighbour(){

  $opt = $_GET;

  // == Step 1. Get discursive terms that we don’t want.
  $query = new EntityFieldQuery() ;
  $terms = $query
    ->entityCondition('entity_type', 'taxonomy_term')
    ->entityCondition('bundle', 'comportement')
    ->fieldCondition('field_discursif', 'value', 1, '=')
    ->execute();

  foreach ($terms['taxonomy_term'] as $tid => $term)
    $opt['discursive_tids'][] = $tid;

  // == Step 2. Get nids.
  $query = new VoisinEntityFieldQuery();

  // -- create an array contains datas.
  $data = array();
  $n = 20; // number of voisins wanted.

  if( isset($opt['voisins_nids']) ) :
    $data["nids"] = $opt['voisins_nids'];
    $query->entityCondition('entity_id', $opt['voisins_nids'], 'NOT IN');
    $n -= count($data["nids"]);
  endif;

  $entities = $query
    ->fieldCondition('field_comportement', 'tid', $opt['discursive_tids'], 'NOT IN')
    ->addTag('random')
    ->range(0, $n)
    ->execute();

  if( isset($entities['node']) ) :

    // -- get nodes nid.
    foreach ($entities['node'] as $nid => $node)
      $data["nids"][] = $nid;

  endif;

  // dsm($data,'$data');

  return drupal_json_output($data);

}

function robinsonmod_tv_show_nodeLoad(){

  $opt = $_GET;
  $nid = $opt['nid']?:null;

  if( $nid ):
    $node = node_load($nid);
    $data['type'] = $node->type;

    switch ($node->type) {
      case 'programme':
        $ret = robinsonmod_tv_show_nodeLoad_programme($node);
        $data = array_merge($data,$ret);
        break;
      case 'thematique':
        $ret = robinsonmod_tv_show_nodeLoad_thematique($node);
        $data = array_merge($data,$ret);
        break;
      case 'voisin':
        $ret = robinsonmod_tv_show_nodeLoad_voisin($node);
        $data = array_merge($data,$ret);
        break;
    }

  else:
    $data = false;
  endif;

  return drupal_json_output($data);
  // return $data;

}

function robinsonmod_tv_show_nodeLoad_programme($node){
  $ret['html'] = theme('robinsonmod_tv_theme', array('node' => $node));
  return $ret;
}

function robinsonmod_tv_show_nodeLoad_thematique($node){
  $ret['html'] = theme('robinsonmod_tv_theme', array('node' => $node));
  $voisins = field_get_items('node', $node, 'field_ref_voisin');
  foreach ($voisins as $voisin)
    $ret['voisins_nids'][] = $voisin['target_id'];
  return $ret;
}

function robinsonmod_tv_show_nodeLoad_voisin($node){
  $field_comportement = field_get_items('node', $node, 'field_comportement');
  $comportement = taxonomy_term_load($field_comportement[0]['tid']);
  $field_type_media = field_get_items('node', $node, 'field_type_media');
  $mediatype = taxonomy_term_load($field_type_media[0]['tid']);

  // Get size
  $field_size = field_get_items('taxonomy_term', $comportement, 'field_taille_minmax');
  $size = field_view_value('taxonomy_term', $comportement, 'field_taille_minmax', $field_size[0]);
  $size = render($size);
  preg_match_all('/\d+/', $size, $sizes);
  if( isset($sizes[0]) ):
    $min = min($sizes[0]);
    $max = max($sizes[0]);
    $size = rand($min,$max);
  else:
    $size = 1;
  endif;

  // Get media type
  $type = $mediatype->name;

  // Get duration
  if( $type == 'photo' || $type == 'texte' ):
    $field_duree_sec_minmax = field_get_items('taxonomy_term', $comportement, 'field_duree_sec_minmax');
    $duration = field_view_value('taxonomy_term', $comportement, 'field_duree_sec_minmax', $field_duree_sec_minmax[0]);
    $duration = render($duration);
    preg_match_all('/\d+/', $duration, $durations);
    if( isset($durations[0]) ):
      $min = min($durations[0]);
      $max = max($durations[0]);
      $duration = rand($min,$max);
    else:
      $duration = 10;
    endif;
  else:
    $duration = null;
  endif;

  $ret['duration'] = $duration;
  $ret['mediatype'] = $type;
  $ret['html'] = theme('robinsonmod_tv_voisin', array('node' => $node, 'size' => $size));
  return $ret;
}


/* RENDEZ-VOUS */
function robinsonmod_rendez_vous_getcontent($arg=FALSE,$arg2=FALSE){
  // dsm($arg,'$arg');
  $ret = preg_match('/\d+/', $arg) ? robinsonmod_rendez_vous_getNode($arg,$arg2) : robinsonmod_rendez_vous_getAll();
  return $ret;
}

function robinsonmod_rendez_vous_getAll(){
  $query = new ProgramEntityFieldQuery();

  $starttime = time();
  $endtime   = strtotime( "+1 month", $starttime );
  // $starttime = '1401621300';
  // $endtime   = strtotime( "+15 day", $starttime );

  $entities = $query
    ->fieldCondition('field_prog_plage', 'value', array($starttime, $endtime), 'BETWEEN')
    ->execute();

  // -- create an array with one cell per day for the period.
  $data = array();

  if (isset($entities['node'])) :

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