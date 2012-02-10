/**
 * Implementation of Drupal behavior.
 */
(function($) {

Drupal.behaviors.guibik = {};
Drupal.behaviors.guibik.attach = function(context) {

	$('form.form-edit', '.views-edit-view').each(function(index) {
		var $this = $(this),
				_alt = false,
				_submit = function(event){
					// console.log('_submit');
					event.preventDefault();
					$('input[type=submit]#edit-actions-save', $this).focus();
					$this.submit();
					return false;
				};
		
		$(document).bind({
			keydown: function(event) {
				// console.log('keydown', event);
				switch(event.keyCode){
					case 18:
						_alt = true;
					break;
					case 83: // s
						if(_alt)
							return _submit(event);
				}
			},
			keyup: function(event) {
				// console.log('keyup', event);
				switch(event.keyCode){
					case 18:
						_alt = false;
					break;
				}
			
			}
		});

		// $(document).keydown(function(event){
		// 	console.log(event);			
		// });

		
		
	});


};

Drupal.behaviors.init_theme = {};
Drupal.behaviors.init_theme.attach = function (context) {

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


})(jQuery);
