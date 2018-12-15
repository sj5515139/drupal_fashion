<?php 

/**
 * Page alter.
 */
function bizreview_page_alter($page) {
	$mobileoptimized = array(
		'#type' => 'html_tag',
		'#tag' => 'meta',
		'#attributes' => array(
		'name' =>  'MobileOptimized',
		'content' =>  'width'
		)
	);
	$handheldfriendly = array(
		'#type' => 'html_tag',
		'#tag' => 'meta',
		'#attributes' => array(
		'name' =>  'HandheldFriendly',
		'content' =>  'true'
		)
	);
	$viewport = array(
		'#type' => 'html_tag',
		'#tag' => 'meta',
		'#attributes' => array(
		'name' =>  'viewport',
		'content' =>  'width=device-width, initial-scale=1'
		)
	);
	drupal_add_html_head($mobileoptimized, 'MobileOptimized');
	drupal_add_html_head($handheldfriendly, 'HandheldFriendly');
	drupal_add_html_head($viewport, 'viewport');
}

/**
 * Preprocess variables for html.tpl.php
 */
function bizreview_preprocess_html(&$variables) {
  /* Color */
  $file = 'color-' . theme_get_setting('theme_color') . '-style.css';
  drupal_add_css(path_to_theme() . '/css/'. $file, array('group' => CSS_THEME, 'weight' => 115,'browsers' => array(), 'preprocess' => FALSE));
	/**
	 * Add IE8 Support
	 */
	drupal_add_css(path_to_theme() . '/css/ie8.css', array('group' => CSS_THEME, 'browsers' => array('IE' => '(lt IE 9)', '!IE' => FALSE), 'preprocess' => FALSE));
	
	/**
	* Add Javascript for enable/disable Bootstrap 3 Javascript
	*/
	if (theme_get_setting('bootstrap_js_include', 'bizreview')) {
	drupal_add_js(drupal_get_path('theme', 'bizreview') . '/bootstrap/js/bootstrap.min.js');
	}
	//EOF:Javascript
	
	
	/**
	* Add Javascript for enable/disable scrollTop action
	*/
	if (theme_get_setting('scrolltop_display', 'bizreview')) {

		drupal_add_js('jQuery(document).ready(function($) { 
			$(window).scroll(function() {
				if($(this).scrollTop() != 0) {
					$("#toTop").fadeIn();	
				} else {
					$("#toTop").fadeOut();
				}
			});
		});',
		array('type' => 'inline', 'scope' => 'header'));
	}
	
	
	drupal_add_js('jQuery(document).ready(function($) { 
		
		//JS for changing add to cart button text..........
		$(".commerce-add-to-cart .form-submit").text("Book Now").button("refresh");
		
		//JS for Clicking div in models tab in homepage
		$(".model-image .title").click(function() {
		  window.location = $(this).find("a").attr("href"); 
		  return false;
		});
		
		// JS for Adding images in tabs on homepage
	   	$( ".quicktabs-tabs li a" ).each(function() {
		  	var a = $(this).text();
		  	if(a.includes("Female")){
		  		var f_img = "<img src=sites/default/files/Female%20icon%20%281%29.png style=height:120px;margin-right:50px;></img><span style=display:none>Female</span>";
		  		$(this).html(f_img);
		  	}else{
			  	var m_img = "<img src=sites/default/files/Male%20icon%20%281%29.png style=height:120px;margin-right:30px;></img><span style=display:none>Male</span>";
			  	$(this).html(m_img);
			  	//$("#page").css("background", "red");
		  	}
		});
		
		// JS for changing background in tabs on homepage
		$(".quicktabs-tabs li a").click(function() {
			var a = $(this).text();
			if(a.includes("Female")){
				$("#page").css("background", "linear-gradient(135deg, #e85663e8, rgb(253, 224, 218))");
			}else{
				$("#page").css("background", "linear-gradient(135deg, rgb(0, 168, 127), rgb(185, 217, 127))");
			}
		});
		
		//JS for changing the date on add to cart form.
		$("#edit-quantity").prop("readonly", "readonly"); 
		$(".jcarousel-item").hover(function () {
			//alert("ddf");
			var From_date = new Date($(this).find(".start-date-wrapper .date-clear").val());
			var To_date = new Date($(this).find(".end-date-wrapper .date-clear").val());
			var diff_date =  To_date - From_date;
			 
			var days = diff_date/1000/60/60/24;
			$(this).find("#edit-quantity").val(days+1);
			$(this).find("#edit-quantity").click();
		});
		
		$("#toTop").click(function() {
			$("body,html").animate({scrollTop:0},800);
		});
		
		
		});',
		array('type' => 'inline', 'scope' => 'header'));
	//EOF:Javascript
	
	global $user;
	if($user->uid == 0){
		// JS for Auto Populate Div Start 
		drupal_add_library('system', 'jquery.cookie');
		drupal_add_js('jQuery(document).ready(function($) {
			var visited = readCookie("popup-visited");
			if(visited != "yes"){
				//setInterval(function() {
				//		$("#auto-popup").toggle();
				//		$("#auto-popup").focus();
				//}, 40000);
				
				//$("#auto-popup").show();
				
				setTimeout(function(){
                    $("#auto-popup").show();
                },40000);
			}
		});',
		array('type' => 'inline', 'scope' => 'header'));
	}
	
	//Js for changing placeholder of newsletter textbox.....................
	drupal_add_js('jQuery(document).ready(function($) {		
	    $(".simplenews-subscribe .form-item-mail input").attr("placeholder", "Enter Your Email");
	});',
	array('type' => 'inline', 'scope' => 'header'));
}

/**
 * Override or insert variables into the html template.
 */
function bizreview_process_html(&$vars) {
	// Hook into color.module
	if (module_exists('color')) {
	_color_html_alter($vars);
	}
}

/**
 * Preprocess variables for page template.
 */
function bizreview_preprocess_page(&$vars) {
	//$path = cuurent_path();
	$path = request_uri();
	//$path = request_path();
	global $user;
	/**
	 * insert variables into page template.
	 */
	if($vars['page']['sidebar_first'] && $vars['page']['sidebar_second']) { 
		$vars['sidebar_first_grid_class'] = 'col-md-2';
		$vars['sidebar_second_grid_class'] = 'col-md-3';
		$vars['main_grid_class'] = 'col-md-7';
	} elseif ($vars['page']['sidebar_first'] && !($vars['page']['sidebar_second'])) {
		$vars['sidebar_first_grid_class'] = 'col-md-3';
		$vars['main_grid_class'] = 'col-md-9';
	} elseif (!($vars['page']['sidebar_first']) && $vars['page']['sidebar_second']) {
		$vars['sidebar_second_grid_class'] = 'col-md-4';
		$vars['main_grid_class'] = 'col-md-8';			
	} else {
		$vars['main_grid_class'] = 'col-md-12';			
	}

	if($vars['page']['header_top_left'] && $vars['page']['header_top_right']) { 
		$vars['header_top_left_grid_class'] = 'col-md-6';
		$vars['header_top_right_grid_class'] = 'col-md-6';
	} elseif ($vars['page']['header_top_right'] || $vars['page']['header_top_left']) {
		$vars['header_top_left_grid_class'] = 'col-md-12';
		$vars['header_top_right_grid_class'] = 'col-md-12';		
	}

	if($vars['page']['preface_first'] && $vars['page']['preface_second']) { 
		$vars['preface_first_grid_class'] = 'col-md-9';
		$vars['preface_second_grid_class'] = 'col-md-3';
	} elseif ($vars['page']['preface_second'] || $vars['page']['preface_first']) {
		$vars['preface_first_grid_class'] = 'col-md-12';
		$vars['preface_second_grid_class'] = 'col-md-12';		
	}

	if($vars['page']['main_navigation'] && $vars['page']['sub_navigation']) { 
		$vars['main_navigation_grid_class'] = 'col-md-3';
		$vars['sub_navigation_grid_class'] = 'col-md-7';
	} else {
		$vars['main_navigation_grid_class'] = 'col-md-10';
		$vars['sub_navigation_grid_class'] = 'col-md-10';		
	}
	
	
	//Redirecting unlogged user to login page............
	// if(strpos($path, 'business-listing') == TRUE){
		// if(!in_array('authenticated user', $user->roles)){
			// drupal_goto('user/login');
		// }
	// }
	
}

/**
 * Override or insert variables into the page template.
 */
function bizreview_process_page(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
}

/**
 * Preprocess variables for block.tpl.php
 */
function bizreview_preprocess_block(&$variables) {
	$variables['classes_array'][]='clearfix';
}

/**
 * Add placeholder text to the search form

function bizreview_form_alter(&$form, &$form_state, $form_id){
  if($form_id == "views_exposed_form"){
    if (isset($form["search_api_views_fulltext"])) {
            $form["search_api_views_fulltext"]['#attributes'] = array('placeholder' => array(t('What are you looking for?')));
    }
  }
}
 */
