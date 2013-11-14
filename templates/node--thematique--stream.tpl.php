
<?php print render($title_prefix); ?>
<h2 class="thema-title"<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
<?php print render($title_suffix); ?>


<?php
  dsm($content, 'content');
  hide($content['comments']);
  hide($content['links']);
  print render($content);
?>
