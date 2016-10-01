<?php // dsm($data,'$data'); ?>

<h2 class="page-subtitle"><?= t("Lors des 30 prochains jours") ?></h2>

<div class="row">

  <?php foreach ($data as $date => $nodes): ?>
  <section class="item-list col-xs-12 col-sm-6 col-md-4 col-lg-3">

    <h3 class="item-title"><?= $date ?></h3>

    <?php $tdate = strtotime($date); ?>
    <?php foreach ($nodes as $key => $node): ?>
    <article class="item item-<?= $key ?>">
      <a href="<?= current_path().'/'.$node->nid.'/'.$tdate ?>">
        <?php
        $fieldvalues = field_get_items('node', $node, 'field_prog_plage');
        foreach ($fieldvalues as $fieldvalue) :
          $tstart = timestampDay( $fieldvalue['value'], TRUE );
          if ( $tdate == $tstart ) :
            $format = 'H:i';
            $start  = format_date( $fieldvalue['value'],  'custom', $format );
            $end    = format_date( $fieldvalue['value2'], 'custom', $format );
            break;
          endif;
        endforeach;
        ?>

        <h4 class="hours"><?= $start ?> - <?= $end ?></h4>
        <p class="name"><?= $node->title ?></p>
      </a>
    </article>
    <?php endforeach; ?>

  </section>
  <?php endforeach ?>

</div>