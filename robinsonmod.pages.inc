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

  $thema = $themas['node'][array_rand($themas['node'])];
  
  $thema_node = node_load($thema->nid); 
  dsm($thema_node, 'thema_node');
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