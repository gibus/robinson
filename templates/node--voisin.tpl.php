<?php $voisin_class = str_replace('voisin-', '', str_replace('_', '-', $view_mode)); ?>
<article class="voisin <?php print $voisin_class; ?>">
<?php
  // dsm($content, 'content');
  hide($content['comments']);
  hide($content['links']);
  print render($content);
?>
</article>