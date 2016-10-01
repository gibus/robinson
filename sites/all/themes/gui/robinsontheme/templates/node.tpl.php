<div class="row">

  <article class="node node-<?= $node->nid ?> col-xs-12 col-sm-10 col-md-8 col-lg-6" <?= $attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
  </article>

</div>
