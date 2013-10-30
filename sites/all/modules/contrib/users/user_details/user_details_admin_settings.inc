<?php
function user_details_admin_settings() {
  // Add the css that is needed for the admin form
  drupal_add_css(drupal_get_path('module', 'user_details') . '/css/user_details_admin.css');

  $overview = t('The User Details module is a simple module to help the end-user find thier way around a website by adding a central location for important link, stats, and thier content.');
  $overview .= '<br/>';
  $overview .= t('The User Details module is broken up into two blocks: logged-in and authored by. For a more detailed overview please visit the ') . '<a href="/admin/help/user_details">' . t('User Details help page') . '</a>';

  $loggedin_header = '<hr>';
  $loggedin_header .= '<h3>' . t('User Details: logged-in user settings') . '</h3>';

  $authored_header = '<hr>';
  $authored_header .= '<h3>' . t('User Details: authored user settings') . '</h3>'; 

  $hr = '<hr>';

  $form['overview'] = array(
    '#markup' => $overview,
  );
  $form['loggedin_header'] = array(
    '#markup' => $loggedin_header,
  );
  $form['loggedin_stats'] = array(
    '#type' => 'fieldset',
    '#title' => 'User Stats.',
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['loggedin_stats']['user_details_loggedin_avatar_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display the "User Avatar".'),
    '#default_value' => variable_get('user_details_loggedin_avatar_display', FALSE),
    '#description' => t('Displays the Avatar of the user, if any is available.')
  );
  $form['loggedin_stats']['user_details_loggedin_joined_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display the "Joined Date".'),
    '#default_value' => variable_get('user_details_loggedin_joined_display', FALSE),
    '#description' => t('Displays the account creation date of the user.')
  );  
  $form['loggedin_stats']['user_details_loggedin_postcount_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display the "Post count"'),
    '#default_value' => variable_get('user_details_loggedin_postcount_display', FALSE),
    '#description' => t('Displays the user\'s current number of posts.'),
  );   
  if (module_exists('userpoints')) {
    $form['loggedin_stats']['user_details_loggedin_points_display'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display the "User Points".'),
      '#default_value' => variable_get('user_details_loggedin_points_display', FALSE),
      '#description' => t('Displays the user\'s "User Points" amount.'),
      '#disabled' => FALSE,
    );
  }
  else {
    $form['loggedin_stats']['user_details_loggedin_points_display'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display the "User Points".'),
      '#default_value' => variable_get('user_details_loggedin_points_display', FALSE),
      '#description' => t('Please install <a href="http://drupal.org/project/userpoints">User Points</a>'),
      '#disabled' => TRUE,
    );
  } 
  $form['loggedin_stats']['user_details_loggedin_rank_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display the role.'),
    '#default_value' => variable_get('user_details_loggedin_rank_display', FALSE),
    '#description' => t('Displays the user\'s role name.'),
  );
  if (module_exists('privatemsg')) {
    $form['loggedin_stats']['user_details_loggedin_privatemsg_display'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display the unread message amount.'),
      '#default_value' => variable_get('user_details_loggedin_privatemsg_display', FALSE),
      '#description' => t('Displays the unread message amount from the "Private Messages" module.'),
      '#disabled' => FALSE,
    );
  }
  else {
    $form['loggedin_stats']['user_details_loggedin_privatemsg_display'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display the unread message amount.'),
      '#default_value' => variable_get('user_details_loggedin_privatemsg_display', FALSE),
      '#description' => t('Please install <a href="http://drupal.org/project/privatemsg">Private Messages</a>'),
      '#disabled' => TRUE,
    );
  }
  
  $form['loggedin_stats_hr'] = array(
    '#type' => 'fieldset',
    '#title' => 'Horizontal Ruler.',
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['loggedin_stats_hr']['user_details_loggedin_stats_hr_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display "HR"'),
    '#default_value' => variable_get('user_details_loggedin_stats_hr_display', FALSE),
    '#description' => t('Displays a hortizontal ruler html enity seprating the stats and links sections.'),
  );

  //Links Options
  $form['loggedin_links'] = array(
    '#type' => 'fieldset',
    '#title' => 'Links.',
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['loggedin_links']['front_link'] = array(
    '#type' => 'fieldset',
    '#title' => t('Front Link'),
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['loggedin_links']['front_link']['user_details_loggedin_frontlink_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display'),
    '#default_value' => variable_get('user_details_loggedin_frontlink_display', FALSE),
    '#description' => t('Displays an icon link leading to the site\'s front page.'),
  );
  $form['loggedin_links']['front_link']['user_details_loggedin_frontlink_imgsrc'] = array(
    '#type' => 'textfield',
    '#title' => t('Image source.'),
    '#default_value' => variable_get('user_details_loggedin_frontlink_imgsrc', "/" . drupal_get_path('module', 'user_details') . "/images/front-icon.png"),
    '#description' => t('default value: <i>/' . drupal_get_path('module', 'user_details') . '/images/front-icon.png</i>'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  $form['loggedin_links']['profile_link'] = array(
    '#type' => 'fieldset',
    '#title' => t('Profile Link'),
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['loggedin_links']['profile_link']['user_details_loggedin_profilelink_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display'),
    '#default_value' => variable_get('user_details_loggedin_profilelink_display', FALSE),
    '#description' => t('Displays an icon link leading to the user\'s profile page.'),
  );
  $form['loggedin_links']['profile_link']['user_details_loggedin_profilelink_imgsrc'] = array(
    '#type' => 'textfield',
    '#title' => t('Image source.'),
    '#default_value' => variable_get('user_details_loggedin_profilelink_imgsrc', "/" . drupal_get_path('module', 'user_details') . "/images/profile-icon.png"),
    '#description' => t('default value: <i>/' . drupal_get_path('module', 'user_details') . '/images/profile-icon.png</i>'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  $form['loggedin_links']['profile_edit_link'] = array(
    '#type' => 'fieldset',
    '#title' => t('Profile Edit Link'),
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['loggedin_links']['profile_edit_link']['user_details_loggedin_profileeditlink_display'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display'),
      '#default_value' => variable_get('user_details_loggedin_profileeditlink_display', FALSE),
      '#description' => t('Displays an icon link leading to the user\'s edit profile page.')
  );
  $form['loggedin_links']['profile_edit_link']['user_details_loggedin_profileeditlink_imgsrc'] = array(
    '#type' => 'textfield',
    '#title' => t('Image source.'),
    '#default_value' => variable_get('user_details_loggedin_profileeditlink_imgsrc', "/" . drupal_get_path('module', 'user_details') . "/images/profileedit-icon.png"),
    '#description' => t('default value: <i>/' . drupal_get_path('module', 'user_details') . '/images/profileedit-icon.png</i>'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  $form['loggedin_links']['privatemsg_link'] = array(
    '#type' => 'fieldset',
    '#title' => t('Private Message Link'),
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  if (module_exists('privatemsg')) {
    $form['loggedin_links']['privatemsg_link']['user_details_loggedin_privatemsglink_display'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display'),
      '#default_value' => variable_get('user_details_loggedin_privatemsglink_display', FALSE),
      '#description' => t('Displays an icon link leading to the user\'s private message profile page.'),
      '#disabled' => FALSE,
    );
  }
  else {
    $form['loggedin_links']['privatemsg_link']['user_details_loggedin_privatemsglink_display'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display'),
      '#default_value' => variable_get('user_details_loggedin_privatemsglink_display', FALSE),
      '#description' => t('please install <a href="http://drupal.org/project/privatemsg">Private Message</a>.'),
      '#disabled' => TRUE,
    );
  }
  if (module_exists('privatemsg')) {
    $form['loggedin_links']['privatemsg_link']['user_details_loggedin_privatemsglink_imgsrc'] = array(
      '#type' => 'textfield',
      '#title' => t('Image source.'),
      '#default_value' => variable_get('user_details_loggedin_privatemsg_imgsrc', "/" . drupal_get_path('module', 'user_details') . "/images/privatemsg-icon.png"),
      '#description' => t('default value: <i>/' . drupal_get_path('module', 'user_details') . '/images/privatemsg-icon.png</i>'),
      '#size' => 75,
      '#maxlength' => 500,
    );
  }
  $form['loggedin_links']['create_link'] = array(
    '#type' => 'fieldset',
    '#title' => t('Create Link'),
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['loggedin_links']['create_link']['user_details_loggedin_createlink_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display'),
    '#default_value' => variable_get('user_details_loggedin_createlink_display', FALSE),
    '#description' => t('Displays an icon link to the /node/add page'),
  );
  $form['loggedin_links']['create_link']['user_details_loggedin_createlink_imgsrc'] = array(
    '#type' => 'textfield',
    '#title' => t('Image source.'),
    '#default_value' => variable_get('user_details_loggedin_createlink_imgsrc', "/" . drupal_get_path('module', 'user_details') . "/images/create-icon.png"),
    '#description' => t('default value: <i>/' . drupal_get_path('module', 'user_details') . '/images/create-icon.png</i>'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  $form['loggedin_links']['admin_link'] = array(
    '#type' => 'fieldset',
    '#title' => t('Admin Link'),
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['loggedin_links']['admin_link']['user_details_loggedin_adminlink_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display'),
    '#default_value' => variable_get('user_details_loggedin_adminlink_display', FALSE),
    '#description' => t('Displays an icon link to the admin page.')
  );
  $form['loggedin_links']['admin_link']['user_details_loggedin_adminlink_imgsrc'] = array(
    '#type' => 'textfield',
    '#title' => t('Image source.'),
    '#default_value' => variable_get('user_details_loggedin_adminlink_imgsrc', "/" . drupal_get_path('module', 'user_details') . "/images/admin-icon.png"),
    '#description' => t('default value: <i>/' . drupal_get_path('module', 'user_details') . '/images/admin-icon.png</i>'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  $form['loggedin_links']['panels_link'] = array(
    '#type' => 'fieldset',
    '#title' => t('Panels Link'),
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  if (module_exists('panels')) {
    $form['loggedin_links']['panels_link']['user_details_loggedin_panelslink_display'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display'),
      '#default_value' => variable_get('user_details_loggedin_panelslink_display', FALSE),
      '#description' => t('Displays an icon link to the admin section of the "Panels" module.')
    );
  }
  else {
    $form['loggedin_links']['panels_link']['user_details_loggedin_panelslink_display'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display'),
      '#default_value' => variable_get('user_details_loggedin_panelslink_display', FALSE),
      '#description' => t('Please install <a href="http://drupal.org/project/panels">Panels</a>'),
      '#disabled' => TRUE,
    );
  }
  if (module_exists('panels')) {
    $form['loggedin_links']['panels_link']['user_details_loggedin_panelslink_imgsrc'] = array(
      '#type' => 'textfield',
      '#title' => t('Image source.'),
      '#default_value' => variable_get('user_details_loggedin_panelslink_imgsrc', "/" . drupal_get_path('module', 'user_details') . "/images/panels-icon.png"),
      '#description' => t('default value: <i>/' . drupal_get_path('module', 'user_details') . '/images/panels-icon.png</i>'),
      '#size' => 75,
      '#maxlength' => 500,
    );
  }
  $form['loggedin_links']['views_link'] = array(
    '#type' => 'fieldset',
    '#title' => t('Views Link'),
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  if (module_exists('views')) {
    $form['loggedin_links']['views_link']['user_details_loggedin_viewslink_display'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display'),
      '#default_value' => variable_get('user_details_loggedin_viewslink_display', FALSE),
      '#description' => t('Displays an icon link to the admin section of the "Views" module.')
    );
  }
  else {
    $form['loggedin_links']['views_link']['user_details_loggedin_viewslink_display'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display'),
      '#default_value' => variable_get('user_details_loggedin_viewslink_display', FALSE),
      '#description' => t('Please install <a href="http://drupal.org/project/views">Panels</a>'),
      '#disabled' => TRUE,
    );
  }
  if (module_exists('views')) {
    $form['loggedin_links']['views_link']['user_details_loggedin_viewslink_imgsrc'] = array(
      '#type' => 'textfield',
      '#title' => t('Image source.'),
      '#default_value' => variable_get('user_details_loggedin_viewslink_imgsrc', "/" . drupal_get_path('module', 'user_details') . "/images/views-icon.png"),
      '#description' => t('default value: <i>/' . drupal_get_path('module', 'user_details') . '/images/views-icon.png</i>'),
      '#size' => 75,
      '#maxlength' => 500,
    );
  }
  $form['loggedin_links']['performance_link'] = array(
    '#type' => 'fieldset',
    '#title' => t('Performance Link'),
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['loggedin_links']['performance_link']['user_details_loggedin_performancelink_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display'),
    '#default_value' => variable_get('user_details_loggedin_performancelink_display', FALSE),
    '#description' => t('Displays an icon link to the admin section of the "Views" module.')
  );
  $form['loggedin_links']['performance_link']['user_details_loggedin_performancelink_imgsrc'] = array(
    '#type' => 'textfield',
    '#title' => t('Image source.'),
    '#default_value' => variable_get('user_details_loggedin_performancelink_imgsrc', "/" . drupal_get_path('module', 'user_details') . "/images/performance-icon.png"),
    '#description' => t('default value: <i>/' . drupal_get_path('module', 'user_details') . '/images/performance-icon.png</i>'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  $form['loggedin_links']['logout_link'] = array(
    '#type' => 'fieldset',
    '#title' => t('Logout Link'),
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['loggedin_links']['logout_link']['user_details_loggedin_logoutlink_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display'),
    '#default_value' => variable_get('user_details_loggedin_logoutlink_display', FALSE),
    '#description' => t('Displays an icon link to allow the user to logout.')
  );
  $form['loggedin_links']['logout_link']['user_details_loggedin_logoutlink_imgsrc'] = array(
    '#type' => 'textfield',
    '#title' => t('Image source.'),
    '#default_value' => variable_get('user_details_loggedin_logoutlink_imgsrc', "/" . drupal_get_path('module', 'user_details') . "/images/logout-icon.png"),
    '#description' => t('It is the URL relative to your drupal install. Do not include your domain name.(http://www.example.com)'),
    '#size' => 75,
    '#maxlength' => 500,
  );

  //Custom Link One Options
  $form['loggedin_links']['custom_link_one'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom Link One'),
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['loggedin_links']['custom_link_one']['user_details_loggedin_customlinkone_type'] = array(
    '#type' => 'select',
    '#title' => t('Link Type'),
    '#options' => array(
      0 => t('Disabled'),
      2 => t('User Link'),
      3 => t('Admin Link'),
    ),
    '#default_value' => variable_get('user_details_loggedin_customlinkone_type', '0'),
    '#description' => t('Choose which type of link this link is.'),
  );
  $form['loggedin_links']['custom_link_one']['user_details_loggedin_customlinkone_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL path.'),
    '#default_value' => variable_get('user_details_loggedin_customlinkone_url', ''),
    '#description' => t('the url of the page you want this link to refer to. (example: /admin/structure/pages)'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  $form['loggedin_links']['custom_link_one']['user_details_loggedin_customlinkone_imgsrc'] = array(
    '#type' => 'textfield',
    '#title' => t('Image path.'),
    '#default_value' => variable_get('user_details_loggedin_customlinkone_imgsrc', ''),
    '#description' => t('the path to your image. (example: /sites/all/themes/my-theme/custom-link-one.png)'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  $form['loggedin_links']['custom_link_one']['user_details_loggedin_customlinkone_imgtitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Image title.'),
    '#default_value' => variable_get('user_details_loggedin_customlinkone_imgtitle', ''),
    '#description' => t('The image title, or mouse-over tooltip, of the image.'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  //Custom Link Two Options
  $form['loggedin_links']['custom_link_two'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom Link Two'),
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['loggedin_links']['custom_link_two']['user_details_loggedin_customlinktwo_type'] = array(
    '#type' => 'select',
    '#title' => t('Link Type'),
    '#options' => array(
      0 => t('Disabled'),
      2 => t('User Link'),
      3 => t('Admin Link'),
    ),
    '#default_value' => variable_get('user_details_loggedin_customlinktwo_type', '0'),
    '#description' => t('Choose which type of link this link is.'),
  );
  $form['loggedin_links']['custom_link_two']['user_details_loggedin_customlinktwo_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL path.'),
    '#default_value' => variable_get('user_details_loggedin_customlinktwo_url', ''),
    '#description' => t('the url of the page you want this link to refer to. (example: /admin/structure/pages)'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  $form['loggedin_links']['custom_link_two']['user_details_loggedin_customlinktwo_imgsrc'] = array(
    '#type' => 'textfield',
    '#title' => t('Image path.'),
    '#default_value' => variable_get('user_details_loggedin_customlinktwo_imgsrc', ''),
    '#description' => t('the path to your image. (example: /sites/all/themes/my-theme/custom-link-two.png)'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  $form['loggedin_links']['custom_link_two']['user_details_loggedin_customlinktwo_imgtitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Image title.'),
    '#default_value' => variable_get('user_details_loggedin_customlinktwo_imgtitle', ''),
    '#description' => t('The image title, or mouse-over tooltip, of the image.'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  //Custom Link Three Options
  $form['loggedin_links']['custom_link_three'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom Link Three'),
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['loggedin_links']['custom_link_three']['user_details_loggedin_customlinkthree_type'] = array(
    '#type' => 'select',
    '#title' => t('Link Type'),
    '#options' => array(
      0 => t('Disabled'),
      2 => t('User Link'),
      3 => t('Admin Link'),
    ),
    '#default_value' => variable_get('user_details_loggedin_customlinkthree_type', '0'),
    '#description' => t('Choose which type of link this link is.'),
  );
  $form['loggedin_links']['custom_link_three']['user_details_loggedin_customlinkthree_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL path.'),
    '#default_value' => variable_get('user_details_loggedin_customlinkthree_url', ''),
    '#description' => t('the url of the page you want this link to refer to. (example: /admin/structure/pages)'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  $form['loggedin_links']['custom_link_three']['user_details_loggedin_customlinkthree_imgsrc'] = array(
    '#type' => 'textfield',
    '#title' => t('Image path.'),
    '#default_value' => variable_get('user_details_loggedin_customlinkthree_imgsrc', ''),
    '#description' => t('the path to your image. (example: /sites/all/themes/my-theme/custom-link-three.png)'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  $form['loggedin_links']['custom_link_three']['user_details_loggedin_customlinkthree_imgtitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Image title.'),
    '#default_value' => variable_get('user_details_loggedin_customlinkthree_imgtitle', ''),
    '#description' => t('The image title, or mouse-over tooltip, of the image.'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  
  //Custom Link Four Options
  $form['loggedin_links']['custom_link_four'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom Link Four'),
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['loggedin_links']['custom_link_four']['user_details_loggedin_customlinkfour_type'] = array(
    '#type' => 'select',
    '#title' => t('Link Type'),
    '#options' => array(
      0 => t('Disabled'),
      2 => t('User Link'),
      3 => t('Admin Link'),
    ),
    '#default_value' => variable_get('user_details_loggedin_customlinkfour_type', '0'),
    '#description' => t('Choose which type of link this link is.'),
  );
  $form['loggedin_links']['custom_link_four']['user_details_loggedin_customlinkfour_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL path.'),
    '#default_value' => variable_get('user_details_loggedin_customlinkfour_url', ''),
    '#description' => t('the url of the page you want this link to refer to. (example: /admin/structure/pages)'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  $form['loggedin_links']['custom_link_four']['user_details_loggedin_customlinkfour_imgsrc'] = array(
    '#type' => 'textfield',
    '#title' => t('Image path.'),
    '#default_value' => variable_get('user_details_loggedin_customlinkfour_imgsrc', ''),
    '#description' => t('the path to your image. (example: /sites/all/themes/my-theme/custom-link-four.png)'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  $form['loggedin_links']['custom_link_four']['user_details_loggedin_customlinkfour_imgtitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Image title.'),
    '#default_value' => variable_get('user_details_loggedin_customlinkfour_imgtitle', ''),
    '#description' => t('The image title, or mouse-over tooltip, of the image.'),
    '#size' => 75,
    '#maxlength' => 500,
  );
 
  //Custom Link Five Options
  $form['loggedin_links']['custom_link_five'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom Link Five'),
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['loggedin_links']['custom_link_five']['user_details_loggedin_customlinkfive_type'] = array(
    '#type' => 'select',
    '#title' => t('Link Type'),
    '#options' => array(
      0 => t('Disabled'),
      2 => t('User Link'),
      3 => t('Admin Link'),
    ),
    '#default_value' => variable_get('user_details_loggedin_customlinkfive_type', '0'),
    '#description' => t('Choose which type of link this link is.'),
  );
  $form['loggedin_links']['custom_link_five']['user_details_loggedin_customlinkfive_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL path.'),
    '#default_value' => variable_get('user_details_loggedin_customlinkfive_url', ''),
    '#description' => t('the url of the page you want this link to refer to. (example: /admin/structure/pages)'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  $form['loggedin_links']['custom_link_five']['user_details_loggedin_customlinkfive_imgsrc'] = array(
    '#type' => 'textfield',
    '#title' => t('Image path.'),
    '#default_value' => variable_get('user_details_loggedin_customlinkfive_imgsrc', ''),
    '#description' => t('the path to your image. (example: /sites/all/themes/my-theme/custom-link-five.png)'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  $form['loggedin_links']['custom_link_five']['user_details_loggedin_customlinkfive_imgtitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Image title.'),
    '#default_value' => variable_get('user_details_loggedin_customlinkfive_imgtitle', ''),
    '#description' => t('The image title, or mouse-over tooltip, of the image.'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  
  $form['loggedin_links_hr'] = array(
    '#type' => 'fieldset',
    '#title' => 'Horizontal Ruler.',
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['loggedin_links_hr']['user_details_loggedin_links_hr_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display "HR"'),
    '#default_value' => variable_get('user_details_loggedin_links_hr_display', FALSE),
    '#description' => t('Displays a hortizontal ruler html enity seprating the links and content sections.'),
  ); 

  //Content Options
  $form['loggedin_content'] = array(
    '#type' => 'fieldset',
    '#title' => 'Content.',
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  ); 
  $form['loggedin_content']['user_details_loggedin_content_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display "Content"'),
    '#default_value' => variable_get('user_details_loggedin_content_display', FALSE),
    '#description' => t('Lists the last X updated nodes authored by the user.')
  );
  $form['loggedin_content']['user_details_loggedin_content_amount'] = array(
    '#type' => 'textfield',
    '#title' => t('User content amount'),
    '#default_value' => variable_get('user_details_loggedin_content_amount', 3),
    '#size' => 2,
    '#maxlength' => 2,
    '#description' => t('Changes the number of recent items listed for the "Content" list. (<b>if set to 0 it renders this list null.</b>)')
  );

/**
 * Authored options
 *
 * the authored by block settings.
 */
  $form['authored_header'] = array(
    '#markup' => $authored_header,
  );
  $form['authored_stats'] = array(
    '#type' => 'fieldset',
    '#title' => 'User Stats.',
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['authored_stats']['user_details_authored_avatar_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display the "User Avatar".'),
    '#default_value' => variable_get('user_details_authored_avatar_display', FALSE),
    '#description' => t('Displays the Avatar of the user, if any is available.')
  );
  $form['authored_stats']['user_details_authored_joined_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display the "Joined Date".'),
    '#default_value' => variable_get('user_details_authored_joined_display', FALSE),
    '#description' => t('Displays the account creation date of the user.')
  );  
  $form['authored_stats']['user_details_authored_postcount_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display the "Post count"'),
    '#default_value' => variable_get('user_details_authored_postcount_display', FALSE),
    '#description' => t('Displays the user\'s current number of posts.'),
  );   
  if (module_exists('userpoints')) {
    $form['authored_stats']['user_details_authored_points_display'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display the "User Points".'),
      '#default_value' => variable_get('user_details_authored_points_display', FALSE),
      '#description' => t('Displays the user\'s "User Points" amount.'),
      '#disabled' => FALSE,
    );
  }
  else {
    $form['authored_stats']['user_details_authored_points_display'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display the "User Points".'),
      '#default_value' => variable_get('user_details_authored_points_display', FALSE),
      '#description' => t('Please install <a href="http://drupal.org/project/userpoints">User Points</a>'),
      '#disabled' => TRUE,
    );
  } 
  $form['authored_stats']['user_details_authored_rank_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display the role.'),
    '#default_value' => variable_get('user_details_authored_rank_display', FALSE),
    '#description' => t('Displays the user\'s role name.'),
  );
  
  $form['authored_stats_hr'] = array(
    '#type' => 'fieldset',
    '#title' => 'Horizontal Ruler.',
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['authored_stats_hr']['user_details_authored_stats_hr_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display "HR"'),
    '#default_value' => variable_get('user_details_authored_stats_hr_display', FALSE),
    '#description' => t('Displays a hortizontal ruler html enity seprating the stats and links sections.'),
  );

  $form['authored_links'] = array(
    '#type' => 'fieldset',
    '#title' => 'Links.',
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['authored_links']['profile_link'] = array(
    '#type' => 'fieldset',
    '#title' => t('Profile Link'),
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['authored_links']['profile_link']['user_details_authored_profilelink_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display'),
    '#default_value' => variable_get('user_details_authored_profilelink_display', FALSE),
    '#description' => t('Displays an icon link leading to the user\'s profile page.'),
  );
  $form['authored_links']['profile_link']['user_details_authored_profilelink_imgsrc'] = array(
    '#type' => 'textfield',
    '#title' => t('Image source.'),
    '#default_value' => variable_get('user_details_authored_profilelink_imgsrc', "/" . drupal_get_path('module', 'user_details') . "/images/profile-icon.png"),
    '#description' => t('default value: <i>/' . drupal_get_path('module', 'user_details') . '/images/profile-icon.png</i>'),
    '#size' => 75,
    '#maxlength' => 500,
  );
  $form['authored_links']['privatemsg_link'] = array(
    '#type' => 'fieldset',
    '#title' => t('Private Message Link'),
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  if (module_exists('privatemsg')) {
    $form['authored_links']['privatemsg_link']['user_details_authored_privatemsglink_display'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display'),
      '#default_value' => variable_get('user_details_authored_privatemsglink_display', FALSE),
      '#description' => t('Displays an icon link leading to the user\'s private message profile page.'),
      '#disabled' => FALSE,
    );
  }
  else {
    $form['authored_links']['privatemsg_link']['user_details_authored_privatemsglink_display'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display'),
      '#default_value' => variable_get('user_details_authored_privatemsglink_display', FALSE),
      '#description' => t('please install <a href="http://drupal.org/project/privatemsg">Private Message</a>.'),
      '#disabled' => TRUE,
    );
  }
  if (module_exists('privatemsg')) {
    $form['authored_links']['privatemsg_link']['user_details_authored_privatemsglink_imgsrc'] = array(
      '#type' => 'textfield',
      '#title' => t('Image source.'),
      '#default_value' => variable_get('user_details_authored_privatemsg_imgsrc', "/" . drupal_get_path('module', 'user_details') . "/images/privatemsg-icon.png"),
      '#description' => t('default value: <i>/' . drupal_get_path('module', 'user_details') . '/images/privatemsg-icon.png</i>'),
      '#size' => 75,
      '#maxlength' => 500,
    );
  }
  
  $form['authored_links_hr'] = array(
    '#type' => 'fieldset',
    '#title' => 'Horizontal Ruler.',
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );
  $form['authored_links_hr']['user_details_authored_links_hr_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display "HR"'),
    '#default_value' => variable_get('user_details_authored_links_hr_display', FALSE),
    '#description' => t('Displays a hortizontal ruler html enity seprating the links and content sections.'),
  );

  //Content Options
  $form['authored_content'] = array(
    '#type' => 'fieldset',
    '#title' => 'Content.',
    '#collapsible' => 'true',
    '#collapsed' => 'true',
  );  
  $form['authored_content']['user_details_authored_content_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display "Content"'),
    '#default_value' => variable_get('user_details_authored_content_display', FALSE),
    '#description' => t('Lists the last X updated nodes authored by the user.')
  );
  $form['authored_content']['user_details_authored_content_amount'] = array(
    '#type' => 'textfield',
    '#title' => t('User content amount'),
    '#default_value' => variable_get('user_details_authored_content_amount', 3),
    '#size' => 2,
    '#maxlength' => 2,
    '#description' => t('Changes the number of recent items listed for the "Content" list. (<b>if set to 0 it renders this list null.</b>)')
  );
  return system_settings_form($form);
}
?>