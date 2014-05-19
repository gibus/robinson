<?php

$voisin_classes = array("voisin");
$voisin_classes[] = "voisin-".$node->nid;
$media_term = taxonomy_term_load($node->field_type_media['und'][0]['tid']);
$voisin_classes[] = stripAccents($media_term->name);
$voisin_classes[] = "voisin-media-".$node->field_type_media['und'][0]['tid'];
$voisin_classes[] = str_replace('voisin-', '', str_replace('_', '-', $view_mode));

?>
<article class="<?php print implode(' ', $voisin_classes); ?>">
<?php
  // dsm($content, 'content');
  hide($content['comments']);
  hide($content['links']);
  print render($content);
?>
</article>