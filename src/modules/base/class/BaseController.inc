<?php
/*
 * Framework Fanagoria
 * Творец  Ивелин Василев
 * Start date: 24.02.2017
 */

class BaseController{

 function __construct( ) {

   $GLOBALS['rest']['browser'] = new GetBrowser;
   $GLOBALS['rest']['browser']->storeDetectedDevice();

   switch($GLOBALS['rest']['rest_module']){
   	case "information":
   		new InformationController();
   		exit;
   		break;
   	case "home":
   		new HomeController();
   		  exit;
   		break;
       default:
        // if($GLOBALS['rest']['rest_module']){
   		 //  new baseErrorPage();
   		 //  exit;
   	     //}
   	    new HomeController();
   }
  	
 }
  
}

