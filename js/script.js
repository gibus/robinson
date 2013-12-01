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
  var _themas = [];
  var _displayed_themas = [];
  var _thema_loaded = 0;
  var _anime_voisins_ready = 0;

  function init(){
    initGraphics();

    if($('body').is('.logged-in'))
      return;

    newThema();
  };

  function initGraphics(){
    setupGrid();

    $('h1', '#header')
      .clone().attr('id', 'site-name')
      .appendTo(_$stream_wrapper)
      .placeBlock({left:0})
      .notAnime();
  };

  function newThema(){
    //console.log("newThema")
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
        // TODO shift _thema array
      }, 5000);
    }

    // create new thema
    var thema = new Thema()
    _themas.push(thema);

    thema.$
      .on('ready', playThema)
      // .on('finished', newThema);
      .on('finished', reload);
  };

  function reload(){
    location.reload(true);
  };

  function playThema(event){
    $('#site-name').preAnime();
    this.startAnime();
  };

  /**
  * Thema()
  */
  function Thema(){
    //console.log('- - - - - - - - - new Thema - - - - - - - -');
    
    // var thema = this;

    this.$ = $(this);
    this.anime_voisins_buffer = 0;

    /* PROTOTYPES */
    if(typeof Thema.prototype.initialized == "undefined"){
      
      Thema.prototype.ajaxLoad = function(){
        var thema = this;
    
        $.getJSON(Drupal.settings.basePath+Drupal.settings.pathPrefix+'ajax/robinson/thema', 
          // {'types':types,'current_path':document.location.href, 'keys':keys, 'searchmode':searchmode},
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
        (function(thema){
          setTimeout(function(){thema.loadVoisins();}, 10000);
        }(this));
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

      Thema.prototype.loadVoisins = function(){
        //console.log('Thema :: loadVoisin');
        
        this.voisins_loaded = 0;

        if(this.list_voisins !== null){
          this.voisins_len = this.list_voisins.length;
          this.voisins = {
            flat:[],
            video:[],
            audio:[],
            image:[],
            txt:[],
            discursif:[]
          };
          
          var thema = this, voisin, vid;
          for(index in this.list_voisins){
            vid = this.list_voisins[index].target_id; 
            voisin = new Voisin(this, vid);
            voisin.$.on('loaded', function(event) {
              thema.onVoisinLoaded(this);
            });
          }

        }else{
          this.voisins_len = 0;
          this.voisinLoaded(false);
        }
      };

      Thema.prototype.onVoisinLoaded = function(voisin){
        this.voisins_loaded ++;
        console.log('Thema :: onVoisinLoaded | voisin', voisin);

        this.voisins.flat.push(voisin);

        switch(voisin.viewmode){
          case "atmosphere_video":
          case "contrib_video":
            this.voisins.video.push(voisin);
            break;
          case "atmosphere_audio":
          case "contrib_audio":
            this.voisins.audio.push(voisin);
            break;
          case "atmosphere_image":
          case "contrib_image":
            this.voisins.image.push(voisin);
            break;
          case "contrib_txt":
            this.voisins.txt.push(voisin);
          case "discursif":
            this.voisins.discursif.push(voisin);
            break;            
        }

        if(this.voisins_loaded >= this.voisins_len)
          this.bufferizeAnimeVoisins();
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
        // console.log('thema', thema);
        var thema = this;

        this.video_id = id;

        $f(id)
          .addEvent('play', function(id){thema.onVideoPlay(id);})
          .addEvent('playProgress', function(data, id){thema.onVideoPlayProgress(data, id);})
          .addEvent('pause', function(id){thema.onVideoPause(id);})
          .addEvent('finish', function(id){thema.onVideoFinished(id);});
  
        this.$.trigger('ready');
      };  

      Thema.prototype.onVideoPlay = function(id){
        //console.log('Thema :: onVideoPlay : id = '+id);
      };

      Thema.prototype.onVideoPause = function(id){
        //console.log('Thema :: onVideoPause : id = '+id);
      };

      Thema.prototype.onVideoPlayProgress = function(data, id){
        // console.log('Thema :: onVideoPlayProgress | id = '+id+' | data = ',data);
        
        if(typeof this.video_duration == "undefined"){
          this.video_duration = data.duration;
          this.bufferizeAnimeVoisins();
        }

        // wait to know the video duration before launch voisin
        // if(this.anime_voisins_buffer < 3)
        //   this.bufferizeAnimeVoisins();

        // if(data.seconds >= 120){
        //   this.videoPause();
        //   this.onVideoFinished(id);
        // }
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
        //console.log("Thema :: startAnime");

        // (function(id){
        //   setTimeout(function(){$f(id).api('play');}, 5000);
        // }(id));
        
        this.videoPlay();

        var elmts = new Array();
        elmts.push($('.thema-title', this.$thema));
        elmts.push($('section.content', this.$thema));

        // set delay for animation
        // function anime
        for (var i = 0; i < elmts.length; i++) {
          (function(i, elmts, thema){
            setTimeout(function(){
              
              if(i > 0)
                if(!elmts[i-1].is('section.content')) elmts[i-1].postAnime();
              
              elmts[i].preAnime();

              if(i == elmts.length-1)
                thema.bufferizeAnimeVoisins();

            }, 3000*i + Math.random()*4000);
          })(i, elmts, this);
        }
      };

      Thema.prototype.bufferizeAnimeVoisins = function(){
        console.log('Thema :: bufferizeAnimeVoisins', this.voisins);
        this.anime_voisins_buffer ++;
        if(this.anime_voisins_buffer == 3)
          this.startAnimeVoisins();
      };

      Thema.prototype.startAnimeVoisins = function(){
        console.log("Thema :: startAnimeVoisins", this.voisins);
        
        // txt
        this.startAnimeTxt();
        // images
        this.startAnimeImage();
        // videos
        this.startAnimeVideo();
        // sons
        this.startAnimeAudio();

        // var i = 0;
        // for (index in this.voisins.flat) {
        //   this.voisins.flat[index].startAnime(i);
        //   i++;
        // };
      };

      Thema.prototype.startAnimeTxt = function(){
        var delay = this.video_duration*1000 / this.voisins.txt.length; 
        for (index in this.voisins.txt) {
          (function(thema, delay, index){
            
            setTimeout(function(){
              thema.voisins.txt[index].startAnime();
            }, delay*index + (-1000+Math.random()*2000));

          }(this, delay, index));
        }
      };

      Thema.prototype.startAnimeImage = function(){
        var delay = this.video_duration*1000 / this.voisins.image.length; 
        for (index in this.voisins.image) {
          (function(thema, delay, index){
            
            setTimeout(function(){
              thema.voisins.image[index].startAnime();
            }, delay*index + (-1000+Math.random()*2000));

          }(this, delay, index));
        };
      };

      Thema.prototype.startAnimeVideo = function(){
        var delay = this.video_duration*1000 / this.voisins.video.length; 
        for (index in this.voisins.video) {
          (function(thema, delay, index){
            
            setTimeout(function(){
              thema.voisins.video[index].startAnime();
            }, delay*index + (-1000+Math.random()*2000));

          }(this, delay, index));
        };
      };

      Thema.prototype.startAnimeAudio = function(){
        var delay = this.video_duration*1000 / this.voisins.audio.length; 
        for (index in this.voisins.audio) {
          (function(thema, delay, index){
            
            setTimeout(function(){
              thema.voisins.audio[index].startAnime();
            }, delay*index + (-1000+Math.random()*2000));

          }(this, delay, index));
        };
      };

      Thema.prototype.initialized = true;
    }

    this.ajaxLoad();

  }; // Thema

  /**
  * Voisin()
  */
  function Voisin(thema, nid){
    // console.log('- - - - new Voisin '+nid+' - - - -');

    var voisin = this;
    this.$ = $(this);
    this.nid = nid;
    this.thema = thema;

    /* PROTOTYPES */
    if(typeof Voisin.prototype.initialized == "undefined"){

      Voisin.prototype.ajaxLoad = function(){
        var voisin = this;

        $.getJSON(Drupal.settings.basePath+Drupal.settings.pathPrefix+'ajax/robinson/voisin', 
          {'id':this.nid},
          function(json){
            voisin.ajaxLoaded(json);
        });
      };

      Voisin.prototype.ajaxLoaded = function(datas){
        // console.log('Voisin :: ajaxLoaded',datas);

        for(index in datas)
          this[index] = datas[index];

        this.initGraphics();
        
        switch(this.viewmode){
          case "atmosphere_video":
          case "contrib_video":
            this.initVideo();
            break;
          case "atmosphere_audio":
          case "contrib_audio":
            this.initAudio();
            break;
          // default:
            // this.$.trigger('loaded');            
        }

        this.$.trigger('loaded');
        
      };

      Voisin.prototype.initGraphics = function(){
        // console.log('Voisin :: initGraphics '+this.nid, this);

        var $voisin = $(this.rendered_voisin)   
          .appendTo(this.thema.$thema)
          .notAnime();

        this.$voisin = $voisin;

        // if($voisin.is('.atmosphere-video') || $voisin.is('.contrib-video'))
        //   this.listenVoisinVimeo();

        if(!$voisin.is('.discuscif') && !$voisin.is('.atmosphere-audio') && !$voisin.is('.contrib-son')){
          $voisin.placeBlock();
        }else{
          $voisin.css('top', -1000);  
        }
      };

      Voisin.prototype.initVideo = function(){
        var voisin = this;
        this.$viframe = $('iframe', this.$voisin);
        this.$viframe.load(function(){
          $f(this).addEvent('ready', function(id){voisin.onVideoReady(id);});
        });        
      };

      Voisin.prototype.onVideoReady = function(id) {
        console.log('Voisins :: onVideoReady : id = '+id);         
        var voisin = this;
        this.video_id = id;

        $f(id)
          .addEvent('play', function(id){voisin.onVideoPlay(id);})
          .addEvent('playProgress', function(data, id){voisin.onVideoPlayProgress(data, id);})
          .addEvent('pause', function(id){voisin.onVideoPause(id);})
          .addEvent('finish', function(id){voisin.onVideoFinished(id);});

        // this.$.trigger('loaded');
      };

      Voisin.prototype.playVideo = function(){
        // var $viframe = $('iframe', $voisin);
        // var id = $viframe.attr('id');

        // (function(id){
          // setTimeout(function(){$f(id).api('play');}, 500);
        // }(id));

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
        // console.log('Voisin :: onVideoPlayProgress | id = '+id+' | data = ',data);
        // if(data.seconds >= 15){
        //   $f(id).api('pause');
        //   onThemaVideoFinish(id);
        // }
      };

      Voisin.prototype.onVideoFinished = function(id){
        //console.log('Voisin :: onVideoFinished | id = '+id);
        // onVideoFinish(id);
        this.$.trigger('video_finished');
      };

      Voisin.prototype.initAudio = function(){
        // TODO souncloud player
        this.$.trigger('loaded');
      };

      Voisin.prototype.startAnime = function(){ // i
        //console.log('Voisin :: startAnime '+this.viewmode);

        switch(this.viewmode){
          case "atmosphere_video":
          case "contrib_video":
            this.startAnimeVideo();
            break;
          case "atmosphere_audio":
          case "contrib_audio":
            // this.voisins.audio.push(voisin);
            break;
          case "atmosphere_image":
          case "contrib_image":
            this.startAnimeImage();
            break;
          case "contrib_txt":
            this.startAnimeTxt();
          case "discursif":
            // this.voisins.discursif.push(voisin);
            break;            
        }
      };

      Voisin.prototype.startAnimeTxt = function(){
        this.$voisin.preAnime();
        (function(voisin){
          setTimeout(function(){voisin.$voisin.postAnime()}, 5000+Math.random()*5000);
        }(this));
      };

      Voisin.prototype.startAnimeImage = function(){
        this.$voisin.preAnime();
        (function(voisin){
          setTimeout(function(){voisin.$voisin.postAnime()}, 3000+Math.random()*10000);
        }(this));
      };

      Voisin.prototype.startAnimeVideo = function(){
        this.playVideo();
        this.$voisin.preAnime();
        (function(voisin){
          voisin.$.on('video_finished', function(){
            voisin.videoUnload();
            voisin.$voisin.postAnime();
          });  
        }(this));
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
    // console.log('placeBlock', $elmt);
    var defaults = {top:"rand",left:"rand"};   
    var options = $.extend({}, defaults, opts);
    
    // console.log('options', options);  
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
