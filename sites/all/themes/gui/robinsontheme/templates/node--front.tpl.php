<div class="row alert alert-standard alert-dismissible fade in" role="alert">

  <article class="node node-<?= $node->nid ?> col-md-4 col-md-offset-4" <?= $attributes; ?>>

    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
  </article>

  <a class="hidden-xs hidden-sm col-md-1" data-dismiss="alert" aria-label="Close">Fermer</a>

</div>