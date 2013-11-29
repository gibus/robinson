
<?php print render($title_prefix); ?>
<h2 class="thema-title"<?php print $title_attributes; ?>><span class="txt"><?php print $title; ?></span></h2>
<?php print render($title_suffix); ?>

<section class="content">
<?php
  // dsm($content, 'content');
  hide($content['comments']);
  hide($content['links']);
  print render($content);

  // print render($content['field_video']);
  // print $title;
  // print render($content['field_thema_date']);
?>
</section>