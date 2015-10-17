/**
 * В этом файле описан функционал, который добавляет панель в правую часть сайта, которая позволяет промотать экран вверх.
 */


$(function() {

	var to_top_button = $('<div class="to_top" ><div class="to_top_panel" title="Наверх"><div class="to_top_button"><span class="arrow">&uarr;</span> <span class="label">наверх</span></div></div></div>')	
		
	$('body').append(to_top_button);
	
	$('.to_top_panel', to_top_button).click(function(){
		$.scrollTo( $('body') , 500,  { axis: 'y' } );
	})
	
	var show = false
	$(window).scroll(function () { 

		if( this.pageYOffset > 400){
			if(!show){
				to_top_button.show()
				show = true
			}
		}else{
			if(show){
				to_top_button.hide()
				show = false
			}
		}
	})
	
	function mini_or_normal_width(){
		if( $(window).width() < 1330 ){ // если экран маленький - показываем мини панель
			to_top_button.addClass('mini')
		}else{                          // если экран нормальный - показываем нормальную панель
			to_top_button.removeClass('mini')
		}
	}
	
	$(window).resize(function() {
  	mini_or_normal_width()
	});
	
	mini_or_normal_width()
	
});