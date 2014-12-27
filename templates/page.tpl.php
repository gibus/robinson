<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>
    <header id="header" class="row">

      <div class="col-sm-5 col-md-4">

        <?php if ($logo): ?>
        <a href="<?= $front_page; ?>" title="<?= t('Home'); ?>" rel="home" id="logo">
          <img src="<?= $logo; ?>" alt="<?= t('Home'); ?>" />
        </a>
        <?php endif; ?>

        <?php if ($site_name): ?>
        <h1 id="site-title">
          <a href="<?= $front_page; ?>" title="<?= t('Home'); ?>" rel="home" id="logo">
            <?= $site_name ?>
          </a>
        </h1>
        <?php endif; ?>

        <?php if ($site_slogan): ?>
        <h2 id="site-slogan"><?= $site_slogan ?></h2>
        <?php endif; ?>

        <?= render($page['header']); ?>

      </div>

      <nav id="navigation" class="col-sm-5 col-sm-offset-2 col-md-4 col-md-offset-4" role="navigation">
        <ul class="nav navbar-nav">
          <?php if ($main_menu): ?>
          <li class="dropdown">
            <button class="btn btn-primary btn-block dropdown-toggle" type="button" data-toggle="dropdown">
              <?= t('informations') ?> <span class="caret"></span>
            </button>
            <!-- <a id="dLabel" role="button" data-toggle="dropdown" data-target="#" href="/">
              <?= t('informations') ?> <span class="caret"></span>
            </a> -->
            <?= theme('links__system_main_menu', array('links' => $main_menu, 'attributes' => array('id' => 'main-menu', 'class' => array('dropdown-menu'), 'role' => 'menu'))); ?>
          </li>
          <?php endif; ?>
          <?php if ($secondary_menu): ?>
          <li class="dropdown">
            <a href="#" class="dropdown-toggle" data-toggle="dropdown"><?= t('Secondary menu') ?> <span class="caret"></span></a>
            <?= theme('links__system_secondary_menu', array('links' => $secondary_menu, 'attributes' => array('id' => 'secondary-menu', 'class' => array('nav', 'navbar-nav')))); ?>
          </li>
          <?php endif; ?>
        </ul>
      </nav> <!-- /#navigation -->

    </header><!-- /#header -->

    <?php if ($show_messages && $messages): print $messages; endif; ?>
    <?= render($page['help']); ?>

    <?php if ($breadcrumb): ?>
    <nav id="breadcrumb" role="breadcrumb"><?= $breadcrumb; ?></nav>
    <?php endif; ?>

    <main id="main">

      <?php if($title): ?><h1 class="page-title"><?= $title ?></h1><?php endif; ?>

      <?= render($page['content']); ?>

    </main><!-- /#main -->

    <footer id="footer">

      <?= render($page['footer']); ?>

    </footer><!-- /#footer -->