<?php
/*
 * Творец  Ивелин Василев
 * 21.12.2015
 * 
 *  WEB_DIR/bg/ajax/   // <== constatna za backend 
 *  http://kardam.codixfr.private:8681/extranet_mmpi_iiva/bg/ajax/get-project-chains/52
 */

class baseAjaxController{

 function __construct( ) {
    
  switch($GLOBALS['rest']['rest_sub_module']){
  	//for pr info
  	case "get-submited-prinfo":
  		new issueAjaxController();
  		exit;
  		break;
  	// Make delivery chains drop down all/by project_id
  	case "get-project-chains":
  		$deliverychainsController = new deliverychainsController(); 
  		$deliverychainsController->makeDeliveryChainsDropDown($GLOBALS['rest']['rest_arguments']['get-project-chains']);
  		//mdebug($deliverychainsController);
    break;
    // Make list of instances all/by delivery chain
    case "get-dchains-instances":
    	$instancesController = new instancesController();
    	$instancesController->makeInstancesTableColumns($GLOBALS['rest']['rest_arguments']['get-dchains-instances']);
    break;
    default:
  }
  	
 } 
 
}

