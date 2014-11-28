<article id="node-<?= $node->nid; ?>" class="<?= $classes; ?> view-mode-<?= $view_mode ?>"<?= $attributes; ?>>

  <div class="content row"<?= $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
  </div>

</article>
