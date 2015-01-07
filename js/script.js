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
  var _Neighbourhood;


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
    $(window).on('theme-lpr-nid-recovered',   themeNidRecovered);
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

  /* =load */
  function themeNidRecovered(event,nid) {
    $('body').removeClass("random-mode program-mode").addClass(_mode+'-mode');
    _Theme = new Theme(nid);
    _Theme.$.one('hide-lpr-theme', getContent);
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

    this.$ =         $(this);
    this.nid =       nid;//300;//212;
    this.id =        "#theme-"+this.nid
    this.container = "#container-theme-"+this.nid
    this.html =      'empty';
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
        console.log('Theme :: Loaded');//,data);

        // Save datas
        this.html = data.html;
        this.voisins.nids = data.voisins_nids;

        // Init actions.
        this.neighbours();
        this.append();
        this.events();
      };

      Theme.prototype.neighbours = function() {
        _Neighbourhood = new Neighbourhood(this.voisins.nids,this.container);
      }

      Theme.prototype.append = function() {
        console.log("Theme :: node append");
        // Append theme to DOM.
        _$main.append(
          $('<div>')
            .attr('id', this.container.replace('#',''))
            .addClass('container-theme')
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
          .one('play-lpr-vimeo',   this.vimeoStart );

        $(this.id + ' iframe')
          .one('load', function(event){

            console.log( 'THEME :: iframe =', $(this) );
            console.log( 'THEME :: theme.id', theme.id );

            var iframe = $(this)[0];
            var player = $f(iframe);
            theme.vimeo.$player = player;

            // When the player is ready, add listeners for pause, finish, and playProgress
            player.addEvent('ready', function() {
              player.addEvent('play',         function(id) { theme.vimeoPlay(id)   });
              player.addEvent('pause',        function(id) { theme.vimeoPause(id)  });
              player.addEvent('finish',       function(id) { theme.vimeoFinish(id) });
              player.addEvent('playProgress', function(data, id) { theme.vimeoPlayProgress(data, id) });

              theme.$.trigger('show-lpr-theme');
              theme.$.trigger('play-lpr-vimeo');
            });

            // DEV
            // ajout d’un bouton pour aller 10s avant la fin de la vidéo.
            $(theme.id).on('click', '.seek', function(event) {
              event.preventDefault();
              /* Act on the event */
              theme.vimeo.$player.api('getDuration', function (value, player_id) {
                console.log('Theme :: duration',value);
                theme.vimeo.$player.api('seekTo', (value-10));
              });
            });
            $(theme.id).prepend(
              $('<button>')
                .addClass('seek btn btn-default')
                .html('Goto end -10s')
            );
            //end dev

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

        // Theme is displayed, active Neighbourhood.
        _Neighbourhood.$.trigger('show-lpr-neighbourhood');
      };

      Theme.prototype.hide = function(event) {
        console.log('Theme :: hide');
        var theme = this;
        $(this.id)
          .addClass('hide-lpr')
          .one('bsTransitionEnd', function(event) {
            theme.$.trigger('hidden-lpr-theme');
          });

        // Theme is hide, desactive Neighbourhood.
        _Neighbourhood.$.trigger('hide-lpr-neighbourhood');
      };

      Theme.prototype.hidden = function(event) {
        console.log('Theme :: hidden');
        var theme = this;
        $(this.id)
          .addClass('hidden-lpr')
          .remove();
        this.$.off();
      };



      Theme.prototype.vimeoStart = function() {
        console.log('THEME :: Start vimeo playing');
        this.vimeo.$player.api("play");
      };

      Theme.prototype.vimeoPlay = function(id) {
        console.log("THEME :: VIMEO ---> [Play]",id);
      }

      Theme.prototype.vimeoPause = function(id) {
        console.log("THEME :: VIMEO ---> [Pause]",id);
      }

      Theme.prototype.vimeoFinish = function(id) {
        console.log("THEME :: VIMEO ---> [Finish]");
      }

      Theme.prototype.vimeoPlayProgress = function(data, id) {
        // console.log("THEME :: VIMEO ---> " + data.seconds + 's played');
        if( (data.duration - data.seconds) < 5 )
          this.$.trigger('hide-lpr-theme');
      }

    }// - end prototypes

    this.nodeLoad();

  }// - end Theme

  /* =NEIGHBORHOOD
  -----------------------------------------------------------------------------*/
  function Neighbourhood(nids,container) {

    this.$ =          $(this);
    this.nids =       nids;
    this.container =  container;
    this.called =     0;
    this.neighbours = [];
    this.timer =      null;

    /* PROTOTYPES */
    if(typeof Neighbourhood.prototype.initialized == "undefined"){

      Neighbourhood.prototype.init = function() {
        var neighbourhood = this;
        $.getJSON(_ajax_base_path+'ajax/tv-show/give-me-a-neighbour', {'voisins_nids': this.nids}, function(data){ neighbourhood.nodeLoaded(data); } );
      };

      Neighbourhood.prototype.nodeLoaded = function(data) {
        console.log('Neighbourhood :: Loaded');//,data);
        this.nids = data.nids;

        // Init actions.
        this.events();
      };

      Neighbourhood.prototype.events = function() {

        this.$
          .on('show-lpr-neighbourhood',          this.show )
          .one('loaded-lpr-neighbourhood-watch', this.neighbourLoaded )
          .one('hide-lpr-neighbourhood-watch',   this.neighbourHide )
          .one('hide-lpr-neighbourhood',         this.hide );
      };

      Neighbourhood.prototype.show = function() {
        var neighbourhood = this;

        // console.log('Neighbourhood invoc Neighbour',this.called);
        // console.log('this.nids',this.nids);

        if( this.called < 4 ) {
        // if( this.called < 1 ) {
          var nid = this.nids.shift();
          var neighbour = new Neighbour(nid,this.container);
          this.neighbours.push(neighbour);
          this.called ++;
        }

        clearTimeout(this.timer);
        this.timer = setTimeout(function(){
          neighbourhood.$.trigger('show-lpr-neighbourhood');
        }, 20000);
      };

      Neighbourhood.prototype.hide = function() {
        // console.log('Neighbourhood revoc Neighbour', this.called);
        // console.log('this.nids',this.nids);

        this.$.off();

        // Revoc all Neighbours
        for (var i = 0; i < this.neighbours.length; i++) {
          console.log("this.neighbours[]["+i+"]");
          this.neighbours[i].request.abort(); // abort the ajax request if neighbour hasn’t finish to load.
          this.neighbours[i].$.trigger('hide-lpr-neighbour'); // hide him
        };

      };

      Neighbourhood.prototype.neighbourLoaded = function(event,nid) {
        console.log('Neighbourhood :: neighbour Loaded');
      };

      Neighbourhood.prototype.neighbourHide = function(event,nid) {
        console.log('Neighbourhood :: neighbour Hide');
        this.called --;
      };

    }// - end prototypes

    this.init();

  }// - end Neighbourhood

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
      clinicalDeath: null,
    };
    this.request;

    /* PROTOTYPES */
    if(typeof Neighbour.prototype.initialized == "undefined"){

      Neighbour.prototype.nodeLoad = function() {
        var neighbour = this;
        this.request = $.getJSON(_ajax_base_path+'ajax/tv-show/node-load', {'nid':neighbour.nid}, function(data){ neighbour.nodeLoaded(data); } );
      };

      Neighbour.prototype.nodeLoaded = function(data) {
        console.log('Neighbour :: Loaded');//,data);

        // Save datas
        this.html = data.html;
        this.duration = data.duration;
        this.mediatype = data.mediatype;

        // Init actions.
        this.append();
        this.events();

        // WHen it’s loaded, inform the Neighbourhood.
        _Neighbourhood.$.trigger( 'loaded-lpr-neighbourhood-watch', this.nid );
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
          .one('show-lpr-neighbour',      this.show )
          .one('shown-lpr-neighbour',     this.shown )
          .one('hide-lpr-neighbour',      this.hide )
          .one('hidden-lpr-neighbour',    this.hidden )
          .one('play-lpr-neighbourVimeo', this.vimeoStart );

        if( $(this.id + ' iframe').length > 0 ) {

          $(this.id + ' iframe')
            .one('load', function(event){

              // console.log( 'NEIGHBOUR :: iframe =', $(this) );
              // console.log( 'NEIGHBOUR :: neighbour.id', neighbour.id );

              var iframe = $(this)[0];
              var player = $f(iframe);
              neighbour.vimeo.$player = player;

              // When the player is ready, add listeners for pause, finish, and playProgress
              player.addEvent('ready', function() {
                player.addEvent('play',         function(id) { neighbour.vimeoPlay(id)   });
                player.addEvent('pause',        function(id) { neighbour.vimeoPause(id)  });
                player.addEvent('finish',       function(id) { neighbour.vimeoFinish(id) });
                player.addEvent('playProgress', function(data, id) { neighbour.vimeoPlayProgress(data, id) });

                neighbour.$.trigger('show-lpr-neighbour');
                neighbour.$.trigger('play-lpr-neighbourVimeo');
              });

            });

        } else {
          setTimeout(function(){
            neighbour.$.trigger('show-lpr-neighbour');
          },500);
        }

      }

      Neighbour.prototype.show = function(event) {
        console.log('Neighbour :: show',this.id);
        var neighbour = this;
        $(this.id)
          .addClass('show-lpr')
          .one('bsTransitionEnd', function(event) {
            neighbour.$.trigger('shown-lpr-neighbour');
          });
      };

      Neighbour.prototype.shown = function(event) {
        console.log('Neighbour :: shown',this.id);
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
        console.log('Neighbour :: hide',this.id);
        var neighbour = this;
        $(this.id)
          .addClass('hide-lpr')
          .one('bsTransitionEnd', function(event) {
            neighbour.$.trigger('hidden-lpr-neighbour');
          });

        // When it’s hidding, inform the Neighbourhood.
        _Neighbourhood.$.trigger( 'hide-lpr-neighbourhood-watch', this.nid );
      };

      Neighbour.prototype.hidden = function(event) {
        console.log('Neighbour :: hidden',this.id);
        $(this.id)
          .addClass('hidden-lpr')
          .remove();
        this.$.off();
      };



      Neighbour.prototype.vimeoStart = function() {
        console.log('NEIGHBOUR :: Start vimeo playing',this.id);
        this.vimeo.$player.api("play");
      };

      Neighbour.prototype.vimeoPlay = function(id) {
        console.log("NEIGHBOUR :: VIMEO ---> [Play]",id);
        // check if a neighbour replay after stoping,
        //cancel the countdown to clinical death.
        clearTimeout(this.vimeo.clinicalDeath);
      }

      Neighbour.prototype.vimeoPause = function(id) {
        console.log("NEIGHBOUR :: VIMEO ---> [Pause]",id);
        // check if a neighbour stop playing for too long,
        // which is probably not good. In this case, we hide it.
        var neighbour = this;
        this.vimeo.clinicalDeath = setTimeout(function(){
          console.log("NEIGHBOUR :: VIMEO ---> [clinical death]",id);
          neighbour.$.trigger('hide-lpr-neighbour');
        },5000);
      }

      Neighbour.prototype.vimeoFinish = function(id) {
        console.log("NEIGHBOUR :: VIMEO ---> [Finish]",id);
      }

      Neighbour.prototype.vimeoPlayProgress = function(data, id) {
        // console.log("NEIGHBOUR :: VIMEO ---> " + data.seconds + 's played');
        // console.log("NEIGHBOUR :: VIMEO in vimeoPlayProgress; this = ", this);
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