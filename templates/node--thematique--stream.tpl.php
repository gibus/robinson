
<?php print render($title_prefix); ?>
<h2 class="thema-title"<?php print $title_attributes; ?>>
  <span class="txt"><?php print $title; ?></span>
  <?php print render($content['field_titre_lettrage']); ?>
</h2>
<?php print render($title_suffix); ?>

<section class="content">
<?php
  // dsm($content, 'content');
  hide($content['comments']);
  hide($content['links']);
  hide($content['field_titre_lettrage']);
  print render($content);

  // print render($content['field_video']);
  // print $title;
  // print render($content['field_thema_date']);
?>
</section>