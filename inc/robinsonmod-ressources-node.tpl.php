<?php //dsm($node,'$node'); ?>

<? if ($node): ?>
<h2 class="page-subtitle"><?= $node->title ?></h2>

<div class="row">

  <article class="node node-<?= $node->nid ?> col-xs-12 col-sm-10 col-md-8 col-lg-6">
    <? if( !empty($node->field_description) ) : ?>
      <?php $field_description = field_view_field('node', $node, 'field_description', array("label"=>"hidden")); ?>
      <?= render( $field_description ) ?>
    <? else: ?>
      <p>Pas encore renseigné.</p>
    <? endif ?>
  </article>

</div>
<? endif ?>