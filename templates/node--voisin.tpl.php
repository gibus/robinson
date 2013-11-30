<?php 
$voisin_classes = array("voisin");
$voisin_classes[] = "voisin-".$node->nid;
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