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
  var _ajax_base_path;
  var _main_display_zone = {w:1024, h:768};
  var _cell_w = 340, _cell_h = 249, _line_h = _cell_h/4; 
  var _$stream_wrapper = $('<div>').attr('id','stream-wrapper').appendTo('#main');
  var _play_mode;

  var _themas = [];
  var _displayed_themas = [];
  var _thema_loaded = 0;
  var _anime_voisins_ready = 0;

  function init(){
    _ajax_base_path = Drupal.settings.basePath+Drupal.settings.pathPrefix;

    initGraphics();

    if($('body').is('.logged-in'))
      return;

    getContent();

    // newThema();
  };

  function initGraphics(){
    setupGrid();

    $('h1', '#header')
      .clone().attr('id', 'site-name')
      .appendTo(_$stream_wrapper)
      .placeBlock({left:0})
      .notAnime();
  };

  function getContent(){
    console.log('getcontent');
    var currentTime = new Date();
    $.getJSON(_ajax_base_path+'ajax/robinson/getcontent', 
      {currentTime:currentTime.getTime(), displayed_themas:_displayed_themas},
      contentLoaded  
    );
  };

  function contentLoaded(json){
    console.log("contentLoaded", json);

    _play_mode = json.mode;

    switch(_play_mode){
      case 'random':
        playRandom(json);
        break;
      case 'programe':
        playPrograme(json);
    }
  };

  function playRandom(json){
    console.log('playRandom', json);
    newThema(json.thema);
  };

  function playPrograme(json){
    console.log("playPrograme", json);
    // décompte
    // intro
    // sequence thema
    // sequence voisin
    // ...
    // outro
    // getContent();
  };

  function programeNextSequence(){
    console.log('programe_next_sequence');
  };

  function newThema(t){
    console.log("newThema", t);
    // move sitename in front
    $('#site-name', _$stream_wrapper)
      .notAnime()
      .detach()
      .appendTo(_$stream_wrapper);

    // purge themas in dom
    // $themas = $('.thema', _$stream_wrapper);
    if(_themas.length > 5){
      // first mask the oldest
      _themas[0].$thema.notAnime();
      // then remove it from dom after 5sec
      
      setTimeout(function(){
        _themas[0].$thema.remove();
        // TODO : shift _thema array
        // delete _themas[0];
      }, 5000);
    }

    // create new thema
    var thema = new Thema(t.nid)
    _themas.push(thema);

    thema.$
      .on('ready', playThema)
      // .on('finished', newThema);
      .on('finished', onThemaFinished);
  };

  function onThemaFinished(event){
    console.log("onThemaFinished :: _play_mode = "+ _play_mode);
    switch(_play_mode){
      case "random":
        _displayed_themas.push(this.nid);
        getContent();
        break;
      case "programe":
        programeNextSequence();
        break;
    }
  };

  function playThema(event){
    $('#site-name').preAnime();
    // this.startAnime();
  };

  /**
  * Thema()
  */
  function Thema(nid){
    //console.log('- - - - - - - - - new Thema - - - - - - - -');
    
    // var thema = this;
    this.$ = $(this);
    this.nid = nid;
    this.ready_for_voisins = this.loading_voisin = false;
    this.availablespace = 10;
    this.played_voisins = [];
    this.played_voisinsnids = [];
    this.impulseFrequency = 5; // in seconds

    /* PROTOTYPES */
    if(typeof Thema.prototype.initialized == "undefined"){
      
      Thema.prototype.ajaxLoad = function(){
        var thema = this;
    
        $.getJSON(_ajax_base_path+'ajax/robinson/thema', 
          {'thema_nid':this.nid},
          function(json){
            thema.ajaxLoaded(json);
        });
      };

      Thema.prototype.ajaxLoaded = function(datas){
        //console.log('Thema :: loaded | datas', datas);

        this.thema_id = _thema_loaded = _thema_loaded+1;

        for(index in datas)
          this[index] = datas[index];

        this.initGraphics();
        this.listenVideo();
      };

      Thema.prototype.initGraphics = function(){
        //console.log('Thema :: initGraphics');
        $('<div>')
          .attr('id', 'thema-'+this.thema_id)
          .addClass('thema')
          .append(this.rendered_thema)
          .appendTo(_$stream_wrapper);

        this.$thema = $('#thema-'+this.thema_id, _$stream_wrapper);

        $('.thema-title', this.$thema).placeBlock({left:1}).notAnime();
        $('.content', this.$thema).placeBlock({left:0}).notAnime();

        // TODO this should go out of Thema
        $('#site-name', _$stream_wrapper).placeBlock({left:0});
      };
    
      Thema.prototype.listenVideo = function(){
        /*
        https://vimeo.com/forums/topic:37800
        http://jsfiddle.net/bdougherty/UTt2K/
        http://kevinchevallier.com/vimeo-froogaloop-ajax/
        http://juanfra.me/2012/08/flexslider-multiple-videos-v2/
        http://mikeheavers.com/main/code-item/a_simpler_vimeo_froogaloop_javascript_api_example
        https://developer.vimeo.com/player/js-api#universal-with-postmessage
        http://player.vimeo.com/playground
        http://jsfiddle.net/nerdess/D5fD4/3/
        */
        var thema = this;
        this.$viframe = $('iframe', this.$thema);
        this.$viframe.load(function(){
          $f(this).addEvent('ready', function(id){thema.onVideoReady(id);});
        });
      };
  
      Thema.prototype.onVideoReady = function(id) {
        //console.log('Thema :: onVideoReady : id = '+id);
        var thema = this;

        this.video_id = id;

        $f(id)
          .addEvent('play', function(id){thema.onVideoPlay(id);})
          .addEvent('playProgress', function(data, id){thema.onVideoPlayProgress(data, id);})
          .addEvent('pause', function(id){thema.onVideoPause(id);})
          .addEvent('finish', function(id){thema.onVideoFinished(id);});

        this.$.trigger('ready');

        this.startAnime();
        this.voisins = [];
        this.videoPlay();
      };  

      Thema.prototype.onVideoPlay = function(id){
        //console.log('Thema :: onVideoPlay : id = '+id);
      };

      Thema.prototype.onVideoPause = function(id){
        //console.log('Thema :: onVideoPause : id = '+id);
      };

      Thema.prototype.onVideoPlayProgress = function(data, id){
        // console.log('Thema :: onVideoPlayProgress | id = '+id+' | data = ',data);
        
        if(typeof this.video_duration == "undefined"){ // first trigger
          this.video_duration = data.duration;
          this.thema_duration = data.duration + 30;
        }else if(data.seconds > this.impulseFrequency){
          // impulse voisins stream every n second
          // convert sec to milisec and use modulo
          // since play progress is triggered every (environ) 300 millisec we test modulo < to 300
          // var milisec = parseInt(data.seconds*1000);
          // var modulo = milisec % (2*1000);
          // console.log("seconds = "+data.seconds) 
          // console.log("seconds = "+data.seconds+" | milisec = "+milisec+" | modulo = "+modulo);
          
          if( (data.seconds % this.impulseFrequency) < 0.25)
            this.impulseVoisins();

          // if(data.seconds >= 120){
          //   this.videoPause();
          //   this.onVideoFinished(id);
          // }  
        }
      };

      Thema.prototype.videoPlay = function(){
        $f(this.video_id).api('play');
      };

      Thema.prototype.videoPause = function(){
        $f(this.video_id).api('pause');
      };

      Thema.prototype.onVideoFinished = function(id){
        //console.log('Thema :: onVideoFinished | id = '+id);
        
        this.$viframe.parents('.content').postAnime();
      
        (function(id){
          setTimeout(function(){
            //console.log('Thema :: unload vimeo '+id);
            $f(id).api('unload');
          }, 4000);      
        }(id));

        this.$.trigger('finished');
      };

      Thema.prototype.startAnime = function(){
        console.log("Thema :: startAnime");
        
        this.$thema.children().each(function(i){
          (function(e, i){
            setTimeout(function(){ 
              e.preAnime();
            }, 3000*i + Math.random()*4000);
          }($(this), i));
        });

        // when all elmnts are treated, we launch voisins
        (function(thema){
          setTimeout(function(){
            thema.$thema.children(':not(.content)').postAnime();
            thema.ready_for_voisins = true;
          }, 5000*thema.$thema.children().size());
        }(this));

      };

      Thema.prototype.impulseVoisins = function(){
        // console.log('impulseVoisins');
        if(this.ready_for_voisins && this.availablespace && !this.loading_voisin){
          this.loading_voisin = true;
          var thema = this;
          var voisin = new Voisin({thema:this});
          voisin.$
            .bind('loaded', function(event){thema.onVoisinLoaded(this, event)})
            .bind('finished', function(event){thema.onVoisinFinished(this, event)});
        }
      };

      Thema.prototype.onVoisinLoaded = function(voisin, event){
        // console.log('Thema :: onVoisinLoaded : voisin', voisin);
        this.availablespace -= voisin.space;
        this.played_voisins.push(voisin);
        this.played_voisinsnids.push(voisin.nid);
        this.loading_voisin = false;
      };

      Thema.prototype.onVoisinFinished = function(voisin, event){
        // console.log("Thema :: onVideoFinished : voisin", voisin);
        this.availablespace += voisin.space;
      };

      Thema.prototype.initialized = true;
    }

    this.ajaxLoad();
  }; // Thema

  /**
  * Voisin()
  */
  function Voisin(ops){
    //console.log('- - - - new Voisin '+nid+' - - - -');

    // var voisin = this;
    this.$ = $(this);
    
    for(op in ops)
      this[op] = ops[op];
    
    /* PROTOTYPES */
    if(typeof Voisin.prototype.initialized == "undefined"){

      Voisin.prototype.ajaxLoad = function(){
        console.log('Voisin :: ajaxload : this', this);
        var voisin = this;
        var params;
        if(this.nid){
          params = {voisin:{nid:this.nid}};
        }else if(this.thema){
          params = {thema:{
            nid                 :this.thema.nid, 
            voisins_list        :this.thema.voisins_list, 
            played_voisins_nids :this.thema.played_voisinsnids,
            availablespace      :this.thema.availablespace
          }};
        }

        $.getJSON(_ajax_base_path+'ajax/robinson/voisin', 
          params,
          function(json){
            voisin.ajaxLoaded(json);
        });
      };

      Voisin.prototype.ajaxLoaded = function(datas){
        // console.log('Voisin :: ajaxLoaded',datas);

        for(index in datas.voisin)
          this[index] = datas.voisin[index];
        
        // this.parseComportement();

        this.$.trigger('loaded');

        this.start();
      };

      // not used any more
      // i made the comportement parsing on server side
      // it's cached by session
      // it allows me to precalculate the space and so on to filter the voisin to randomly choose with available space 
      // Voisin.prototype.parseComportement = function(){
        // console.log("Voisin :: parseComportement ", this.comportement);
        // field_discursif              "0"
        // field_duree_sec_minmax       "5/120"
        // field_pause_apres_le_voisin  "0/0"
        // field_proba                  "50"
        // field_taille_minmax          "1/3"

        // this.discursif = parseInt(this.comportement.field_discursif) == 1;
        // this.proba = parseInt(this.comportement.field_proba);

        // var d = this.comportement.field_duree_sec_minmax.match(/(\d{1,3})\/(\d{1,3})/i);
        // // console.log("d", d);
        // this.duree = {
        //   min:d[1],
        //   max:d[2]
        // }

        // d = this.comportement.field_pause_apres_le_voisin.match(/(\d{1,3})\/(\d{1,3})/i);
        // // console.log("d", d);
        // this.pauseafter = {
        //   min:d[1],
        //   max:d[2]
        // }

        // d = this.comportement.field_taille_minmax.match(/(\d{1})\/(\d{1})/i);
        // // console.log("d", d);
        // this.taille = {
        //   min:d[1],
        //   max:d[2]
        // }
        
        // console.log("voisin :: ", this);
      // };

      Voisin.prototype.start = function(){
        console.log('Voisin :: start : media_type = '+this.media_type);

        if(typeof this['start'+this.media_type] == 'function')
          this['start'+this.media_type].call(this);
      };

      /**
      * common init
      * html
      */
      Voisin.prototype.initCommons = function(){
        //console.log('Voisin :: initGraphics '+this.nid, this);

        this.$voisin = $(this.rendered)   
          .appendTo(this.thema.$thema)
          .notAnime();
      };

      Voisin.prototype.setSize = function(){
        // this.$voisin.width(_cell_w * parseInt(this.taille.min + Math.random()*(this.taille.max-this.taille.min)));
        this.$voisin.width(_cell_w * this.comportement.taille);
      };

      Voisin.prototype.setDuree = function(){
        console.log('Voisin :: setDuree');
        (function(voisin){
          setTimeout(function(){
            voisin.endAnime();
          }, voisin.comportement.duree*1000);
        }(this));
      };

      Voisin.prototype.endAnime = function(){
        console.log('Voisin :: endAnime');
        this.$voisin.postAnime();
        this.$.trigger('finished');
      };

      /**
      * text
      */
      Voisin.prototype.starttext = function(){
        console.log("Voisin :: starttext", this);
        this.initCommons();
        this.setSize();
        this.$voisin.placeBlock();
        this.$voisin.preAnime();
        this.setDuree();
      };

      /**
      * image
      */
      Voisin.prototype.startimage = function(){
        console.log("Voisin :: startimage", this);
        this.initCommons();
        this.$voisin.placeBlock();
        this.$voisin.preAnime();
        this.setDuree();
      };

      /**
      * audio
      */
      Voisin.prototype.startaudio = function(){
        console.log("Voisin :: startaudio", this);
        this.initCommons();
        this.setupSoundCloudPlayer();
        this.$voisin.css('top', -1000);
      };

      Voisin.prototype.setupSoundCloudPlayer = function(){

      };

      /**
      * video
      */
      Voisin.prototype.startvideo = function(){
        console.log("Voisin :: startvideo", this);

        this.initCommons();
        this.$voisin.placeBlock();
        

        var voisin = this;
        this.$viframe = $('iframe', this.$voisin);
        this.$viframe.load(function(){
          $f(this).addEvent('ready', function(id){voisin.onVideoReady(id);});
        });        
      };

      Voisin.prototype.onVideoReady = function(id) {
        //console.log('Voisins :: onVideoReady : id = '+id);         
        var voisin = this;
        this.video_id = id;

        $f(id)
          .addEvent('play', function(id){voisin.onVideoPlay(id);})
          .addEvent('playProgress', function(data, id){voisin.onVideoPlayProgress(data, id);})
          .addEvent('pause', function(id){voisin.onVideoPause(id);})
          .addEvent('finish', function(id){voisin.onVideoFinished(id);});

        this.startAnimeVideo();
      };

      Voisin.prototype.startAnimeVideo = function(){
        this.playVideo();
        this.$voisin.preAnime();
        // (function(voisin){
        //   voisin.$.on('video_finished', function(){
        //     voisin.unloadVideo();
        //     voisin.$voisin.postAnime();
        //   });  
        // }(this));
      };

      Voisin.prototype.playVideo = function(){
        $f(this.video_id).api('play');
      };

      Voisin.prototype.unloadVideo = function(){
        // var $viframe = $('iframe', $voisin);
        // var id = $viframe.attr('id');

        // (function(id){
          // setTimeout(function(){$f(id).api('play');}, 500);
        // }(id));

        $f(this.video_id).api('unload');
      };

      Voisin.prototype.onVideoPlay = function(id){
        //console.log('Voisin :: onVideoPlay : id = '+id);
      };

      Voisin.prototype.onVideoPause = function(id){
        //console.log('Voisin :: onVideoPause : id = '+id);
      };

      Voisin.prototype.onVideoPlayProgress = function(data, id){
        //console.log('Voisin :: onVideoPlayProgress | id = '+id+' | data = ',data);
        // if(data.seconds >= 15){
        //   $f(id).api('pause');
        //   onThemaVideoFinish(id);
        // }
      };

      Voisin.prototype.onVideoFinished = function(id){
        //console.log('Voisin :: onVideoFinished | id = '+id);
        // onVideoFinish(id);
        // this.$.trigger('video_finished');
        this.unloadVideo();
        this.endAnime();
      };

      Voisin.prototype.initialized = true;
    }

    this.ajaxLoad();
  }; // Voisins


  /* GRID */
  function setupGrid(){
    //console.log('setupGrid');
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
    //console.log('placeBlock', $elmt);
    var defaults = {top:"rand",left:"rand"};   
    var options = $.extend({}, defaults, opts);
    
    //console.log('options', options);  
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

  // preAnime() is automaticly folllowed by anime()
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
