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
  var _Content; // could be a theme or a program.


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
    // $('> *', _$main).fadeOut();

  }

  function setupEvent() {

    $(window).on('theme-lpr-nid-recovered', themeNidRecovered);
    $(window).on('program-lpr-nid-recovered', programNidsRecovered);

  }

  function getContent() {

    $.getJSON(_ajax_base_path+'ajax/tv-show/give-me-a-theme', {loaded: _loaded}, success);

  };

  function success(data) {
    console.log("This is a theme:", data);
    if( data.nid ) {
      _loaded.push(data.nid);
      _mode = data.mode;

      $('body')
        .removeClass("random-mode program-mode")
        .addClass(_mode+'-mode');

      if( _mode == "random" )
        $(window).trigger('theme-lpr-nid-recovered', data.nid );
      else
        $(window).trigger('program-lpr-nid-recovered', data );

    } else {
      console.log("Hoops. No Nid came in.");
    }
  }

  function forceElementInViewport($el) {
    if( $el.length > 0 ) {
      var rect = $el[0].getBoundingClientRect();
      if( rect.bottom >= (window.innerHeight || document.documentElement.clientHeight) ) {
        console.log("[forceElementInViewport]", $el.attr('class'));
        if( $el.hasClass('col-offset-top-1') ) {
          var n = 1;
          var nn = 0;
        } else {
          var cl = $el.attr('class');
          var n = parseInt(/col-offset-top-(\d+)/.exec(cl)[1], 10);
          var nn = Math.floor(Math.random() * (n-1));
        }
        $el.removeClass('col-offset-top-'+n).addClass('col-offset-top-'+nn);
        if( nn > 0 )
          forceElementInViewport($el);
      }
    }
  }

  /* =load */
  function themeNidRecovered(event,nid) {
    _Content = new Theme(nid);
    _Content.$.one('hide-lpr-theme', getContent);
  }

  function programNidsRecovered(event,data) {
    _Content = new Program(data.nid,data.nids);
    _Content.$.one('hide-lpr-program', getContent);
  }

  /* =BORD TIME */
  function setupBordTime() {
    _$bordTime = $('<div>').attr('id', 'bord-time').appendTo('body');
    _$bordTime.append( $('<div>').addClass('container') );
    moveBordTime();
    setInterval(function(){
      moveBordTime();
    }, 60000); // 60000ms = 1 min.
  };

  function moveBordTime() {
    var date = new Date();
    var G = date.getHours();
    var i = date.getMinutes();
    var daymns = 24*60;
    var top = ((G*60+i)/daymns) * 80;
    _$bordTime.css('top', top + '%');
  };



  /* =PROGRAM
  -----------------------------------------------------------------------------*/
  function Program(nid,nids) {

    console.log(" - - - - - - - - - New Program - - - - - - - - - ");

    this.$ =               $(this);
    this.nid =             nid;
    this.nids =            nids;
    this.id =              "#program-"+this.nid;
    this.container =       "#container-prog-"+this.nid;
    this.currentSequence = null;
    this.sequences =       [];
    this.timer =           null;

    /* PROTOTYPES */
    if(typeof Program.prototype.initialized == "undefined"){

      Program.prototype.init = function() {

        this.append();
        this.events();
        this.invocSequence();

      };

      Program.prototype.append = function() {
        console.log("Program :: node append");
        // Append theme to DOM.
        _$main.append(
          $('<div>')
            .attr('id', this.container.replace('#',''))
            .addClass('container-prog')
            .append(
              $(this.html)
                .attr('id', this.id.replace('#',''))
                .addClass('program')
            )
        );
      }

      Program.prototype.events = function() {

        this.$
          .on('show-lpr-sequence',  this.invocSequence )
          .one('hide-lpr-sequence', this.hide );

      };

      Program.prototype.invocSequence = function() {

        console.log('Program :: invoc Sequence');
        // console.log('this.nids',this.nids);

        var program = this;

        var sequence = this.nids.shift();

        if( sequence ) {

          var nid =  sequence.nid;
          var type = sequence.ctype;

          if ( type == 'voisin' ) {

            // * neighbour
            this.currentSequence = new Neighbour(nid,this.container);
            this.sequences.push(this.currentSequence);
            this.currentSequence.$.on('hide-lpr-neighbourhood-watch',   function(event) { program.sequenceHide(event); });

          } else if ( type == 'thematique' ) {

            // * theme
            this.currentSequence = new Theme(nid);
            this.sequences.push(this.currentSequence);
            this.currentSequence.$.one('hide-lpr-theme', function(event) { program.sequenceHide(event); });

          };

        } else {
          this.$.trigger('hide-lpr-program');
        }


      };

      Program.prototype.hide = function() {
        console.log('Program :: hide');
        this.$.off();
      };

      Program.prototype.sequenceHide = function(event) {
        console.log('Program :: sequence Hide');
        var program = this;
        clearTimeout(this.timer);
        var delay = this.currentSequence.delay || 1;
        this.timer = setTimeout(function(){
          // queue the sequences, when one finish, invoc a new one
          program.$.trigger('show-lpr-sequence');
        }, delay*1000 );
      };

    }// - end prototypes

    this.init();

  }// - end Program



  /* =THEME
  -----------------------------------------------------------------------------*/
  function Theme(nid) {

    console.log(" - - - - - - - - - New Theme - - - - - - - - - ");

    this.$ =         $(this);
    this.nid =       nid;//300;//212;
    this.id =        "#theme-"+this.nid
    this.container = "#container-theme-"+this.nid
    this.html =      'empty';
    this.vimeo = {
      iframe : null,
      $player : null,
      status : null,
      clinicalDeath : null,
    };
    this.voisins = {
      nids : [],
      loaded : [],
    };
    this.neighbourhood = null;

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
        this.neighbourhood = new Neighbourhood(this.voisins.nids,this.container);
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

            console.log( 'Theme :: iframe =', $(this) );
            console.log( 'Theme :: theme.id', theme.id );

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

        forceElementInViewport( $('article.node',$(this.id)) );
        forceElementInViewport( $('aside.node',$(this.id)) );
      };

      Theme.prototype.shown = function(event) {
        console.log('Theme :: shown');
        $(this.id)
          .addClass('shown-lpr');

        // Theme is displayed, active Neighbourhood.
        this.neighbourhood.$.trigger('show-lpr-neighbourhood');
      };

      Theme.prototype.hide = function(event) {
        console.log('Theme :: hide');
        var theme = this;

        theme.vimeo.$player.removeEvent('pause');

        $(this.id)
          .addClass('hide-lpr')
          .one('bsTransitionEnd', function(event) {
            theme.$.trigger('hidden-lpr-theme');
          });

        // Theme is hide, desactive Neighbourhood.
        this.neighbourhood.$.trigger('hide-lpr-neighbourhood');
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
        console.log('Theme :: Start vimeo playing');
        this.vimeo.$player.api("play");
      };

      Theme.prototype.vimeoPlay = function(id) {
        console.log("Theme :: vimeo ---> [Play]",id);
        // check if a neighbour replay after stoping,
        // cancel the countdown to clinical death.
        clearTimeout(this.vimeo.clinicalDeath);
      }

      Theme.prototype.vimeoPause = function(id) {
        console.log("Theme :: vimeo ---> [Pause]",id);
        // force video playing.
        this.vimeo.$player.api("play");
        var theme = this;
        this.vimeo.clinicalDeath = setTimeout(function(){
          console.log("Theme :: vimeo ---> [clinical death]",id);
          theme.$.trigger('hide-lpr-theme');
        }, 30000); // 30s
      }

      Theme.prototype.vimeoFinish = function(id) {
        console.log("Theme :: vimeo ---> [Finish]");
        clearTimeout(this.vimeo.clinicalDeath);
      }

      Theme.prototype.vimeoPlayProgress = function(data, id) {
        // console.log("Theme :: vimeo ---> " + data.seconds + 's played');
        if( (data.duration - data.seconds) < 5 )
          this.$.trigger('hide-lpr-theme');
      }

    }// - end prototypes

    this.nodeLoad();

  }// - end Theme



  /* =NEIGHBORHOOD
  -----------------------------------------------------------------------------*/
  function Neighbourhood(nids,container) {

    this.$ =                $(this);
    this.nids =             nids;
    this.container =        container;
    this.called =           0;
    this.currentNeighbour = null;
    this.neighbours =       [];
    this.timer =            null;

    /* PROTOTYPES */
    if(typeof Neighbourhood.prototype.initialized == "undefined"){

      Neighbourhood.prototype.init = function() {
        var neighbourhood = this;
        $.getJSON(_ajax_base_path+'ajax/tv-show/give-me-a-neighbour', {'voisins_nids': this.nids}, function(data){ neighbourhood.nodeLoaded(data); } );
      };

      Neighbourhood.prototype.nodeLoaded = function(data) {
        console.log('Neighbourhood :: Loaded',data);
        this.nids = data.nids;

        // Init actions.
        this.events();
      };

      Neighbourhood.prototype.events = function() {

        this.$
          .on('show-lpr-neighbourhood', this.invocNeighbour )
          .one('hide-lpr-neighbourhood', this.hide );
      };

      Neighbourhood.prototype.invocNeighbour = function() {

        console.log('Neighbourhood :: invoc neighbour');//,this.called);
        // console.log('this.nids',this.nids);

        var neighbourhood = this;

        if( this.called < 4 ) {
          var nid = this.nids.shift();
          this.currentNeighbour = new Neighbour(nid,this.container);
          this.neighbours.push(this.currentNeighbour);
          this.called ++;

          // attach events on the neighbour.
          this.currentNeighbour.$.on('loaded-lpr-neighbourhood-watch', function(event) { neighbourhood.neighbourLoaded(event); });
          this.currentNeighbour.$.on('hide-lpr-neighbourhood-watch',   function(event) { neighbourhood.neighbourHide(event); });
        }

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

      Neighbourhood.prototype.neighbourLoaded = function(event) {
        console.log('Neighbourhood :: neighbour Loaded');
      };

      Neighbourhood.prototype.neighbourHide = function(event) {
        console.log('Neighbourhood :: neighbour Hide', this.currentNeighbour.nid);
        var neighbourhood = this;
        this.called --;
        clearTimeout(this.timer);
        this.timer = setTimeout(function(){
          // queue the neighbours, when one finish, invoc a new one
          neighbourhood.$.trigger('show-lpr-neighbourhood');
        }, this.currentNeighbour.delay*1000 );
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
    this.delay =     null;
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
        console.log('Neighbour :: Loaded',data);

        // Save datas
        this.html =      data.html;
        this.duration =  data.duration;
        this.mediatype = data.mediatype;
        this.delay =     data.delay;

        // Init actions.
        this.append();
        this.events();

        // When it’s loaded, inform the Neighbourhood.
        this.$.trigger( 'loaded-lpr-neighbourhood-watch', this.nid );
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

              // console.log( 'Neighbour :: iframe =', $(this) );
              // console.log( 'Neighbour :: neighbour.id', neighbour.id );

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

              // start a countdown on load, if the vimeo not playing in the 5s, ask for hidding it.
              neighbour.vimeo.clinicalDeath = setTimeout(function(){
                neighbour.$.trigger('hide-lpr-neighbour');
              },5000);

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

        forceElementInViewport( $('.node',$(this.id)) );

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

        if( neighbour.vimeo.$player ) {
          neighbour.vimeo.$player.removeEvent('pause');
        }

        $(this.id)
          .addClass('hide-lpr')
          .one('bsTransitionEnd', function(event) {
            neighbour.$.trigger('hidden-lpr-neighbour');
          });

        // When it’s hidding, inform the Neighbourhood.
        this.$.trigger( 'hide-lpr-neighbourhood-watch', this.nid );
      };

      Neighbour.prototype.hidden = function(event) {
        console.log('Neighbour :: hidden',this.id);
        $(this.id)
          .addClass('hidden-lpr')
          .remove();
        this.$.off();
      };



      Neighbour.prototype.vimeoStart = function() {
        console.log('Neighbour :: Start vimeo playing',this.id);
        this.vimeo.$player.api("play");
      };

      Neighbour.prototype.vimeoPlay = function(id) {
        console.log("Neighbour :: vimeo ---> [Play]",id);
        // check if a neighbour replay after stoping,
        // cancel the countdown to clinical death.
        clearTimeout(this.vimeo.clinicalDeath);
      }

      Neighbour.prototype.vimeoPause = function(id) {
        console.log("Neighbour :: vimeo ---> [Pause]",id);

        // check if a neighbour stop playing for too long,
        // which is probably not good. In this case, we hide it.
        var neighbour = this;
        this.vimeo.clinicalDeath = setTimeout(function(){
          console.log("Neighbour :: vimeo ---> [clinical death]",id);
          neighbour.$.trigger('hide-lpr-neighbour');
        },5000);
      }

      Neighbour.prototype.vimeoFinish = function(id) {
        console.log("Neighbour :: vimeo ---> [Finish]",id);
        clearTimeout(this.vimeo.clinicalDeath);
      }

      Neighbour.prototype.vimeoPlayProgress = function(data, id) {
        // console.log("Neighbour :: vimeo ---> " + data.seconds + 's played');
        // console.log("Neighbour :: vimeo in vimeoPlayProgress; this = ", this);
        if( (data.duration - data.seconds) < 5 )
          this.$.trigger('hide-lpr-neighbour');
      }

    }// - end prototypes

    this.nodeLoad();

  }// - end Neighbour

  /* =READY
  -----------------------------------------------------------------------------*/
  $(document).ready(init);


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
