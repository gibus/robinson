// @koala-prepend "gui.js"
// @codekit-prepend "gui.js"


Drupal.behaviors.init_theme = function (context) {
  // Growl-style system messages
  $('#messages-and-help > div.messages:not(.processed)')
    .addClass('processed')
    .each(function() {
      // If a message meets these criteria, we don't autoclose
      // - contains a link
      // - is an error or warning
      // - contains a lenghthy amount of text
      if ($('a', this).size() || $(this).is('.error') || $(this).is('.warning') || $(this).text().length > 100) {
        $(this).prepend("<span class='close'>X</span>");
        $('span.close', this).click(function() {
          $(this).parent().slideUp('fast');
        });
      }
      else {
        // This essentially adds a 3 second pause before hiding the message.
        $(this).animate({opacity:1}, 5000, 'linear', function() {
          $(this).slideUp('fast');
        });
      }
    });
};

(function($) {

  var _debug = false;
  var _main_display_zone = {w:1024, h:768};
  var _cell_w = 341, _cell_h = 256, _line_h = _cell_h/4; 
  var _$stream_wrapper = $('<div>').attr('id','stream-wrapper').appendTo('#main');
  var _displayed_themas = [];

  function init(){
    initGraphics();
    loadThema();
  };

  function initGraphics(){
    setupGrid();

    $('h1', '#header')
      .clone().attr('id', 'site-name')
      .appendTo(_$stream_wrapper)
      .placeBlock({left:0});
  };

  function loadThema(){
    console.log('loadThema');
    $.getJSON(Drupal.settings.basePath+Drupal.settings.pathPrefix+'ajax/robinson/thema', 
      // {'types':types,'current_path':document.location.href, 'keys':keys, 'searchmode':searchmode},
      function(json){
        console.log('json', json);
        displayThema(json);
    });
  };

  function displayThema(data){
    var thema_id = data.thema.nid;

    $('<div>')
      .attr('id', 'thema-'+thema_id)
      .addClass('thema')
      .append(data.rendered_thema)
      .appendTo(_$stream_wrapper);

    var $thema = $('#thema-'+thema_id, _$stream_wrapper);

    $('.thema-title', $thema).placeBlock({left:1});
    $('.content', $thema).placeBlock({left:0});

    loadVoisins($thema, data);
    listenThemaVideo($thema);
  };

  // https://vimeo.com/forums/topic:37800
  // http://jsfiddle.net/bdougherty/UTt2K/
  // http://kevinchevallier.com/vimeo-froogaloop-ajax/
  // http://juanfra.me/2012/08/flexslider-multiple-videos-v2/
  // http://mikeheavers.com/main/code-item/a_simpler_vimeo_froogaloop_javascript_api_example
  // https://developer.vimeo.com/player/js-api#universal-with-postmessage
  // http://player.vimeo.com/playground

  function listenThemaVideo($thema){
    var $vimeoIframe = $('iframe', $thema);

    // Listen for messages from the player
    if (window.addEventListener){
      window.addEventListener('message', function(e){
        onMessageReceived($vimeoIframe, e)
      }, false);
    }else {
      window.attachEvent('onmessage', function(e){
        onMessageReceived($vimeoIframe, e)
      }, false);
    }
  };

  // Handle messages received from the player
  function onMessageReceived($vimeoIframe, e){
    try{
      var data = JSON.parse(e.data);
      // console.log('onMessageReceived | e', data.event);
      switch (data.event) {
        case 'ready':
          onVideoIsReady($vimeoIframe);
          break;
        case 'playProgress':
          onVideoPlayProgress($vimeoIframe, data.data);
          break;
        // case 'pause':
        //   onVideoPause();
        //   break;
        case 'finish':
          onVideoFinish($vimeoIframe);
          break;
      }
    }catch(e){

    }
  };

  // function for sending a message to the player
  function post($vimeoIframe, action, value) {
      // console.log('POST | action : '+action+' | value : '+value);
      var  url = $vimeoIframe.attr('src').split('?')[0];
      var data = { method: action };
      
      if (value)
          data.value = value;

      var jsoned = JSON.stringify(data);
      
      $vimeoIframe[0].contentWindow.postMessage(jsoned, url);
  };

  function onVideoIsReady($vimeoIframe){
    // console.log('onVideoIsReady', $vimeoIframe);
    // post($vimeoIframe, 'addEventListener', 'pause');
    post($vimeoIframe, 'addEventListener', 'finish');
    post($vimeoIframe, 'addEventListener', 'playProgress');
    post($vimeoIframe, 'play');
  };

  function onVideoPlayProgress($vimeoIframe, data){
    // console.log('onVideoPlayProgress | data = ', data);
  };

  function onVideoFinish($vimeoIframe){
    console.log('onVideoFinish', $vimeoIframe);
    post($vimeoIframe, 'unload');
    onThemaVideoFinish($vimeoIframe);
  };

  function onThemaVideoFinish($vimeoIframe){
    console.log('onThemaVideoFinish');
    $vimeoIframe.parents('.thema').fadeOut('slow', function() {
      $(this).remove();
    });
    launchNewThema();
  };

  function launchNewThema(){
    console.log('launchNewThema');
    loadThema();
  };

  /* VOISINS */
  function loadVoisins($thema, data){
    console.log('loadVoisin', data);
    for(index in data.thema.voisins){
      var voisin_id = data.thema.voisins[index].target_id; 
      console.log("voisin_id = "+voisin_id);
      $.getJSON(Drupal.settings.basePath+Drupal.settings.pathPrefix+'ajax/robinson/voisin', 
      {'id':voisin_id},
      function(json){
        // console.log('voisin loaded | json', json);
        displayVoisin($thema, json);
      });
    }
  };

  function displayVoisin($thema, data){
    console.log('displayVoisin', data);
    $(data.rendered_voisin)
      .appendTo($thema)
      .placeBlock();
  };

  /* GRID */
  function setupGrid(){
    console.log('setupGrid');
    _main_display_zone.top = ($(window).height() - _main_display_zone.h)/2;
    _main_display_zone.left = ($(window).width() - _main_display_zone.w)/2;


    if(_debug) drawDebugGrid();
  };

  function drawDebugGrid(){
    var $g = $('<div>').attr('id','debug-grid').appendTo('body');

    $g.css({
      "top":_main_display_zone.top,
      "left":_main_display_zone.left,
      "width":_main_display_zone.w-2,
      "height":_main_display_zone.h-2
    });

    $('<div>').addClass('cells').css({
      "top":-1,
      "left":_cell_w-1,
      "width":_cell_w-2,
      "height":_main_display_zone.h-2
    }).appendTo($g);

    $('<div>').addClass('cells').css({
      "top":_cell_h-1,
      "left":-1,
      "width":_main_display_zone.w-2,
      "height":_cell_h-2
    }).appendTo($g);

    for (var i = 0; i < 6; i++) {
      $('<div>').addClass('lines').css({
        "top":_line_h+(_line_h*2)*i -1,
        "left":-1,
        "width":_main_display_zone.w-2,
        "height":_line_h-2
      }).appendTo($g);      
    };
  };

  function placeBlock($elmt, opts){
    console.log('placeBlock', $elmt);
    var defaults = {top:"rand",left:"rand"};   
    var options = $.extend({}, defaults, opts);
    
    console.log('options', options);  
    var top_free_cells = Math.floor((_main_display_zone.h - $elmt.innerHeight() +_line_h)/_line_h);
    var top_cell = options.top == 'rand' ? Math.floor(Math.random()*(top_free_cells)) : options.top;
    var top = _main_display_zone.top + top_cell*_line_h;

    var left_free_cells = Math.floor((_main_display_zone.w - $elmt.width() + _cell_w)/_cell_w);
    var left_cell = options.left == 'rand' ? Math.floor(Math.random()*(left_free_cells)) : options.left;
    var left = _main_display_zone.left + left_cell*_cell_w;

    $elmt
      .css({
        "top":top+'px',
        "left":left+'px',
      })
      .addClass('placed');
  };

  
  /**
  * ready
  */
  $(document).ready(init);


  /**
  * plugins
  */
  $.fn.randomize = function(selector){
    (selector ? this.find(selector) : this).parent().each(function(){
        $(this).children(selector).sort(function(){
            return Math.random() - 0.5;
        }).detach().appendTo(this);
    });

    return this;
  };
  
  $.fn.center = function () {
    this.css("position","absolute");
    this.css("top", Math.max(0, (($(window).height() - $(this).outerHeight()) / 2) + 
                                                $(window).scrollTop()) + "px");
    this.css("left", Math.max(0, (($(window).width() - $(this).outerWidth()) / 2) + 
                                                $(window).scrollLeft()) + "px");
    return this;
  };

  $.fn.placeBlock = function(o) {
    placeBlock(this, o);
    return this;
  };


})(jQuery);
