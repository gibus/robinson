<?php // dsm($data,'$data'); ?>

<h2 class="page-subtitle"><?= t("Thématiques") ?></h2>

<div class="row">

  <?php foreach ($data as $key => $node): ?>
  <article class="item-list col-xs-12 col-sm-6 col-md-4 col-lg-3">
    <a href="<?= current_path().'/'.$node->nid ?>">
      <h3 class="item-title"><?= $node->title ?></h3>
      <?php $field_description = field_view_field('node', $node, 'field_description', array(
        "label"=>"hidden",
        'type' => 'text_summary_or_trimmed',
        'settings'=>array('trim_length' => 140),
      )); ?>
      <?= render( $field_description ) ?>
    </a>
  </article>
  <?php endforeach ?>

</div>