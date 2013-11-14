<?php 

class NodeEntityFieldQuery extends EntityFieldQuery {  
  public function __construct() {    
    // //parent::__construct();
//    global $language;
    $this
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('status', 1);
      // ->propertyCondition('language', array('und', $language->language))
  }
}

class ThemaEntityFieldQuery extends EntityFieldQuery{ //NodeEntityFieldQuery {  
  public function __construct() {
    ////parent::__construct();
    $this
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('status', 1)
      ->entityCondition('bundle', array('thematique'));
  }
}
