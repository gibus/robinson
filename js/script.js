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
  var _cell_w = 340, _cell_h = 249, _line_h = _cell_h/4; 
  var _$stream_wrapper = $('<div>').attr('id','stream-wrapper').appendTo('#main');
  var _displayed_themas = [];
  var _thema_loaded = 0;
  var _anime_voisins_ready = 0;

  function init(){
    initGraphics();

    if($('body').is('.logged-in'))
      return;

    loadThema();
  };

  function initGraphics(){
    setupGrid();

    $('h1', '#header')
      .clone().attr('id', 'site-name')
      .appendTo(_$stream_wrapper)
      .placeBlock({left:0})
      .notAnime();
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
    // var thema_id = data.thema.nid;
    var thema_id = _thema_loaded = _thema_loaded+1;

    $('<div>')
      .attr('id', 'thema-'+thema_id)
      .addClass('thema')
      .append(data.rendered_thema)
      .appendTo(_$stream_wrapper);

    var $thema = $('#thema-'+thema_id, _$stream_wrapper);

    $('.thema-title', $thema).placeBlock({left:1}).notAnime();
    $('.content', $thema).placeBlock({left:0}).notAnime();

    $('#site-name', _$stream_wrapper).placeBlock({left:0});

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
  // http://jsfiddle.net/nerdess/D5fD4/3/
  function listenThemaVideo($thema){
    var $viframe = $('iframe', $thema);
    $viframe.load(function(){
      $viframe.data('stoped', false);
      $f(this).addEvent('ready', onVimeoThemaReady);
    });
  };

  function onVimeoThemaReady(id) {
    console.log('onVimeoReady : id = '+id);         

    $f(id)
      .addEvent('play', onVimeoPlay)
      .addEvent('playProgress', onVimeoPlayProgress)
      .addEvent('pause', onVimeoPause)
      .addEvent('finish', onVimeoFinished);
    
    (function(id){
      setTimeout(function(){$f(id).api('play');}, 5000);
    }(id));

    startAnimeThema($("#"+id).parents(".thema"));
  };  

  function onVimeoPlay(id){
    console.log('onVimeoPlay : id = '+id);
  };

  function onVimeoPause(id){
    console.log('onVimeoPause : id = '+id);
  };

  function onVimeoPlayProgress(data, id){
    // console.log('onVimeoPlayProgress | id = '+id+' | data = ',data);
    // if(data.seconds >= 15){
    //   $f(id).api('pause');
    //   onThemaVideoFinish(id);
    // }
  };

  function onVimeoFinished(id){
    console.log('onVimeoFinished | id = '+id);
    onThemaVideoFinish(id);
  };

  function onThemaVideoFinish(id){
    console.log('onThemaVideoFinish | id = '+id);
    var $viframe = $('#'+id); 
    $viframe.parents('.content').postAnime();
  
    (function(id){
      setTimeout(function(){
        console.log('unload '+id);
        $f(id).api('unload');
      }, 4000);      
    }(id));

    launchNewThema();
  };

  function launchNewThema(){
    console.log('launchNewThema');

    // move sitename in front
    $('#site-name', _$stream_wrapper)
      .notAnime()
      .detach()
      .appendTo(_$stream_wrapper);

    // purge themas in dom
    $themas = $('.thema', _$stream_wrapper);
    if($themas.size()>5){
      // first mask the oldest
      $themas.eq(0).notAnime();
      // then remove it from dom after 5sec
      (function($t){
        setTimeout(function(){
          $t.remove();
        }, 5000);
      }($themas.eq(0)));
    }

    loadThema();
  };

  function startAnimeThema($thema){
    var elmts = new Array();
    elmts.push($('#site-name'));
    elmts.push($('.thema-title', $thema));
    elmts.push($('section.content', $thema));

    // set delay for animation
    // function anime
    for (var i = 0; i < elmts.length; i++) {
      (function(i, elmts, $thema){
        setTimeout(function(){
          
          if(i > 0)
            if(!elmts[i-1].is('section.content') || !elmts[i-1].is('.voisin.*-video')) elmts[i-1].postAnime();
          
          elmts[i].preAnime();

          if(i == elmts.length-1)
            bufferizeAnimeVoisins($thema);

        }, 3000*i + Math.random()*4000);
      })(i, elmts, $thema);
    }
  };

  /* VOISINS */
  function loadVoisins($thema, data){
    console.log('loadVoisin', data);
    
    $thema.data('voisins_loaded', 0);
     
    if(data.thema.voisins !== null){
      $thema.data('voisins_len', data.thema.voisins.length);
      
      for(index in data.thema.voisins){
        var voisin_id = data.thema.voisins[index].target_id; 
        console.log("voisin_id = "+voisin_id);
        $.getJSON(Drupal.settings.basePath+Drupal.settings.pathPrefix+'ajax/robinson/voisin', 
        {'id':voisin_id},
        function(json){
          // console.log('voisin loaded | json', json);
          voisinLoaded($thema, json);
        });
      }  
    }else{
      $thema.data('voisins_len', 0);
      voisinLoaded($thema, false);
    }
  };

  function voisinLoaded($thema, data){
    var loaded_voisins = $thema.data('voisins_loaded') +1;
    $thema.data('voisins_loaded', loaded_voisins);

    if(loaded_voisins >= $thema.data('voisins_len'))
      bufferizeAnimeVoisins($thema);
    
    if(data)
      displayVoisin($thema, data);
  };

  function displayVoisin($thema, data){
    console.log('displayVoisin', data);
  
    $(data.rendered_voisin)
      .appendTo($thema)
      .placeBlock()//{left:1}
      .notAnime();
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

  /* ANIME */

  function notAnime($elmt){
    $elmt
      .addClass("not-anime")
      .removeClass("pre-anime")
      .removeClass('anime')
      .removeClass('post-anime');
  };

  function preAnime($elmt){
    $elmt
      .removeClass("not-anime")
      .addClass("pre-anime")
      .removeClass('anime')
      .removeClass('post-anime');
   
   (function($elmt){
      setTimeout(function(){
        $elmt.anime();
      }, 1000 + Math.random()*1000);
    }($elmt));
  };

  function anime($elmt){
    $elmt
      .removeClass("not-anime")
      .removeClass('pre-anime')
      .addClass("anime")
      .removeClass('post-anime');
  };

  function postAnime($elmt){
    $elmt
      .removeClass("not-anime")
      .removeClass('pre-anime')
      .removeClass('anime')
      .addClass("post-anime");
  };

  function bufferizeAnimeVoisins($thema){
    _anime_voisins_ready ++;
    if(_anime_voisins_ready == 2){
      startAnimeVoisins($thema);
    }
  };

  function startAnimeVoisins($thema){
    // record all elements to anime
    var elmts = new Array();
    // elmts.push($('#site-name'));
    // elmts.push($('.thema-title', $thema));
    // elmts.push($('section.content', $thema));
    $('article.voisin', $thema).each(function(index) {
      elmts.push($(this));
    });

    // set delay for animation
    // function anime
    for (var i = 0; i < elmts.length; i++) {
      (function(i, elmts){
        setTimeout(function(){
          if(i > 0)
            if(!elmts[i-1].is('section.content') || !elmts[i-1].is('.voisin.*-video')) elmts[i-1].postAnime();
          
          elmts[i].preAnime();
        }, 5000*(i+1) + Math.random()*5000);
      })(i, elmts);
    }
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

  $.fn.notAnime = function(){
    notAnime(this);
    return this;
  };
  $.fn.preAnime = function(){
    preAnime(this);
    return this;
  };
  $.fn.anime = function(){
    anime(this);
    return this;
  };
  $.fn.postAnime = function(){
    postAnime(this);
    return this;
  };


})(jQuery);
