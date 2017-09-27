<?php
/*
 *    Framework: Fanagoria
 *   Start time: 25.09.2017
 */

class HomeController {
	
	
	function __construct( ) {
		
		$baseBody = new baseTemplater('homeBody.tpl.inc');
		Base::loadBaseTemplates($baseBody);
		$baseBody->publish();
		
	}
	
}