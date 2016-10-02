<?php



/**
 * Implements hook_views_data().
 */
// function tode_views_data() {
//    // Code goes here. See example at http://views.doc.logrus.com/group__views__hooks.html#g227057901681e4a33e33c199c7a8c989
// 
// 	$data['node']['tode_parent'] = array(    
//     'group' => t('tode'),
//     'title' => t('Tode'),
//     'help' => t('Filtrer with tode parent term.'), // The help that appears on the UI,  
//     // 'real field' => 'field_pv_value',
//     'filter' => array(
//       'handler' => 'tode_views_handler_parent_filter',
//     ),    
//   );
// 
// }	

function tode_views_data_alter(&$data) {
  $data['tid']['tode_parent'] = array(
   'title' => t('Tode parent'),
   'group' => 'Tode',
   'help' => t('Parent term of tode field'),
 		'real field' => 'field_tode_program',
   'filter' => array(
      'handler' => 'tode_views_handler_parent_filter',
    ),        
  );    
}