<?php

/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * Variables:
 * - $css: An array of CSS files for the current page.
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
 * - $rdf_namespaces: All the RDF namespace prefixes used in the HTML document.
 * - $grddl_profile: A GRDDL profile allowing agents to extract the RDF data.
 * - $head_title: A modified version of the page title, for use in the TITLE
 *   tag.
 * - $head_title_array: (array) An associative array containing the string parts
 *   that were used to generate the $head_title variable, already prepared to be
 *   output as TITLE tag. The key/value pairs may contain one or more of the
 *   following, depending on conditions:
 *   - title: The title of the current page, if any.
 *   - name: The name of the site.
 *   - slogan: The slogan of the site, if any, and if there is no title.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $page_top: Initial markup from any modules that have altered the
 *   page. This variable should always be output first, before all other dynamic
 *   content.
 * - $page: The rendered page content.
 * - $page_bottom: Final closing markup from any modules that have altered the
 *   page. This variable should always be output last, after all other dynamic
 *   content.
 * - $classes String of classes that can be used to style contextually through
 *   CSS.
 *
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>

<?= $doctype; ?>

<!-- paulirish.com/2008/conditional-stylesheets-vs-css-hacks-answer-neither/ -->
<!--[if lt IE 7]> <html class="no-js ie6 oldie" lang="<?= $language->language; ?>" dir="<?= $language->dir; ?>" <?= $rdf_namespaces; ?>> <![endif]-->
<!--[if IE 7]>    <html class="no-js ie7 oldie" lang="<?= $language->language; ?>" dir="<?= $language->dir; ?>" <?= $rdf_namespaces; ?>> <![endif]-->
<!--[if IE 8]>    <html class="no-js ie8 oldie" lang="<?= $language->language; ?>" dir="<?= $language->dir; ?>" <?= $rdf_namespaces; ?>> <![endif]-->
<!-- Consider adding an manifest.appcache: h5bp.com/d/Offline -->
<!--[if gt IE 8]><!--> <html class="no-js" lang="<?= $language->language; ?>" dir="<?= $language->dir; ?>" <?= $rdf_namespaces; ?>> <!--<![endif]-->

<head<?= $rdf_profile; ?>>
  <?= $head; ?>
  <title><?= $head_title; ?></title>
  <?= $styles; ?>
</head>

<body class="<?= $classes; ?>" <?= $attributes;?>>

  <!-- CONTENT -->
  <div class="container">
    <?= $page_top; ?>
    <?= $page; ?>
    <?= $page_bottom; ?>
  </div>

  <!-- TOOLS -->
  <div id="dev">
    <div class="container">
      <div id="grid" class="row">
        <?php for ($i=1; $i < 13; $i++) : ?>
        <div class="col col-xs-1"><div class="in"><?= $i ?></div></div>
        <?php endfor ?>
      </div>
      <div class="row">
        <div class="col col-xs-12">
          <div id="size"></div>
        </div>
      </div>
    </div>
  </div>

  <div id="dev2">
    <div class="container">
      <? $hidden = ['hidden-xs ','hidden-sm ','hidden-md ','hidden-lg '] ?>
      <? $n      = 3 ?>

      <? foreach (range('A', 'C') as $i) : ?>
      <div class="row">

        <? for ($j=0; $j < $n; $j++) : ?>
        <?
          $class = "";
          if($j > 0) $class .= $hidden[0];
          if($j > 1) $class .= $hidden[1];
          if($j > 2) $class .= $hidden[2];
        ?>
        <div class="col-xs-12 col-sm-4 <?= $class ?>">
          <div class="ratio">
            <div class="in">
              <? for ($k=0; $k < 4; $k++) : ?>
              <? $ligne = $i ."-". ($j+1) ."-". ($k+1) ?>
              <div class="ligne ligne-<?= $ligne ?>"><?= $ligne ?></div>
              <? endfor ?>
            </div>
          </div>
        </div>
        <? endfor ?>

      </div>
      <? endforeach ?>
    </div>
  </div>

  <!-- Javascript at the bottom for fast page loading -->
  <?= $scripts; ?>
  <!-- Prompt IE 6 users to install Chrome Frame. Remove this if you want to support IE 6.
       chromium.org/developers/how-tos/chrome-frame-getting-started -->
  <!--[if lt IE 7 ]>
    <script src="//ajax.googleapis.com/ajax/libs/chrome-frame/1.0.3/CFInstall.min.js"></script>
    <script>window.attachEvent('onload',function(){CFInstall.check({mode:'overlay'})})</script>
  <![endif]-->
</body>
</html>
