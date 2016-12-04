<?php
drush_print("Process thematiques");
// Search for publication nodes of publication type "report".
$efq = new EntityFieldQuery();
$efq
  // Conditions on the entity - its type and its bundle ("sub-type")
  ->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'thematique')
  ->fieldCondition('field_type_of_vimeo', 'value', false, '=')
  ->fieldOrderBy('field_memo', 'value');
 
// Execute, returning an array of arrays.
$result = $efq->execute();
 
// Ensure we've got some node results.
if (!isset($result['node'])) {
  drush_log("No nodes to process.", "ok");
  return;
}
$nb_nodes = 0;
$nb_nodes_ok = 0;
$nb_nodes_nok = 0;
$nb_nodes_publish = 0;
$nb_nodes_publish_ok = 0;
$nb_nodes_publish_nok = 0;
// Iterate over the result, loading each node at a time.
foreach($result['node'] as $nid => $stub_node) {
  // Load the full node and wrap it with entity_metadata_wrapper().
  $node = node_load($nid);
  $nb_nodes++;
  if ($node->status) {
    $nb_nodes_publish++;
  }

  $wrapped_node = entity_metadata_wrapper("node", $node);
 
  $description = $wrapped_node->field_description->value();
  if (preg_match('!\[https?://vimeo.com!', $description['value'])) {
    $nb_nodes_ok++;
    if ($node->status) {
      $nb_nodes_publish_ok++;
    }
    drush_print("Processed OK nid={$node->nid}, title={$node->title}");
  }
  else {
    $description['value'] = preg_replace('!\[(https?://vimeo.com)!', '[video:$1', $description['value']);
    $wrapped_node->field_description->set($description);
    $wrapped_node->save();

    $nb_nodes_nok++;
    if ($node->status) {
      $nb_nodes_publish_nok++;
    }
    drush_print("Processed NOK nid={$node->nid}, title={$node->title}");
  }
}
drush_print("$nb_nodes processed ($nb_nodes_publish published): $nb_nodes_ok OK ($nb_nodes_publish_ok) / $nb_nodes_nok NOK ($nb_nodes_publish_nok)");
