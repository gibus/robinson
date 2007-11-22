// $Id$

$(document).ready(function() {
  // get the Drupal basepath
  var basePath = Drupal.settings.simplemenu.basePath;
  // get the element to add the menu to
  var element = Drupal.settings.simplemenu.element;                        
  var menu = '<ul id="simplemenu" class="clear-block"></ul>';
  
  switch (Drupal.settings.simplemenu.placement) {
    case 'prepend':
      $(menu).prependTo(element);
      break;
    case 'append':
      $(menu).appendTo(element);
      break;
    case 'replace':
      $(element).html(menu);
      break;
  }  
  
  $('body').css('margin-top', '20px');
  
  // Build menu        
  $('#simplemenu')
    .append(simplemenu)
    .superfish()
    .find(">li[ul]")
  		.mouseover(function(){
  			$("ul", this).bgiframe({opacity:false});  
  		})
  		.find("a")
  			.focus(function(){
  				$("ul", $("#simplemenu>li[ul]")).bgiframe({opacity:false});
  			});
	 
	 $('#simplemenu').children('li.expanded').addClass('root');    
});           


/*
 * Superfish v1.3.2 - jQuery menu widget
 *
 * Copyright (c) 2007 Joel Birch
 *
 * Dual licensed under the MIT and GPL licenses:
 * 	http://www.opensource.org/licenses/mit-license.php
 * 	http://www.gnu.org/licenses/gpl.html
 *
 * YOU SHOULD DELETE THIS CHANGELOG TO REDUCE FILE SIZE:
 * v1.2.1 altered:  2nd July 07. added hide() before animate to make work for jQuery 1.1.3. See comment in 'over' function.
 * v1.2.2 altered:  2nd August 07. changed over function .find('ul') to .find('>ul') for smoother animations
 * 				    Also deleted the iframe removal lines - not necessary it turns out
 * v1.2.3 altered:  jquery 1.1.3.1 broke keyboard access - had to change quite a few things and set display:none on the
 *				    .superfish rule in CSS instead of top:-999em
 * v1.3	: 		    Pretty much a complete overhaul to make all original features work in 1.1.3.1 and above.
 *				    .superfish rule reverted back to top:-999em (which is better).
 * v1.3.1 altered:  'li[ul]' to $('li:has(ul)') to work with jQuery 1.2
 * v1.3.2: 			added onshow callback option. 'this' keyword refers to revealed ul.
		   			fixed bug whereby multiple menus on a page shared options. Now each menu can have separate options.
					fixed IE6 and IE7 bug whereby under certain circumstances => 3rd tier menus appear instantly with text missing when revisited
 */

(function($){
	$.fn.superfish = function(o){
		var $sf = this,
			defaults = {
			hoverClass	: 'sfHover',
			pathClass	: 'overideThisToUse',
			delay		: 800,
			animation	: {opacity:'show'},
			speed		: 'normal',
			onshow		: function(){} // in your function, 'this' is the revealed ul
		},
			over = function(){
				clearTimeout(this.sfTimer);
				$(this)
				.showSuperfishUl(o)
				.siblings()
				.hideSuperfishUl(o);
			},
			out = function(){
				var $$ = $(this);
				if ( !$$.is('.'+o.bcClass) ) {
					this.sfTimer=setTimeout(function(){
						$$.hideSuperfishUl(o);
						var sf = $$.parents('ul.superfish:first')[0];
						if (!$('.'+o.hoverClass,sf).length) {
							over.call(sf.o.$currents.hideSuperfishUl(o));
						}
					},o.delay);
				}		
			};
		$.fn.extend({
			hideSuperfishUl : function(o){
				return this
					.removeClass(o.hoverClass)
					.find('ul')
						.hide()
						.css('visibility','hidden')
					.end();
			},
			showSuperfishUl : function(o){
				return this
					.addClass(o.hoverClass)
					.find('>ul:hidden')
						.css('visibility','visible')
						.animate(o.animation,o.speed,function(){
							o.onshow.call(this);
						})
					.end();
			},
			applySuperfishHovers : function(){
				return this[($.fn.hoverIntent) ? 'hoverIntent' : 'hover'](over,out);
			}
		});
		
		return this
			.addClass('superfish')
			.each(function(){
				o = $.extend({bcClass:'sfbreadcrumb'},defaults,o || {});
				o = $.extend(o,{$currents:$('li.'+o.pathClass+':has(ul)',this)});
				this.o = o;
				if (o.$currents.length) {
					o.$currents.each(function(){
						$(this).removeClass(o.pathClass).addClass(o.hoverClass+' '+o.bcClass);
					});
				}
				
				var $sfHovAr=$('li:has(ul)',this)
					.applySuperfishHovers(over,out)
					.find('a').each(function(){
						var $a = $(this), $li = $a.parents('li');
						$a.focus(function(){
							over.call($li);
							return false;
						}).blur(function(){
							out.call(this);
							$li.removeClass(o.hoverClass);
							return false;
						});
					})
					.end()
					.not('.'+o.bcClass)
						.hideSuperfishUl(o)
					.end();
				
				$(window).unload(function(){
					$sfHovAr.unbind('mouseover').unbind('mouseout');
					$('ul.superfish').each(function(){
						this.o = this.o.$currents = null; // clean up
					});
				});
			});
	};
})(jQuery);


/* Copyright (c) 2006 Brandon Aaron (http://brandonaaron.net)
 * Dual licensed under the MIT (http://www.opensource.org/licenses/mit-license.php) 
 * and GPL (http://www.opensource.org/licenses/gpl-license.php) licenses.
 *
 * $LastChangedDate: 2007-07-21 18:45:56 -0500 (Sat, 21 Jul 2007) $
 * $Rev: 2447 $
 *
 * Version 2.1.1
 */
(function($){$.fn.bgIframe=$.fn.bgiframe=function(s){if($.browser.msie&&/6.0/.test(navigator.userAgent)){s=$.extend({top:'auto',left:'auto',width:'auto',height:'auto',opacity:true,src:'javascript:false;'},s||{});var prop=function(n){return n&&n.constructor==Number?n+'px':n;},html='<iframe class="bgiframe"frameborder="0"tabindex="-1"src="'+s.src+'"'+'style="display:block;position:absolute;z-index:-1;'+(s.opacity!==false?'filter:Alpha(Opacity=\'0\');':'')+'top:'+(s.top=='auto'?'expression(((parseInt(this.parentNode.currentStyle.borderTopWidth)||0)*-1)+\'px\')':prop(s.top))+';'+'left:'+(s.left=='auto'?'expression(((parseInt(this.parentNode.currentStyle.borderLeftWidth)||0)*-1)+\'px\')':prop(s.left))+';'+'width:'+(s.width=='auto'?'expression(this.parentNode.offsetWidth+\'px\')':prop(s.width))+';'+'height:'+(s.height=='auto'?'expression(this.parentNode.offsetHeight+\'px\')':prop(s.height))+';'+'"/>';return this.each(function(){if($('> iframe.bgiframe',this).length==0)this.insertBefore(document.createElement(html),this.firstChild);});}return this;};})(jQuery);