<?php
/*
 * Творец  Ивелин Василев
 * 14.11.2013
 */

class baseErrorPage {

  
   function __construct( ) {
   	 
   	// Publish header
   	$about_us_header = new baseTemplater('baseHeader.tpl.inc');
   	$about_us_header->set('page_tite', $GLOBALS['lang']['error_page_title']);
   	$about_us_header->set('page_keywords', $GLOBALS['lang']['error_page_keywords']);
   	$about_us_header->set('page_description', $GLOBALS['lang']['error_page_description']);
   	$about_us_header->set('page_author', $GLOBALS['lang']['base_author']);
   	$about_us_header->publish();
   	
   	// Publish body
   	new baseTemplater('baseErrorPageBody.tpl.inc', 'publish');
   	exit;
   }

}