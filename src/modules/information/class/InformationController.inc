<?php
/*
 * Framework: Fanagoria
 * Start date: 2017.09.25
 * 
 */


class InformationController{

	function __construct( ) {
		
		//mdebug($GLOBALS['rest']['rest_sub_module']);
	  switch($GLOBALS['rest']['rest_sub_module']){
	    case "name-location":
		    $this->informationNameLocation();
		  break;
		case "company-history":
		  	$this->informationHistoryOfCompany();
		  break;
		case "company-background":
		  	$this->informationCompanyBackground();
		  break;
      default:
    }
	 
	}
	
	
	public function informationNameLocation(){
		$baseBody = new baseTemplater('informationBody.tpl.inc');
		Base::loadBaseTemplates($baseBody);
		$baseBody->publish();
	}  
	public function informationHistoryOfCompany(){
	  	base::header();
	  new baseTemplater('informationHistoryOfCompany.tpl.inc', 'publish');
	}
	
	public function informationCompanyBackground(){
		base::header();
		new baseTemplater('informationCompanyBackground.tpl.inc', 'publish');
	}
	
}