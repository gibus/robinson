// $Id$

$(document).ready(function() {
  // get the Drupal basepath
  var basePath = Drupal.settings.simplemenu.basePath;
  
  // insert extra <br /> so menu doesn't overlap theme
  $('<ul id="simplemenu" class="clear-block"></ul>').prependTo('body').slideDown(400);
  
  // Drupal menu callback
  $('#simplemenu').load(basePath + 'simplemenu/menu', function() {
    $('li', this).hover(function() {
      $('ul', this).slideDown(200);
    }, function() {});
    $('a', this).title('');
  });
});