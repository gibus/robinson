// $Id$

$(document).ready(function() {
  // get the Drupal basepath
  var basePath = Drupal.settings.menu_bar.basePath;
  
  // insert extra <br /> so menu doesn't overlap theme
  $('body').prepend('<ul id="menubar"></ul><br />');
  
  // Drupal menu callback
  $('#menubar').load(basePath + 'menu_bar/menu', function() {
    $('li', this).hover(function() {
      $('ul', this).slideDown(200);
    }, function() {});
    $('a', this).title('');
  });
});