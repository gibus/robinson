<?php
GLOBAL $user;
/**
 * @file
 * Default theme implementation to present all variables to the theme layer for
 * the logged-in user block of the user_details module.
 *
 * Useable variables: (syntax: <?php print variable; ?>)
 * - $user_details_authored_name (user name of the logged-in user)
 * - $user_details_authored_avatar (user avatar of the logged-in user)
 * - $user_details_authored_joined (logged-in user's account creation date)
 * - $user_details_authored_postcount (number of posts the logged-in user has created)
 * - $user_details_authored_points (number of user points the logged-in user has)
 * - $user_details_authored_rank (logged-in user's user role)
 * - $user_details_authored_content (logged-in user's 3 most recently updated pieces of content)
 * - $user_details_authored_profilelink (link to the logged-in users profile)
 * - $user_details_authored_subscriptionslink (link to the logged-in user's subscription overview tab on thier profile)
 * - $user_details_authored_createlink (link to the create content page)
 * - $user_details_authored_logoutlink (link to logout the logged-in user)
 */
?>
<div id="user-details">
  <div id="authored">
    <?php if (variable_get('user_details_authored_avatar_display') != 0): ?>
      <div class="avatar"><?php print $user_details_authored_avatar; ?></div>
    <?php endif; ?>
    <?php if (variable_get('user_details_authored_joined_display')!= 0): ?>
      <div class="joined">
        <div class="title"><?php print $user_details_authored_joined_title; ?>:</div>
        <div class="result"><?php print $user_details_authored_joined_result; ?></div>
      </div>
    <?php endif; ?>
    <?php if (variable_get('user_details_authored_postcount_display') != 0): ?>
      <div class="posts-count">
        <div class="title"><?php print $user_details_authored_postcount_title; ?>:</div>
        <div class="result"><?php print $user_details_authored_postcount_result; ?></div>
      </div>
    <?php endif; ?>
    <?php if (variable_get('user_details_authored_points_display') != 0 && module_exists('userpoints')): ?>
      <div class="points">
        <div class="title"><?php print $user_details_authored_points_title; ?>:</div>
        <div class="result"><?php print $user_details_authored_points_result; ?></div>
      </div>
    <?php endif; ?>
    <?php if (variable_get('user_details_authored_rank_display') != 0): ?>
      <div class="rank">
        <div class="title"><?php print $user_details_authored_rank_title; ?>:</div>
        <div class="result"><?php print $user_details_authored_rank_result; ?></div>
      </div>
    <?php endif; ?>
    <?php if (variable_get('user_details_authored_stats_hr_display') != 0): ?>
      <?php print $user_details_authored_stats_hr; ?>
    <?php endif; ?>
    <?php if (variable_get('user_details_authored_profilelink_display') != 0 || variable_get('user_details_authored_privatemsglink_display') != 0 && module_exists('privatemsg')): ?>
      <div class="user-quick-links">
        <div class="title">User Links</div>
        <?php if (variable_get('user_details_authored_profilelink_display') != 0): ?>
          <div class="profile-link">
            <a href="<?php print $user_details_authored_profilelink_url; ?>"><img src="<?php print $user_details_authored_profilelink_imgsrc; ?>" title="<?php print $user_details_authored_profilelink_imgtitle; ?>" width="20px" height="20px" /></a>
          </div>
        <?php endif; ?>
        <?php if (variable_get('user_details_authored_privatemsglink_display') != 0): ?>
          <div class="privatemsg-link">
            <a href="<?php print $user_details_authored_privatemsglink_url; ?>"><img src="<?php print $user_details_authored_privatemsglink_imgsrc; ?>" title="<?php print $user_details_authored_privatemsglink_imgtitle; ?>" width="20px" height="20px" /></a>
            
          </div>
        <?php endif; ?>
      </div>
      <div class="block-end"></div>
    <?php endif; ?>
    <?php if (variable_get('user_details_authored_links_hr_display') != 0): ?>
      <?php print $user_details_authored_links_hr; ?>
    <?php endif; ?>
    <?php if (variable_get('user_details_authored_content_display') != 0 && variable_get('user_details_authored_content_amount') != 0): ?>
      <div class="content">
        <div class="title">Author's Content</div>
        <ul class="result">
          <?php print $user_details_authored_content; ?>
        </ul>
      </div>
    <?php endif; ?>
    <div class="block-end"></div>
  </div>
</div>