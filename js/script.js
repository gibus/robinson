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

  var _debug = window.location.host.match(/^dev/gi) != null ? true : false;
  var _ajax_base_path;
  var _display_zone = {};// = {w:1024, h:768};
  var _cell_w = 340, _cell_h = 255, _line_h = _cell_h/4; // _cell_h = 249
  var _$stream_wrapper = $('<div>').attr('id','stream-wrapper').appendTo('#main');
  var _play_mode;

  var _prog_sequence;
  var _prog_sequence_length = 0;
  var _prog_cur_seq_index = -1;

  var _themas = [];
  var _voisins = [];
  var _displayed_themas = [];
  var _thema_loaded = 0;
  var _anime_voisins_ready = 0;

  var _$bordTime;

  function init(){
    _ajax_base_path = Drupal.settings.basePath+Drupal.settings.pathPrefix;

    if($('body').is('.logged-in') && $('body').is('.page-user'))
      return;

    initSoundCloud();
    initKeyboardShortcuts();
    initGraphics();

    getContent();
  };

  function initGraphics(){
    $('<div>').attr('id','no-interaction').appendTo('#main');
    setupBordTime();
    setupGrid();

    // $('h1', '#header')
    //   .clone().attr('id', 'site-name')
    //   .appendTo(_$stream_wrapper)
    //   .placeBlock({left:0})
    //   .notAnime();
  };

  function initSoundCloud(){
    SC.initialize({
      client_id: '705d246367c9a149b1450c8b069a504a'
    });
    // initiate auth popup
    // SC.connect(function() {
    //   SC.get('/me', function(me) {
    //     console.log('Hello, ' + me.username);
    //   });
    // });
  };

  function initKeyboardShortcuts(){

    // $(document)
    //   .bind('keydown', 'Alt+Shift+s:',shortcut_focusSearchField);
      // .bind('keydown', 'Alt+4',shortcut_viewmodeFull)
      // .bind('keydown', 'space',shortcut_togglePreview)
      // .bind('keydown', 'esc',shortcut_closeModaleContent)
      // .bind('keydown', 'up',shortcut_onUpArrow)
      // .bind('keydown', 'right',shortcut_onRightArrow)
      // .bind('keydown', 'down',shortcut_onDownArrow)
      // .bind('keydown', 'left',shortcut_onLeftArrow);
  };

  function getContent(){
    //console.log('getcontent');
    var dateObject = new Date();
    var currentTime = Math.round(dateObject.getTime()/1000);
    //console.log('currentTime = '+currentTime);


    $.getJSON(_ajax_base_path+'ajax/robinson/getcontent',
      {currentTime:currentTime, displayed_themas:_displayed_themas},
      contentLoaded
    );
  };

  function contentLoaded(json){
    //console.log("contentLoaded", json);

    _play_mode = json.mode;

    $('body').addClass(_play_mode+'-mode');

    switch(_play_mode){
      case 'random':
        playRandom(json);
        break;
      case 'program':
        playProgram(json);
    }
  };

  function playRandom(json){
    //console.log('playRandom', json);
    newThema(json.thema.nid);
  };

  function playProgram(json){
    //console.log("playProgram", json);
    _prog_sequence = json.sequence;
    _prog_sequence_length = json.sequence_length;
    _prog_cur_seq_index = -1;

    // TODO : program décompte
    // TODO : program intro
    programNextSequence();
  };

  function programNextSequence(){
    //console.log('program_next_sequence');
    _prog_cur_seq_index ++;

    if(_prog_sequence[_prog_cur_seq_index]){
      switch(_prog_sequence[_prog_cur_seq_index].type){
        case "thematique":
          newThema(_prog_sequence[_prog_cur_seq_index].nid);
          break;
        case "voisin":
          newVoisin(_prog_sequence[_prog_cur_seq_index].nid);
          break;
      }
    }else{
      _themas = null;
      _voisins = null;
      // TODO program outro
      getContent();
    }
  };

  function newThema(nid){
    //console.log("newThema");
    // move sitename in front
    $('#site-name', _$stream_wrapper)
      .notAnime()
      .detach()
      .appendTo(_$stream_wrapper);

    // purge themas in dom
    // $themas = $('.thema', _$stream_wrapper);
    // if(_themas.length > 5){
    //   // first mask the oldest
    //   _themas[0].$thema.notAnime();
    //   // then remove it from dom after 5sec

    //   setTimeout(function(){
    //     _themas[0].$thema.remove();
    //     // TODO : shift _thema array
    //     // delete _themas[0];
    //   }, 5000);
    // }

    // create new thema
    var thema = new Thema(nid)
    _themas.push(thema);

    $(document)
      .bind('keydown', 'right', function(){thema.endThema();})

    thema.$.on('finished', onItemFinished);
  };

  function newVoisin(nid){
    //console.log("newVoisin");

    // create voisin
    var voisin = new Voisin({nid:nid});
    _voisins.push(voisin);

    $(document)
      .bind('keydown', 'right', function(){voisin.endAnime();})

    voisin.$
      // .on('ready', playThema)
      // .on('finished', newThema);
      .on('finished', onItemFinished);
  };

  function onItemFinished(event){
    //console.log("onItemFinished :: _play_mode = "+ _play_mode);

    $(document).unbind('keydown');

    switch(_play_mode){
      case "random":
        _displayed_themas.push(this.nid);
        getContent();
        break;
      case "program":
        programNextSequence();
        break;
    }
  };

  /**
  * Program()
  */
  function Program(){

    /* PROTOTYPES */
    if(typeof Thema.prototype.initialized == "undefined"){

      Thema.prototype.initialized = true;
    }
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
    this.availablespace = Math.floor(_display_zone.surface_cells*1.12);
    this.played_voisins = [];
    this.played_voisinsnids = [];
    this.impulseFrequency = 5; // in seconds


    /* PROTOTYPES */
    if(typeof Thema.prototype.initialized == "undefined"){

      Thema.prototype.ajaxLoad = function(){
        //console.log('Thema :: ajaxload');
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
        // console.log('Thema :: initGraphics');
        $('<div>')
          .attr('id', 'thema-'+this.thema_id)
          .addClass('thema')
          .append(this.rendered_thema)
          .appendTo(_$stream_wrapper);

        this.$thema = $('#thema-'+this.thema_id, _$stream_wrapper);

        $('.thema-title', this.$thema).placeBlock({left:1, centred:true}).notAnime();
        $('.content', this.$thema)
          // .append($('h1', '#header').clone().addClass('site-name'))
          .placeBlock({left:0, centred:true}).notAnime();

        // TODO this should go out of Thema
        // $('#site-name', _$stream_wrapper).placeBlock({left:0});
      };

      Thema.prototype.listenVideo = function(){
        //console.log('Thema :: listenVideo');
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

        this.videoVolume = 0.3;
        $(document)
          // .bind('keydown', 'right', function(){thema.endThema();})
          .bind('keydown', 's', function(){thema.onVideoToggleSound();});
        // this.onVideoToggleSound();

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

      Thema.prototype.onVideoFinished = function(id){
        //console.log('Thema :: onVideoFinished | id = '+id);
        this.endThema();
      };

      Thema.prototype.onVideoToggleSound = function(){
        //console.log('Thema :: onVideoToggleSound');
        if(this.videoVolume){
          $f(this.video_id).api('setVolume', 0);
          this.videoVolume = 0;
        }else{
          $f(this.video_id).api('setVolume', 1);
          this.videoVolume = 0.3;
        }
      };

      Thema.prototype.videoPlay = function(){
        $f(this.video_id).api('play');
      };

      Thema.prototype.videoStop = function(){
        $f(this.video_id).api('stop');
      };

      Thema.prototype.videoUnload = function(){
        // $f(this.video_id).api('unload');
        var thema = this;

        (function(thema){
          setTimeout(function(){
            //console.log('Thema :: remove video');
            thema.$viframe.remove();
          }, 5000);
        }(thema));
      };

      Thema.prototype.startAnime = function(){
        //console.log("Thema :: startAnime");

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

      Thema.prototype.endThema = function(){
        //console.log('endThema');
        this.$viframe.parents('.content').postAnime();
        this.videoStop();
        this.videoUnload();

        for(var voisin in this.played_voisins){
          this.played_voisins[voisin].endAnime();
        }

        this.$.trigger('finished');
      };

      Thema.prototype.impulseVoisins = function(){
        if(this.ready_for_voisins && this.availablespace && !this.loading_voisin){
          //console.log('Thema :: impulseVoisins : availablespace : '+this.availablespace);

          this.loading_voisin = true;
          var thema = this;
          var voisin = new Voisin({thema:this});
          voisin.$
            .bind('loaded', function(event){thema.onVoisinLoaded(this, event)})
            .bind('aborted', function(event){thema.onVoisinAborted(this, event)})
            .bind('finished', function(event){thema.onVoisinFinished(this, event)});
        }
      };

      Thema.prototype.onVoisinLoaded = function(voisin, event){
        // console.log('Thema :: onVoisinLoaded : voisin', voisin);
        this.availablespace -= voisin.space;
        this.played_voisins.push(voisin);
        this.played_voisinsnids.push(voisin.nid);
        this.loading_voisin = false;
        if(voisin.media_type == "audio")
          this.is_playing_audio = true;
      };

      Thema.prototype.onVoisinAborted = function(voisin, event){
        // console.log('Thema :: onVoisinAborted');
        this.loading_voisin = false;
      };

      Thema.prototype.onVoisinFinished = function(voisin, event){
        // console.log("Thema :: onVideoFinished : voisin", voisin);
        this.availablespace += voisin.space;
        if(voisin.media_type == "audio")
          this.is_playing_audio = false;
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

    for(op in ops)
      this[op] = ops[op];


    // var voisin = this;
    this.$ = $(this);//.bind('end-voisin', function(){voisin.endAnime});


    /* PROTOTYPES */
    if(typeof Voisin.prototype.initialized == "undefined"){

      Voisin.prototype.ajaxLoad = function(){
        // console.info('Voisin :: ajaxload', this);// : this', this);
        var voisin = this;
        var params;
        if(this.nid){
          params = {voisin:{nid:this.nid}};
        }else if(this.thema){
          params = {thema:{
            nid                 :this.thema.nid,
            voisins_list        :this.thema.voisins_list,
            played_voisins_nids :this.thema.played_voisinsnids,
            availablespace      :this.thema.availablespace,
            is_playing_audio    :this.thema.is_playing_audio
          }};
        }

        $.getJSON(_ajax_base_path+'ajax/robinson/voisin',
          params,
          function(json){
            voisin.ajaxLoaded(json);
        });
      };

      Voisin.prototype.ajaxLoaded = function(datas){
        //console.log('Voisin :: ajaxLoaded',datas);
        // console.log('Voisin :: children : '+$(datas.voisin.rendered).find('article.voisin').children().size());

        if( datas.voisin ){
        // if( datas.voisin && $(datas.voisin.rendered).find('article.voisin').children().size() ){

          for(index in datas.voisin)
            this[index] = datas.voisin[index];

          this.$.trigger('loaded');

          this.start();
        }else{
          this.$.trigger('aborted');
        }
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
        // console.info('- - - - - - - Voisin :: start : media_type = '+this.media_type);
        this.is_playing = true;
        if(typeof this['start'+this.media_type] == 'function')
          this['start'+this.media_type].call(this);
      };

      /**
      * common init
      * html
      */
      Voisin.prototype.initCommons = function(){
        //console.log('Voisin :: initGraphics '+this.nid, this);
        if(this.thema){
          this.$voisin = $(this.rendered)
            .appendTo(this.thema.$thema)
            .notAnime();
        }else{
          $('<div>')
            .attr('id', 'voisin-'+this.nid)
            .addClass('voisin')
            .append(this.rendered)
            .appendTo(_$stream_wrapper);

          this.$voisin = $('#voisin-'+this.nid, _$stream_wrapper);
        }
      };

      Voisin.prototype.setSize = function(){
        var w = _cell_w * this.comportement.taille;
        //console.log('Voisin :: setSize : '+size);
        // this.$voisin.width(_cell_w * parseInt(this.taille.min + Math.random()*(this.taille.max-this.taille.min)));
        if(this.media_type == 'image'){
          var $img = this.$voisin.find('img');
          var img_h = parseInt($img.attr('height'));
          var img_w = parseInt($img.attr('width'));
          var h = w*img_h/img_w;
          $img.width(w).height(h);
        }

        this.$voisin.width(w);
      };

      Voisin.prototype.setDuree = function(){
        //console.log('Voisin :: setDuree');
        (function(voisin){
          setTimeout(function(){
            voisin.endAnime();
          }, voisin.comportement.duree*1000);
        }(this));
      };

      Voisin.prototype.endAnime = function(){
        //console.log('Voisin :: endAnime');
        if(this.is_playing){
          this.is_playing = false;
          switch(this.media_type){
            case "video":
              this.unloadVideo();
              break;
            case "audio":
              this.stopSound();
              break;
          }
          this.$voisin.postAnime();
          this.$.trigger('finished');
        }
      };

      /**
      * text
      */
      Voisin.prototype.starttext = function(){
        // console.info("Voisin :: start : text", this);
        this.initCommons();
        this.setSize();
        // var left = this.comportement.taille == 3 ? 0 : 1;
        this.$voisin.placeBlock({w_cell:this.comportement.taille}).preAnime();
        this.setDuree();
      };

      /**
      * image
      */
      Voisin.prototype.startimage = function(){
        //console.log("Voisin :: start : image", this);
        this.initCommons();
        this.setSize();
        // var left = this.comportement.taille == 3 ? 0 : 1;
        this.$voisin.placeBlock({w_cell:this.comportement.taille}).preAnime();
        this.setDuree();
      };

      /**
      * audio
      */
      Voisin.prototype.startaudio = function(){
        //console.log("Voisin :: start : audio", this);
        this.initCommons();
        this.setupSoundCloudPlayer();
        this.$voisin.css('top', -1000);
      };

      Voisin.prototype.setupSoundCloudPlayer = function(){
        // http://developers.soundcloud.com/docs#resolving
        // http://developers.soundcloud.com/docs/api/sdks#javascript
        // http://developers.soundcloud.com/docs/api/sdks

        // console.log('Voisin :: setupSoundCloudPlayer');
        var voisin = this;
        var $a = $('a[href^="https://soundcloud.com"]:first');
        var url = $a.attr('href');
        // var url = "https://soundcloud.com/fanfare-bleme/oiseaux-valldemossa/s-PQiPZ";
        // console.log('Voisin :: SC : track url',url);
        SC.get('/resolve', { url: url }, function(track, error) {

          if(error){
            //console.warn("Voisin :: SC resolving error", error);
            voisin.endAnime();
          }else{
            //console.log("Voisin :: SC resolved : track", track);

            if(!track.streamable){
              //console.warn("Voisin :: SC : not streamable : "+track.permalink_url);
              voisin.endAnime();
            }else{
              SC.stream(track.stream_url, {
                autoPlay:true,
                autoLoad:true,
                onplay:function(){voisin.onSoundPlay();},
                onfinish:function(){voisin.onSoundFinish();},
              },function(sound){
                //console.log('Voisin :: SC stream callback');
                voisin.sound = sound;
              });
            }
          }
        });
      };

      Voisin.prototype.stopSound = function(){
        try{
          this.sound.stop();
        }catch(error){
          //console.warn('Voisin :: SC : stopSound()', error);
        }
      };

      Voisin.prototype.onSoundPlay = function(){
        //console.log('Voisin :: onSoundPlay : sound',this.sound);
      };

      Voisin.prototype.onSoundFinish = function(){
        //console.log('Voisin :: onSoundFinish');
        this.endAnime();
      };

      /**
      * video
      */
      Voisin.prototype.startvideo = function(){
        //console.log("Voisin :: start : video", this);

        this.initCommons();
        this.setSize();
        // var left = this.comportement.taille == 3 ? 0 : 1;
        this.$voisin.placeBlock({w_cell:this.comportement.taille});

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
        this.video_visible = false;

        $f(id)
          .addEvent('play', function(id){voisin.onVideoPlay(id);})
          .addEvent('playProgress', function(data, id){voisin.onVideoPlayProgress(data, id);})
          .addEvent('pause', function(id){voisin.onVideoPause(id);})
          .addEvent('finish', function(id){voisin.onVideoFinished(id);});

        this.startAnimeVideo();
      };

      Voisin.prototype.startAnimeVideo = function(){
        this.playVideo();
        // this.$voisin.preAnime();

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
        // console.log('Voisin :: unloadVideo');
        // var $viframe = $('iframe', $voisin);
        // var id = $viframe.attr('id');

        // $f(this.video_id).api('unload');
        var voisin = this;

        (function(voisin){
          setTimeout(function(){
            // console.info('Voisin :: remove video');
            voisin.$viframe.remove();
          }, 5000);
        }(voisin));
      };

      Voisin.prototype.onVideoPlay = function(id){
        //console.log('Voisin :: onVideoPlay : id = '+id);
      };

      Voisin.prototype.onVideoPause = function(id){
        //console.log('Voisin :: onVideoPause : id = '+id);
      };

      Voisin.prototype.onVideoPlayProgress = function(data, id){
        // console.log('Voisin :: onVideoPlayProgress | id = '+id+' | data = ',data);
        var r = 2;

        if(!this.video_visible){
          if(data.seconds > r && data.seconds < (r+1)){
            this.video_visible = true;
            this.$voisin.preAnime();
          }
        }else{
          if((data.duration - data.seconds) < r*2){
          // if(data.seconds > (r+1)+5){
            this.video_visible = false;
            this.endAnime();
          }
        }
      };

      Voisin.prototype.onVideoFinished = function(id){
        //console.log('Voisin :: onVideoFinished | id = '+id);
        // onVideoFinish(id);
        // this.$.trigger('video_finished');
        this.unloadVideo();
        // this.endAnime();
      };

      Voisin.prototype.initialized = true;
    }

    this.ajaxLoad();
  }; // Voisins

  /* BORD TIME */
  function setupBordTime(){
    //console.group("setupBordTime");
    _$bordTime = $('<div>').attr('id', 'bord-time').appendTo('body');
    _$bordTime
      .append($('<div>').addClass('bord-time').addClass('bord-time-left'))
      .append($('<div>').addClass('bord-time').addClass('bord-time-right'));

    moveBordTime();
    setInterval(function(){
      moveBordTime();
    }, 1000*60);

    //console.groupEnd();
  };

  function moveBordTime(){
    //console.group('moveBordTime');
    var date = new Date();
    var hs = date.getHours();
    var mns = date.getMinutes();
    //console.log('hours = '+hs+' | minutes = '+mns);

    var daymns = 24*60;
    var top = ((hs*60+mns)/daymns) * ($(window).height() - _$bordTime.height());
    //console.log('top = '+top);

    _$bordTime.css('top', top);

    //console.groupEnd();
  };

  /* GRID */
  function setupGrid(){

    var h_cells = Math.floor(($(window).height()-100) / _cell_h);
    var w_cells = Math.floor(($(window).width()-100) / _cell_w);

    h_cells = h_cells % 2 ? h_cells: h_cells-1;
    w_cells = w_cells % 2 ? w_cells: w_cells-1;

    // console.log('h_cells : '+h_cells+' | w_cells = '+w_cells);

    // set the main display zone width and height on cell
    _display_zone.h_cells = h_cells;
    _display_zone.w_cells = w_cells;
    _display_zone.surface_cells = h_cells*w_cells;

    // set the main display zone width and height on pixels
    _display_zone.h = h_cells*_cell_h;
    _display_zone.w = w_cells*_cell_w;

    // set the main display zone position on pixels
    _display_zone.top = ($(window).height() - _display_zone.h)/2;
    _display_zone.left = ($(window).width() - _display_zone.w)/2;

    // set the left and top position for centre display in cell
    _display_zone.center_left_cell = (_display_zone.w_cells-3)/2;
    _display_zone.center_top_cell = (_display_zone.h_cells-3)/2;

    if(_debug) drawDebugGrid();
  };

  function drawDebugGrid(){
    var $g = $('<div>').attr('id','debug-grid').appendTo('body');

    $g.css({
      "top":_display_zone.top,
      "left":_display_zone.left,
      "width":_display_zone.w-2,
      "height":_display_zone.h-2
    });


    for (var i = 0; i < _display_zone.h_cells*2; i++) {
      $('<div>').addClass('lines').css({
        "top":_line_h+(_line_h*2)*i -1,
        "left":-1,
        "width":_display_zone.w-2,
        "height":_line_h-2
      }).appendTo($g);
    };

    for(var l = 0; l < _display_zone.h_cells; l++){
      for(var c = 0; c < _display_zone.w_cells; c++){
        $('<div>').addClass('cells').css({
          "top":_cell_h*l-1,
          "left":_cell_w*c-1,
          "width":_cell_w-2,
          "height":_cell_h-2
        }).appendTo($g);
      }
    }

    // $('<div>').addClass('cells').css({
    //   "top":-1,
    //   "left":_cell_w-1,
    //   "width":_cell_w-2,
    //   "height":_display_zone.h-2
    // }).appendTo($g);

    // $('<div>').addClass('cells').css({
    //   "top":_cell_h-1,
    //   "left":-1,
    //   "width":_display_zone.w-2,
    //   "height":_cell_h-2
    // }).appendTo($g);

    // for (var i = 0; i < 6; i++) {
    //   $('<div>').addClass('lines').css({
    //     "top":_line_h+(_line_h*2)*i -1,
    //     "left":-1,
    //     "width":_display_zone.w-2,
    //     "height":_line_h-2
    //   }).appendTo($g);
    // };
  };

  function placeBlock($elmt, opts){
    //console.group('placeBlock', $elmt);
    var defaults = {top:"rand",left:"rand", centred:false};
    var options = $.extend({}, defaults, opts);
    var top_cell, left_cell;
    //console.log("options", options);

    // VERTICAL - - - - - - - - - - - - - - - -
    if(options.top == "rand"){
      // get the free cells to display, depending on centred or not
      var top_free_cells = options.centred
        ? Math.floor( (3*_cell_h - $elmt.height() +_line_h )/_line_h)
        : Math.floor( (_display_zone.h_cells*_cell_h - $elmt.height() +_line_h )/_line_h);

      var top_cell = Math.floor(Math.random()*(top_free_cells));
    }else{
      top_cell = options.top;
    }

    // decal the block depending on centred or not
    top_cell = options.centred
      ? top_cell + _display_zone.center_top_cell
      : top_cell;

    var top = _display_zone.top + top_cell*_line_h;

    // HORIZONTAL - - - - - - - - - - - - - - - -
    var elmt_w_cell = options.w_cell ? options.w_cell : Math.floor($elmt.width()/_cell_w);
    if(options.left == "rand"){
      // get the free cells to display, depending on centred or not
      var left_free_cells = options.centred
        // ? Math.floor( (3*_cell_w - $elmt.width() )/_cell_w)
        // : Math.floor( ( _display_zone.w_cells*_cell_w - $elmt.width() )/_cell_w);
        ? 3 - elmt_w_cell
        : _display_zone.w_cells - elmt_w_cell;


      var left_cell = Math.floor(Math.random()*(left_free_cells));

      // if(!options.centred){
      //   console.info('_display_zone.center_left_cell = '+_display_zone.center_left_cell);
      //   console.info('elmt_w_cell = '+elmt_w_cell);
      //   console.info('first left_cell = '+left_cell);
      //   console.info('-');
      //   console.info('elmnt is on the left : ', left_cell <= _display_zone.center_left_cell+1);
      //   console.info('elmt cover the column 1 of center : ', elmt_w_cell >= (_display_zone.center_left_cell+1-left_cell));
      //   console.info('elmt width is less than 3 column and there is free marges : ', ((elmt_w_cell == 3 && _display_zone.center_left_cell > 0) || elmt_w_cell < 3));
      //   console.info('-');
      // }

      // avoid to cover the column 1 in center zone
      left_cell = options.centred
        // if centred
        ? left_cell == 0 && elmt_w_cell < 3
          ? left_cell + 1
          : left_cell
        // if not centred (more complicated)
        // if elmt is on the left or on the column 1 of center zone
        // and if elmt cover the column 1
        // and if elmt width is less than 3 column and marge are not null
        // so move the elemnt to the right of column 1 of center zone
        : left_cell <= _display_zone.center_left_cell+1
          && elmt_w_cell >= (_display_zone.center_left_cell+1-left_cell)
          && ((elmt_w_cell == 3 && _display_zone.center_left_cell > 0) || elmt_w_cell < 3)
          ? left_cell = _display_zone.center_left_cell+1+Math.floor(Math.random()*(_display_zone.center_left_cell+3-elmt_w_cell))
          : left_cell;

      // if(!options.centred){
      //   console.info('second left_cell = '+left_cell);
      // }

    }else{
      var left_cell = options.left;
    }

    // decal the block depending on centred or not
    left_cell = options.centred
      ? left_cell + _display_zone.center_left_cell
      : left_cell;

    var left = _display_zone.left + left_cell*_cell_w;

    // apply result to $element
    $elmt
      .css({
        "top":top+'px',
        "left":left+'px',
      })
      .addClass('placed');
    //console.groupEnd();
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
