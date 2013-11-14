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

  var _cell_w = 341, _cell_h = 256;
  var _$stream_wrapper = $('<div>').attr('id','stream-wrapper').appendTo('#main');
  var _displayed_themas = [];

  function init(){
    loadThema();
  };

  function loadThema(){
    $.getJSON(Drupal.settings.basePath+Drupal.settings.pathPrefix+'ajax/robinson/thema', 
      // {'types':types,'current_path':document.location.href, 'keys':keys, 'searchmode':searchmode},
      function(json){
        // trace('json', json);
        // console.log('json', json);
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

    listenThemaVideo('#thema-'+thema_id);
  };

  // https://vimeo.com/forums/topic:37800
  // http://jsfiddle.net/bdougherty/UTt2K/
  // http://kevinchevallier.com/vimeo-froogaloop-ajax/
  // http://juanfra.me/2012/08/flexslider-multiple-videos-v2/
  // http://mikeheavers.com/main/code-item/a_simpler_vimeo_froogaloop_javascript_api_example
  // https://developer.vimeo.com/player/js-api#universal-with-postmessage
  // http://player.vimeo.com/playground

  function listenThemaVideo(thema_id){
    var $vimeoIframe = $('iframe', thema_id);

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

      console.log('onMessageReceived | e', data.event);

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

  // Helper function for sending a message to the player
  function post($vimeoIframe, action, value) {
      console.log('post | action : '+action+' | value : '+value);
      var  url = $vimeoIframe.attr('src').split('?')[0];
      var data = { method: action };
      
      if (value) {
          data.value = value;
      }
      
      console.log('url = '+url);
      console.log('data', data);

      var jsoned = JSON.stringify(data);
      console.log('jsoned', jsoned);
      console.log('$vimeoIframe', $vimeoIframe);

      $vimeoIframe[0].contentWindow.postMessage(jsoned, url);
  };

  function onVideoIsReady($vimeoIframe){
    console.log('onVideoIsReady', $vimeoIframe);
    // post('addEventListener', 'pause');
    post($vimeoIframe, 'addEventListener', 'finish');
    post($vimeoIframe, 'addEventListener', 'playProgress');
    post($vimeoIframe, 'play');
  };

  function onVideoFinish($vimeoIframe){
    console.log('onVideoFinish', $vimeoIframe);
    post($vimeoIframe, 'unload');
  };

  function onVideoPlayProgress($vimeoIframe, data){
    console.log('onVideoPlayProgress | data = ', data);
  };






  function setupGrid(){

  };


  /**
  * ready
  */
  $(document).ready(function() {
    init();
  });


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
  }


})(jQuery);
