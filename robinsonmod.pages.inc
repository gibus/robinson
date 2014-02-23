<?php 

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


  # get all the thematiques
  $query = new ThemaEntityFieldQuery;

  # get 10 last already displayed themas
  $displayed_themas = variable_get('robinsonmod_displayed_themas', array());
  // dsm($displayed_themas);
  if(count($displayed_themas))
    $query->entityCondition('entity_id', $displayed_themas, 'NOT IN');

  $themas = $query->execute();
  // dsm($themas);

  # get a random thema
  $thema = $themas['node'][array_rand($themas['node'])];

  $displayed_themas[] = $thema->nid;
  if(count($displayed_themas) > 10)
    array_pop($displayed_themas);

  $rep['displayed_themas'] = $displayed_themas;
  variable_set('robinsonmod_displayed_themas', $displayed_themas);

  $thema_node = node_load($thema->nid); 
  // dsm($thema_node, 'thema_node');

  $voisins = $thema_node->field_ref_voisin['und'];

  # add randomly more voisins to fit to 20
  $min_voisins = 10;
  if(count($voisins) < $min_voisins){
    $voisins_query = new VoisinEntityFieldQuery;
    $all_voisins = $voisins_query->execute();
    $all_voisins = $all_voisins['node'];

    // for ($i=0; $i < 20; $i++) {
    while(count($voisins) < $min_voisins){ 
      shuffle($all_voisins);
      $rand_voisin = array_shift($all_voisins);
      $rand_voisin->target_id = $rand_voisin->nid; 
      $voisins[] = $rand_voisin;
    }
  }

  $rep['nid'] = $thema_node->nid;
  $rep["list_voisins"] = $voisins;
  
  $viewmode = "stream";
  $node_view = node_view($thema_node, $viewmode);
  $rep['rendered_thema'] =   drupal_render($node_view);

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
  
  if(!isset($_GET['id'])){
    $rep['error'] = "no id (need nid to load node)";
  }else{

    $voisin_node = node_load($_GET['id']); 
    
    if($debug)
      $rep['voisin_node'] = $voisin_node;  

    $media_type = $voisin_node->field_type_media['und'][0]['tid'];
    $rep['voisin'] = array(
      "nid"=>$voisin_node->nid,
      // "media_type"=>$media_type,
    ); 
    
    switch ($media_type) {
      case 12: #video
        $viewmode = "voisin_video";
        break;
      case 13: #image
        $viewmode = "voisin_image";
        break;
      case 14: #son
        $viewmode = "voisin_audio";
        break;
      case 15: #texte
        $viewmode = "voisin_text";
        break;
      default:
        $viewmode = "stream";
        break;
    }
    $rep['media_type'] = str_replace('voisin_', '', $viewmode);
    
    # flatenize comportement
    $comportement_tid = $voisin_node->field_comportement['und'][0]['tid'];
    $comportement_term = taxonomy_term_load($comportement_tid);
    foreach ($comportement_term as $key => $value) {
      if(strpos($key, "field_") === 0 && is_array($value)){
        $comportement[$key] = $value['und'][0]['value'];
      }else{
        $comportement[$key] = $value;
      }
    }
    $rep['comportement'] = $comportement;

    // VIDEO & IMAGES : change viewmode for size for images and videos (one viewmode by size 1,2,3)
    if(in_array($media_type, array(12,13))){
      preg_match('/(\d{1})\/(\d{1})/', $comportement['field_taille_minmax'], $matches);
      $Tminmax = array(
        "min" => $matches[1],
        "max" => $matches[2],
      );
      // $rep['tminmax'] = $Tminmax;
      $taille = round(rand($Tminmax['min'], $Tminmax['max']));
      $rep['ttttaille'] = $taille;
      $taille = $taille < 1 ? 1 : $taille > 3 ? 3 : $taille;
      $viewmode .= "_t".$taille;
    }
    
    # record viewmode and render node
    $rep['viewmode'] = $viewmode;

    $node_view = node_view($voisin_node, $viewmode);
    $rep['rendered_voisin'] = drupal_render($node_view);
  }



  if (!$json) {
    dsm($rep, 'rep');
    return "debug display";
  }else{
    drupal_json_output($rep);  
  }
}