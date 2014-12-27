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

  /**
  * VARS
  */

  var _$bordTime;
  var _$main;
  var _ajax_base_path;
  var _loaded = [];
  var _mode = "";
  var _Theme;
  var _Neighborhood;


  /**
  * FUNCTIONS
  */

  function init() {

    setupBordTime();

    if( !$('body').is('.front') )
      return;

    _ajax_base_path = Drupal.settings.basePath+Drupal.settings.pathPrefix;
    setupTV();
    setupEvent();
    getContent();

  }

  function setupTV() {

    _$main = $('#main');
    _$main.addClass('tv-show');
    $('> *', _$main).fadeOut();

  }

  function setupEvent() {

    $(window).on('theme-lpr-nid-recovered', themeNidRecovered);

  }

  function getContent() {
    $.getJSON(_ajax_base_path+'ajax/tv-show/give-me-a-theme', {loaded: _loaded}, success);
  };

  function success(data) {
    console.log("this is a theme:", data);
    _loaded.push(data.nid);
    _mode = data.mode;
    $(window).trigger('theme-lpr-nid-recovered', data.nid );
  }

  /* =LOAD */
  function themeNidRecovered(event,nid) {
    $('body').removeClass("random-mode program-mode").addClass(_mode+'-mode');
    _Theme = new Theme(nid);
  }

  /* =BORD TIME */
  function setupBordTime() {
    _$bordTime = $('<div>').attr('id', 'bord-time').appendTo('body');
    _$bordTime.append( $('<div>').addClass('container') );
    moveBordTime();
    setInterval(function(){
      moveBordTime();
    }, 6000); // 6000ms = 1 min.
  };

  function moveBordTime() {
    var date = new Date();
    var G = date.getHours();
    var i = date.getMinutes();
    var daymns = 24*60;
    var top = ((G*60+i)/daymns) * 80;
    _$bordTime.css('top', top + '%');
  };

  /* =READY
  -----------------------------------------------------------------------------*/
  $(document).ready(init);

  /* =THEME
  -----------------------------------------------------------------------------*/
  function Theme(nid) {

    this.$ = $(this);
    this.nid = 300;//212;//nid;
    this.id = "#theme-"+this.nid
    this.container = "#container-theme-"+this.nid
    this.html = 'empty';
    this.vimeo = {
      iframe : null,
      $player : null,
      status : null,
    };
    this.voisins = {
      nids : [],
      loaded : [],
    };

    /* PROTOTYPES */
    if(typeof Theme.prototype.initialized == "undefined"){

      Theme.prototype.nodeLoad = function() {
        var theme = this;
        $.getJSON(_ajax_base_path+'ajax/tv-show/node-load', {'nid':theme.nid}, function(data){ theme.nodeLoaded(data); } );
      };

      Theme.prototype.nodeLoaded = function(data) {
        console.log('Theme :: Loaded',data);

        // Save datas
        this.html = data.html;
        this.voisins.nids = data.voisins_nids;

        // Init actions.
        this.neighbours();
        this.append();
        this.events();
      };

      Theme.prototype.neighbours = function() {
        _Neighborhood = new Neighborhood(this.voisins.nids,this.container);
      }

      Theme.prototype.append = function() {
        console.log("Theme :: node append");
        // Append theme to DOM.
        _$main.append(
          $('<div>')
            .attr('id', this.container.replace('#',''))
            .append(
              $(this.html)
                .attr('id', this.id.replace('#',''))
                .addClass('theme')
            )
        );
      }

      Theme.prototype.events = function() {

        var theme = this;

        this.$
          .one('show-lpr-theme',   this.show )
          .one('shown-lpr-theme',  this.shown )
          .one('hide-lpr-theme',   this.hide )
          .one('hidden-lpr-theme', this.hidden )
          .one('play-lpr-vimeo',   this.vimeoPlay );

        $(this.id + ' iframe').load(function() {
          $f(this).addEvent('ready', function(id){ theme.vimeoInit(id); });
        });

      }

      Theme.prototype.show = function(event) {
        console.log('Theme :: show');
        var theme = this;
        $(this.id)
          .addClass('show-lpr');
        $('figure', $(this.id))
          .one('bsTransitionEnd', function(event) {
            theme.$.trigger('shown-lpr-theme');
          });
      };

      Theme.prototype.shown = function(event) {
        console.log('Theme :: shown');
        $(this.id)
          .addClass('shown-lpr');

        // Theme is displayed, active Neighborhood.
        _Neighborhood.$.trigger('show-lpr-neighborhood');
      };

      Theme.prototype.hide = function(event) {
        console.log('Theme :: hide');
        var theme = this;
        $(this.id)
          .addClass('hide-lpr')
          .one('bsTransitionEnd', function(event) {
            theme.$.trigger('hidden-lpr-theme');
          });
      };

      Theme.prototype.hidden = function(event) {
        console.log('Theme :: hidden');
        $(this.id).addClass('hidden-lpr');
      };




      Theme.prototype.vimeoInit = function(id) {
        console.log('Theme :: vimeo init',id);

        this.vimeo.iframe  = $('#'+id)[0];
        this.vimeo.$player = $f(this.vimeo.iframe);
        this.vimeo.status  = $('.status');

        this.vimeoEvents();

        // DEV
        // ajout d’un bouton pour aller 10s avant la fin de la vidéo.
        var theme = this;
        $(this.id).on('click', '.seek', function(event) {
          event.preventDefault();
          /* Act on the event */
          theme.vimeo.$player.api('getDuration', function (value, player_id) {
            console.log('Theme :: duration',value);
            theme.vimeo.$player.api('seekTo', (value-10));
          });
        });
        $(this.id).prepend(
          $('<button>')
            .addClass('seek btn btn-default')
            .html('Goto end -10s')
        );
        //end dev

      };

      Theme.prototype.vimeoEvents = function() {

        var theme = this;

        this.vimeo.status.text('ready');

        this.vimeo.$player
          .addEvent('pause',        function(id)     { theme.vimeoPause(id) })
          .addEvent('finish',       function(id)     { theme.vimeoFinish(id) })
          .addEvent('playProgress', function(data,id){ theme.vimeoPlayProgress(data,id) });

        this.$.trigger('show-lpr-theme');
        this.$.trigger('play-lpr-vimeo');
      };

      Theme.prototype.vimeoPlay = function(id) {
        console.log('Theme :: vimeo Play');
        this.vimeo.$player.api("play");
      };

      Theme.prototype.vimeoPause = function(id) {
        console.log('Theme :: vimeo Pause');
        this.vimeo.status.text('paused');
      };

      Theme.prototype.vimeoFinish = function(id) {
        console.log('Theme :: vimeo Finish');
        this.vimeo.status.text('finished');
      };

      Theme.prototype.vimeoPlayProgress = function(data,id) {
        // console.log("vimeo PlayProgress", data);
        this.vimeo.status.text(data.seconds + 's played');
        if( (data.duration - data.seconds) < 5 )
          this.$.trigger('hide-lpr-theme');
      }

    }// - end prototypes

    this.nodeLoad();

  }// - end Theme

  /* =NEIGHBORHOOD
  -----------------------------------------------------------------------------*/
  function Neighborhood(nids,container) {

    this.$ =      $(this);
    this.nids =   nids;
    this.container = container;
    this.called = 0;
    this.loaded = [];
    this.timer =  null;


    /* PROTOTYPES */
    if(typeof Neighborhood.prototype.initialized == "undefined"){

      Neighborhood.prototype.init = function() {
        var neighborhood = this;
        $.getJSON(_ajax_base_path+'ajax/tv-show/give-me-a-neighbour', {'voisins_nids': this.nids}, function(data){ neighborhood.nodeLoaded(data); } );
      };

      Neighborhood.prototype.nodeLoaded = function(data) {
        console.log('Neighborhood :: Loaded',data);
        this.nids = data.nids;

        // Init actions.
        this.events();
      };

      Neighborhood.prototype.events = function() {

        this.$
          .on('show-lpr-neighborhood', this.show )
          .one('loaded-lpr-neighborhood-watch', this.neighbourLoaded )
          .one('hide-lpr-neighborhood-watch',   this.neighbourHide );
      };

      Neighborhood.prototype.show = function() {
        var neighborhood = this;

        console.log('Neighborhood invoc Neighbour',this.called);
        console.log('this.nids',this.nids);

        if( this.called < 4 ) {
          var nid = this.nids.shift();
          var neighbour = new Neighbour(nid,this.container);
          this.called ++;
        }

        clearTimeout(this.timer);
        this.timer = setTimeout(function(){
          neighborhood.$.trigger('show-lpr-neighborhood');
        }, 20000);
      };

      Neighborhood.prototype.neighbourLoaded = function(event,nid) {
        console.log('Neighborhood :: neighbour Loaded');
      };

      Neighborhood.prototype.neighbourHide = function(event,nid) {
        console.log('Neighborhood :: neighbour Hide');
        this.called --;
      };

    }// - end prototypes

    this.init();

  }// - end Neighborhood

  /* =NEIGHBOUR
  -----------------------------------------------------------------------------*/
  function Neighbour(nid,container) {

    this.$ =         $(this);
    this.nid =       nid;
    this.id =        "#neighbour-"+this.nid
    this.container = container;
    this.html =      'empty';
    this.duration =  null;
    this.vimeo = {
      iframe: null,
      $player: null,
      status: null,
    };

    /* PROTOTYPES */
    if(typeof Neighbour.prototype.initialized == "undefined"){

      Neighbour.prototype.nodeLoad = function() {
        var neighbour = this;
        $.getJSON(_ajax_base_path+'ajax/tv-show/node-load', {'nid':neighbour.nid}, function(data){ neighbour.nodeLoaded(data); } );
      };

      Neighbour.prototype.nodeLoaded = function(data) {
        console.log('Neighbour :: Loaded',data);

        // Save datas
        this.html = data.html;
        this.duration = data.duration;
        this.mediatype = data.mediatype;

        // Init actions.
        this.append();
        this.events();

        // WHen it’s loaded, inform the Neighborhood.
        _Neighborhood.$.trigger( 'loaded-lpr-neighborhood-watch', this.nid );
      };

      Neighbour.prototype.append = function() {
        console.log("Neighbour :: Display");
        // Append theme to DOM.
        $(this.container).append(
          $(this.html)
            .attr('id', this.id.replace('#',''))
            .addClass('neighbour')
        );
      }

      Neighbour.prototype.events = function() {

        var neighbour = this;

        this.$
          .one('show-lpr-neighbour',   this.show )
          .one('shown-lpr-neighbour',  this.shown )
          .one('hide-lpr-neighbour',   this.hide )
          .one('hidden-lpr-neighbour', this.hidden )
          .one('play-lpr-neighbourVimeo', this.vimeoPlay );

        if( $(this.id + ' iframe').length > 0 ) {
          $(this.id + ' iframe').load(function() {
            $f(this).addEvent('ready', function(id){ neighbour.vimeoInit(id); });
          });
        } else {
          setTimeout(function(){
            neighbour.$.trigger('show-lpr-neighbour');
          },500);
        }

      }

      Neighbour.prototype.show = function(event) {
        console.log('Neighbour :: show');
        var neighbour = this;
        $(this.id)
          .addClass('show-lpr')
          .one('bsTransitionEnd', function(event) {
            neighbour.$.trigger('shown-lpr-neighbour');
          });
      };

      Neighbour.prototype.shown = function(event) {
        console.log('Neighbour :: shown');
        var neighbour = this;

        $(this.id)
          .addClass('shown-lpr');

        // If duration set, start Timer.
        if( this.duration > 0 ) {
          setTimeout(function(){
            neighbour.$.trigger('hide-lpr-neighbour');
          }, this.duration*1000 );
        }
      };

      Neighbour.prototype.hide = function(event) {
        console.log('Neighbour :: hide');
        var neighbour = this;
        $(this.id)
          .addClass('hide-lpr')
          .one('bsTransitionEnd', function(event) {
            neighbour.$.trigger('hidden-lpr-neighbour');
          });

        // When it’s hidding, inform the Neighborhood.
        _Neighborhood.$.trigger( 'hide-lpr-neighborhood-watch', this.nid );
      };

      Neighbour.prototype.hidden = function(event) {
        console.log('Neighbour :: hidden');
        $(this.id).addClass('hidden-lpr');
      };




      Neighbour.prototype.vimeoInit = function(id) {
        console.log('Neighbour :: vimeo init',id);

        this.vimeo.iframe  = $('#'+id)[0];
        this.vimeo.$player = $f(this.vimeo.iframe);
        this.vimeo.status  = $('.status');

        this.vimeoEvents();

      };

      Neighbour.prototype.vimeoEvents = function() {

        var neighbour = this;

        this.vimeo.status.text('ready');

        this.vimeo.$player
          .addEvent('pause',        function(id)     { neighbour.vimeoPause(id) })
          .addEvent('finish',       function(id)     { neighbour.vimeoFinish(id) })
          .addEvent('playProgress', function(data,id){ neighbour.vimeoPlayProgress(data,id) });

        this.$.trigger('show-lpr-neighbour');
        this.$.trigger('play-lpr-neighbourVimeo');
      };

      Neighbour.prototype.vimeoPlay = function(id) {
        console.log('Neighbour :: vimeo Play');
        this.vimeo.$player.api("play");
      };

      Neighbour.prototype.vimeoPause = function(id) {
        console.log('Neighbour :: vimeo Pause');
        this.vimeo.status.text('paused');
      };

      Neighbour.prototype.vimeoFinish = function(id) {
        console.log('Neighbour :: vimeo Finish');
        this.vimeo.status.text('finished');
      };

      Neighbour.prototype.vimeoPlayProgress = function(data,id) {
        this.vimeo.status.text(data.seconds + 's played');
        if( (data.duration - data.seconds) < 5 )
          this.$.trigger('hide-lpr-neighbour');
      }

    }// - end prototypes

    this.nodeLoad();

  }// - end Neighbour




  /* =Dév.
  -----------------------------------------------------------------------------*/
  $(document).on('keypress', function(event){

    if (event.ctrlKey || event.metaKey) { // With command key
      switch (String.fromCharCode(event.which)) {
        case ';':
          event.preventDefault();
          $('body').toggleClass("dev");
          break;
        case ' ':
          event.preventDefault();
          getContent();
          break;
      }
    }
  });

})(jQuery);