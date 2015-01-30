<?php //dsm($node,'$node'); ?>
<?php //dsm($date,'$date'); ?>

<?php if ($node): ?>
<h2 class="page-subtitle"><?= $node->title ?></h2>

<div class="row">

  <article class="node node-<?= $node->nid ?> col-xs-12 col-sm-10 col-md-8 col-lg-6">
    <?php
    // $fieldvalues = field_get_items('node', $node, 'field_prog_plage');
    // foreach ($fieldvalues as $fieldvalue) :
    //   $tstart = timestampDay( $fieldvalue['value'], TRUE );
    //   $format = 'H:i';
    //   $start  = format_date( $fieldvalue['value'],  'custom', $format );
    //   $end    = format_date( $fieldvalue['value2'], 'custom', $format );
    //   break;
    // endforeach;
    $start = "blabla";
    $end = "blabla";
    $field_prog_plage  = field_view_field('node', $node, 'field_prog_plage',  array("label"=>"hidden"));
    $field_description = field_view_field('node', $node, 'field_description', array("label"=>"hidden"));
    ?>

    <?php if ($date): ?>
    <h4 class="date"><?= timestampDay( $date ); ?></h4>
    <?php endif ?>
    <h5 class="hours"><?= $start ?> - <?= $end ?></h5>
    <?= render( $field_description ) ?>

  </article>

</div>
<?php endif ?>