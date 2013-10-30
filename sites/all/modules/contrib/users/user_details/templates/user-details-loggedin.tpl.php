<?php
GLOBAL $user;
/**
 * @file
 * Default theme implementation to present all variables to the theme layer for
 * the logged-in user block of the user_details module.
 *
 * Useable variables: (syntax: <?php print variable; ?>)
 * - $user_details_loggedin_name (user name of the logged-in user)
 * - $user_details_loggedin_avatar (user avatar of the logged-in user)
 * - $user_details_loggedin_joined (logged-in user's account creation date)
 * - $user_details_loggedin_postcount (number of posts the logged-in user has created)
 * - $user_details_loggedin_points (number of user points the logged-in user has)
 * - $user_details_loggedin_rank (logged-in user's user role)
 * - $user_details_loggedin_content (logged-in user's 3 most recently updated pieces of content)
 * - $user_details_loggedin_profilelink (link to the logged-in users profile)
 * - $user_details_loggedin_subscriptionslink (link to the logged-in user's subscription overview tab on thier profile)
 * - $user_details_loggedin_createlink (link to the create content page)
 * - $user_details_loggedin_logoutlink (link to logout the logged-in user)
 */
?>
<div id="user-details">
  <div id="loggedin">
    <?php if (variable_get('user_details_loggedin_avatar_display') != 0): ?>
      <div class="avatar"><?php print $user_details_loggedin_avatar; ?></div>
    <?php endif; ?>
    <?php if (variable_get('user_details_loggedin_joined_display')!= 0): ?>
      <div class="joined">
        <div class="title"><?php print $user_details_loggedin_joined_title; ?>:</div>
        <div class="result"><?php print $user_details_loggedin_joined_result; ?></div>
      </div>
    <?php endif; ?>
    <?php if (variable_get('user_details_loggedin_postcount_display') != 0): ?>
      <div class="posts-count">
        <div class="title"><?php print $user_details_loggedin_postcount_title; ?>:</div>
        <div class="result"><?php print $user_details_loggedin_postcount_result; ?></div>
      </div>
    <?php endif; ?>
    <?php if (variable_get('user_details_loggedin_points_display') != 0 && module_exists('userpoints')): ?>
      <div class="points">
        <div class="title"><?php print $user_details_loggedin_points_title; ?>:</div>
        <div class="result"><?php print $user_details_loggedin_points_result; ?></div>
      </div>
    <?php endif; ?>
    <?php if (variable_get('user_details_loggedin_privatemsg_display') != 0 && module_exists('privatemsg')): ?>
    <div class="private-message-count">
      <div class="title"><?php print $user_details_loggedin_privatemsg_count_title; ?>:</div>
      <div class="result"><?php print $user_details_loggedin_privatemsg_count_result; ?></div>
    </div>
    <?php endif; ?>
    <?php if (variable_get('user_details_loggedin_rank_display') != 0): ?>
      <div class="rank">
        <div class="title"><?php print $user_details_loggedin_rank_title; ?>:</div>
        <div class="result"><?php print $user_details_loggedin_rank_result; ?></div>
      </div>
    <?php endif; ?>
    <?php if (variable_get('user_details_loggedin_stats_hr_display') != 0): ?>
      <?php print $user_details_loggedin_stats_hr; ?>
    <?php endif; ?>
    <?php if (variable_get('user_details_loggedin_frontlink_display') != 0 || variable_get('user_details_loggedin_profilelink_display') != 0 || variable_get('user_details_loggedin_profileeditlink_display') != 0 || variable_get('user_details_loggedin_privatemsglink_display') != 0 && module_exists('privatemsg') || variable_get('user_details_loggedin_createlink_display') != 0 || variable_get('user_details_loggedin_customlinkone_type') == '2' || variable_get('user_details_loggedin_customlinktwo_type') == '2' || variable_get('user_details_loggedin_customlinkthree_type') == '2' || variable_get('user_details_loggedin_customlinkfour_type') == '2' || variable_get('user_details_loggedin_customlinkfive_type') == '2'): ?>
      <div class="user-quick-links">
        <div class="title">User Links</div>
        <?php if (variable_get('user_details_loggedin_frontlink_display') != 0): ?>
          <div class="front-link">
            <a href="<?php print $user_details_loggedin_frontlink_url; ?>"><img src="<?php print $user_details_loggedin_frontlink_imgsrc; ?>" title="<?php print $user_details_loggedin_frontlink_imgtitle; ?>" width="20px" height="20px" /></a>
          </div>
        <?php endif; ?>
        <?php if (variable_get('user_details_loggedin_profilelink_display') != 0): ?>
          <div class="profile-link">
            <a href="<?php print $user_details_loggedin_profilelink_url; ?>"><img src="<?php print $user_details_loggedin_profilelink_imgsrc; ?>" title="<?php print $user_details_loggedin_profilelink_imgtitle; ?>" width="20px" height="20px" /></a>
          </div>
        <?php endif; ?>
        <?php if (variable_get('user_details_loggedin_profileeditlink_display') != 0): ?>
          <div class="profileedit-link">
            <a href="<?php print $user_details_loggedin_profileeditlink_url; ?>"><img src="<?php print $user_details_loggedin_profileeditlink_imgsrc; ?>" title="<?php print $user_details_loggedin_profileeditlink_imgtitle; ?>" width="20px" height="20px" /></a>
          </div>
        <?php endif; ?>
        <?php if (variable_get('user_details_loggedin_privatemsglink_display') != 0): ?>
          <div class="privatemsg-link">
            <a href="<?php print $user_details_loggedin_privatemsglink_url; ?>"><img src="<?php print $user_details_loggedin_privatemsglink_imgsrc; ?>" title="<?php print $user_details_loggedin_privatemsglink_imgtitle; ?>" width="20px" height="20px" /></a>
            
          </div>
        <?php endif; ?>
        <?php if (variable_get('user_details_loggedin_createlink_display') != 0): ?>
          <div class="create-link">
            <a href="<?php print $user_details_loggedin_createlink_url; ?>"><img src="<?php print $user_details_loggedin_createlink_imgsrc; ?>" title="<?php print $user_details_loggedin_createlink_imgtitle; ?>" width="20px" height="20px" /></a>
          </div>
        <?php endif; ?>
        <?php if (variable_get('user_details_loggedin_logoutlink_display') != 0): ?>
          <div class="logout-link">
            <a href="<?php print $user_details_loggedin_logoutlink_url; ?>"><img src="<?php print $user_details_loggedin_logoutlink_imgsrc; ?>" title="<?php print $user_details_loggedin_logoutlink_imgtitle; ?>" width="20px" height="20px" /></a>
          </div>
        <?php endif; ?>
        <?php if (variable_get('user_details_loggedin_customlinkone_type') == '2'): ?>
          <div class="custom-link-one">
            <a href="<?php print $user_details_loggedin_customlinkone_url; ?>"><img src="<?php print $user_details_loggedin_customlinkone_imgsrc; ?>" title="<?php print $user_details_loggedin_customlinkone_imgtitle; ?>" width="20px" height="20px" /></a>
          </div>
        <?php endif; ?>
        <?php if (variable_get('user_details_loggedin_customlinktwo_type') == '2'): ?>
          <div class="custom-link-two">
            <a href="<?php print $user_details_loggedin_customlinktwo_url; ?>"><img src="<?php print $user_details_loggedin_customlinktwo_imgsrc; ?>" title="<?php print $user_details_loggedin_customlinktwo_imgtitle; ?>" width="20px" height="20px" /></a>
          </div>
        <?php endif; ?>
        <?php if (variable_get('user_details_loggedin_customlinkthree_type') == '2'): ?>
          <div class="custom-link-three">
            <a href="<?php print $user_details_loggedin_customlinkthree_url; ?>"><img src="<?php print $user_details_loggedin_customlinkthree_imgsrc; ?>" title="<?php print $user_details_loggedin_customlinkthree_imgtitle; ?>" width="20px" height="20px" /></a>
          </div>
        <?php endif; ?>
        <?php if (variable_get('user_details_loggedin_customlinkfour_type') == '2'): ?>
          <div class="custom-link-four">
            <a href="<?php print $user_details_loggedin_customlinkfour_url; ?>"><img src="<?php print $user_details_loggedin_customlinkfour_imgsrc; ?>" title="<?php print $user_details_loggedin_customlinkfour_imgtitle; ?>" width="20px" height="20px" /></a>
          </div>
        <?php endif; ?>
        <?php if (variable_get('user_details_loggedin_customlinkfive_type') == '2'): ?>
          <div class="custom-link-five">
            <a href="<?php print $user_details_loggedin_customlinkfive_url; ?>"><img src="<?php print $user_details_loggedin_customlinkfive_imgsrc; ?>" title="<?php print $user_details_loggedin_customlinkfive_imgtitle; ?>" width="20px" height="20px" /></a>
          </div>
        <?php endif; ?>
      </div>
      <div class="block-end"></div>
    <?php endif; ?>
    <?php if (user_access('administor content')): ?>
      <?php if (variable_get('user_details_loggedin_adminlink_display') !=0 || variable_get('user_details_loggedin_panelslink_display') != 0 && module_exists('panels') || variable_get('user_details_loggedin_viewslink_display') && module_exists('views') || variable_get('user_details_loggedin customlinkone_type') == '3' || variable_get('user_details_loggedin customlinktwo_type') == '3' || variable_get('user_details_loggedin customlinkthree_type') == '3' || variable_get('user_details_loggedin customlinkfour_type') == '3' || variable_get('user_details_loggedin customlinkfive_type') == '3'): ?>
        <div class="admin-quick-links">
          <div class="title">Admin Links</div>
          <?php if (variable_get('user_details_loggedin_adminlink_display') != 0): ?>
            <div class="admin-link">
              <a href="<?php print $user_details_loggedin_adminlink_url; ?>"><img src="<?php print $user_details_loggedin_adminlink_imgsrc; ?>" title="<?php print $user_details_loggedin_adminlink_imgtitle; ?>" width="20px" height="20px" /></a>
            </div>
          <?php endif; ?>
          <?php if (variable_get('user_details_loggedin_panelslink_display') != 0 && module_exists('panels')): ?>
            <div class="panels-link">
              <a href="<?php print $user_details_loggedin_panelslink_url; ?>"><img src="<?php print $user_details_loggedin_panelslink_imgsrc; ?>" title="<?php print $user_details_loggedin_panelslink_imgtitle; ?>" width="20px" height="20px" /></a>
            </div>
          <?php endif; ?>
          <?php if (variable_get('user_details_loggedin_viewslink_display') != 0 && module_exists('views')): ?>
            <div class="views-link">
              <a href="<?php print $user_details_loggedin_viewslink_url; ?>"><img src="<?php print $user_details_loggedin_viewslink_imgsrc; ?>" title="<?php print $user_details_loggedin_viewslink_imgtitle; ?>" width="20px" height="20px" /></a>
            </div>
          <?php endif; ?>
          <?php if (variable_get('user_details_loggedin_performancelink_display') != 0): ?>
            <div class="performance-link">
              <a href="<?php print $user_details_loggedin_performancelink_url; ?>"><img src="<?php print $user_details_loggedin_performancelink_imgsrc; ?>" title="<?php print $user_details_loggedin_performancelink_imgtitle; ?>" width="20px" height="20px" /></a>
            </div>
          <?php endif; ?>
          <?php if (variable_get('user_details_loggedin_customlinkone_type') == '3'): ?>
            <div class="custom-link-one">
              <a href="<?php print $user_details_loggedin_customlinkone_url; ?>"><img src="<?php print $user_details_loggedin_customlinkone_imgsrc; ?>" title="<?php print $user_details_loggedin_customlinkone_imgtitle; ?>" width="20px" height="20px" /></a>
            </div>
          <?php endif; ?>
          <?php if (variable_get('user_details_loggedin_customlinktwo_type') == '3'): ?>
            <div class="custom-link-two">
              <a href="<?php print $user_details_loggedin_customlinktwo_url; ?>"><img src="<?php print $user_details_loggedin_customlinktwo_imgsrc; ?>" title="<?php print $user_details_loggedin_customlinktwo_imgtitle; ?>" width="20px" height="20px" /></a>
            </div>
          <?php endif; ?>
          <?php if (variable_get('user_details_loggedin_customlinkthree_type') == '3'): ?>
            <div class="custom-link-three">
              <a href="<?php print $user_details_loggedin_customlinkthree_url; ?>"><img src="<?php print $user_details_loggedin_customlinkthree_imgsrc; ?>" title="<?php print $user_details_loggedin_customlinkthree_imgtitle; ?>" width="20px" height="20px" /></a>
            </div>
          <?php endif; ?>
          <?php if (variable_get('user_details_loggedin_customlinkfour_type') == '3'): ?>
            <div class="custom-link-four">
              <a href="<?php print $user_details_loggedin_customlinkfour_url; ?>"><img src="<?php print $user_details_loggedin_customlinkfour_imgsrc; ?>" title="<?php print $user_details_loggedin_customlinkfour_imgtitle; ?>" width="20px" height="20px" /></a>
            </div>
          <?php endif; ?>
          <?php if (variable_get('user_details_loggedin_customlinkfive_type') == '3'): ?>
            <div class="custom-link-one">
              <a href="<?php print $user_details_loggedin_customlinkfive_url; ?>"><img src="<?php print $user_details_loggedin_customlinkfive_imgsrc; ?>" title="<?php print $user_details_loggedin_customlinkfive_imgtitle; ?>" width="20px" height="20px" /></a>
            </div>
          <?php endif; ?>
        </div>
      <?php endif; ?>
      <div class="block-end"></div>
    <?php endif; ?>
    <?php if (variable_get('user_details_loggedin_links_hr_display') != 0): ?>
      <?php print $user_details_loggedin_links_hr; ?>
    <?php endif; ?>
    <?php if (variable_get('user_details_loggedin_content_display') != 0 && variable_get('user_details_loggedin_content_amount') != 0): ?>
      <div class="content">
        <div class="title">My Content</div>
        <ul class="result">
          <?php print $user_details_loggedin_content; ?>
        </ul>
      </div>
    <?php endif; ?>
    <div class="block-end"></div>
  </div>
</div>