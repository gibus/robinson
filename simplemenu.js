// $Id$

$(document).ready(function() {
  // get the Drupal basepath
  var basePath = Drupal.settings.simplemenu.basePath;
  // get the element to add the menu to
  var element = Drupal.settings.simplemenu.element;                        
  var menu = '<ul id="simplemenu" class="clear-block"></ul>';
  
  switch (Drupal.settings.simplemenu.placement) {
    case 'prepend':
      $(menu).prependTo(element);
      break;
    case 'append':
      $(menu).appendTo(element);
      break;
    case 'replace':
      $(element).html(menu);
      break;
  }  
  
  $('body').css('margin-top', '23px');
  
  // Drupal menu callback
  $('#simplemenu').load(basePath + 'simplemenu/menu', function() {
    $('li', this).hover(function() {
      $('ul', this).slideDown(200);
    }, function() {});
    $('a', this).title('');
    $(this).children('li.expanded').addClass('root');
  });
});