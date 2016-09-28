<div class="panel panel-html5-custom clear-after" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
	<nav class="nav clear-after"><?php print $content['nav']; ?></nav>
	<article class="article clear-after"><?php print $content['article']; ?></article>
	<aside class="aside clear-after">
		
		<?php if($content['aside-nav']): ?><nav class="aside-nav clear-after"><?php print $content['aside-nav']; ?></nav><?php endif; ?>
		<?php print $content['aside-content']; ?>
	</aside>
</div>