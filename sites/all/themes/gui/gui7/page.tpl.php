<?php
// krumo($page);
?>
<?php
?>
  <div id="branding" class="clearfix">
    <?php print $breadcrumb; ?>
    <?php print render($title_prefix); ?>
    <?php if ($title): ?>
      <h1 class="page-title"><?php print $title; ?></h1>
    <?php endif; ?>
    <?php print render($title_suffix); ?>
    <?php print render($primary_local_tasks); ?>
  </div>

  <div id="page">
		
    <div id="content" class="clearfix">
	
			<?php if($page['sidebar_first']): ?>
				<div id="sidebar-first" class="sidebar">
					<?php print render($page['sidebar_first']); ?>
				</div>
			<?php endif; ?>
			
			<?php if($page['sidebar_first'] || $page['sidebar_second']): ?>
				<div id="center">
			<?php endif; ?>

	      <div class="element-invisible"><a id="main-content"></a></div>
	      <?php if ($messages): ?>
	        <div id="console" class="clearfix"><?php print $messages; ?></div>
	      <?php endif; ?>
	      <?php if ($page['help']): ?>
	        <div id="help">
	          <?php print render($page['help']); ?>
	        </div>
	      <?php endif; ?>
	      <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
	      <?php print render($page['content']); ?>

			<?php if($page['sidebar_first'] || $page['sidebar_second']): ?>
				</div><!-- // #center -->
			<?php endif; ?>

			
			<?php if($page['sidebar_second']): ?>
				<div id="sidebar-last" class="sidebar">
					<?php print render($page['sidebar_second']); ?>
				</div>
			<?php endif; ?>
			
			
    </div>

    <div id="footer">
      <?php print $feed_icons; ?>
    </div>

  </div>
