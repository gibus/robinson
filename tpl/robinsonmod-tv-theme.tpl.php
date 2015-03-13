<?php if ($node): ?>
<?php $offsetTop = mt_rand(1,10); ?>
<?php $offsetTopImg = mt_rand(0,10); ?>
<div class="row">

  <article class="node node-<?= $node->nid ?> node-<?= $node->type ?> col-xs-12 col-md-4 col-offset-top-<?= $offsetTop ?>">
    <figure>
      <div class="embed-responsive embed-responsive-4by3">
        <? $field_video = field_get_items('node', $node, 'field_video'); ?>
        <? $video = field_view_value('node', $node, 'field_video', $field_video[0]); ?>
        <?= render($video) ?>
      </div>
      <?php $field_type_of_vimeo = field_get_items('node', $node, 'field_type_of_vimeo'); ?>
      <?php $type_of_vimeo = render(field_view_value('node', $node, 'field_type_of_vimeo', $field_type_of_vimeo[0])); ?>
      <?php if ($type_of_vimeo != 'sound'): ?>
      <figcaption>
        <h2 class="node-title"><?= $node->title ?></h2>
        <? $field_thema_date = field_get_items('node', $node, 'field_thema_date'); ?>
        <h3 class="date"><?= date('d.m.y',$field_thema_date[0][value]) ?></h3>
      </figcaption>
      <?php endif ?>
    </figure>
  </article>

  <? $field_titre_lettrage = field_get_items('node', $node, 'field_titre_lettrage'); ?>
  <? if ( $field_titre_lettrage ): ?>
  <aside class="node node-<?= $node->nid ?> col-xs-12 col-md-8 col-offset-top-<?= $offsetTopImg ?>">
    <figure class="thumbnail">
      <? $img = field_view_value('node', $node, 'field_titre_lettrage', $field_titre_lettrage[0]); ?>
      <?= render($img) ?>
    </figure>
  </aside>
  <? endif ?>

</div>
<?php endif ?>