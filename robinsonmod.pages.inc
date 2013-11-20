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
  $themas = $query->execute();
  // dsm($themas);

  # get a random thema
  $thema = $themas['node'][array_rand($themas['node'])];
  
  $thema_node = node_load($thema->nid); 
  // dsm($thema_node, 'thema_node');
  $rep['thema'] = array(
    "nid"=>$thema_node->nid,
    "voisins"=>$thema_node->field_ref_voisin['und']
  ); 
  
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
    $rep['error'] = "noid";
  }else{

    $voisin_node = node_load($_GET['id']); 
    
    if($debug)
      $rep['voisin_node'] = $voisin_node;  

    $type = $voisin_node->field_voisin_type['und'][0]['tid'];
    $rep['voisin'] = array(
      "nid"=>$voisin_node->nid,
      "type"=>$type,
    ); 
    
    switch ($type) {
      case 5:
        $viewmode = "voisin_atmosphere";
        break;
      case 10:
        $viewmode = "voisin_contrib_image";
        break;
      case 2:
        $viewmode = "voisin_contrib_son";
        break;
      case 9:
        $viewmode = "voisin_contrib_txt";
        break;
      case 8:
        $viewmode = "voisin_contrib_video";
        break;
      case 6:
        $viewmode = "voisin_danse_son";
        break;
      case 4:
        $viewmode = "voisin_danse_video";
        break;
      case 7:
        $viewmode = "voisin_lettrage_image";
        break;
      case 3:
        $viewmode = "voisin_lettrage_video";
        break;
      case 1:
        $viewmode = "voisin_nature";
        break;
      default:
        $viewmode = "stream";
        break;
    }
    
    $node_view = node_view($voisin_node, $viewmode);
    $rep['rendered_voisin'] =   drupal_render($node_view);
  }



  if (!$json) {
    dsm($rep, 'rep');
    return "debug display";
  }else{
    drupal_json_output($rep);  
  }
}