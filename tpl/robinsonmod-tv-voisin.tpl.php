<?php if ($node): ?>
<?php
  // dsm($node,'$node');

  // Transform 3 grid system in 12.
  $size *= 4;

  // Get media fields
  $field_image = field_get_items('node', $node, 'field_image');
  $field_video = field_get_items('node', $node, 'field_video');
  $field_texte = field_get_items('node', $node, 'field_texte');
?>

<div class="row">

  <article class="node node-<?= $node->nid ?> node-<?= $node->type ?> col-xs-<?= $size ?>">
    <?php if ( $field_image ): ?>
      <?php $img = field_view_value('node', $node, 'field_image', $field_image[0]); ?>
      <figure class="thumbnail">
        <?= render($img) ?>
      </figure>
    <?php elseif ( $field_video ): ?>
      <?php $video = field_view_value('node', $node, 'field_video', $field_video[0]); ?>
      <figure>
        <div class="embed-responsive embed-responsive-4by3">
          <?= render($video) ?>
        </div>
      </figure>
    <?php elseif ( $field_texte ): ?>
      <?php $txt = field_view_value('node', $node, 'field_texte', $field_texte[0]); ?>
      <div class="jumbotron">
        <?= render($txt) ?>
      </div>
    <?php endif ?>
  </article>

</div>
<?php endif ?>