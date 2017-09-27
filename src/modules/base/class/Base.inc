<?php

class Base {

  
   function __construct( ) {
   	  	
   }
   
  public static function dbUse( $sqlQuery, $targetDb = null ){
  	
  	   $dbLink = $GLOBALS['localDb'];

  	   if($targetDb){
  	   	$dbLink = $GLOBALS[$targetDb.'Db'];
  	   }

	   $getReturn = $dbLink->dbUse($sqlQuery);
       return ($getReturn);

  }
   
   public static function constructUrl( $get_module = null  ){
		$constructUrl = WEB_ROOT.'/'.$GLOBALS['rest']['language']."/$get_module";
		return ($constructUrl);
   }
	
   public static function getUrl(){
   	$port = !empty($_SERVER['SERVER_PORT']) ? ":".$_SERVER['SERVER_PORT'] : "";
   	$protokol = isset($_SERVER['HTTPS']) ? "https://" : "http://";
   	return $protokol . $_SERVER['SERVER_NAME'] . $port . str_replace('/src', '', WEB_DIR);
   
   }
   
   public static function real_escape_string( $income_raw_string ){
   	global $dbLink;
   	$escaped_string = $dbLink->real_escape_string($income_raw_string);
   	return ($escaped_string);
   
   }
   
   public static function loadBaseTemplates( $getObject = null ){
   
   	$getObject->header = new baseTemplater('baseHeader.tpl.inc');
   	$getObject->sideBar = new baseTemplater('baseSideBar.tpl.inc');
   	$getObject->topNav = new baseTemplater('baseTopNav.tpl.inc');
   	$getObject->footer = new baseTemplater('baseFooter.tpl.inc');
   	$getObject->vendorLibraries = new baseTemplater('baseBottomLibraries.tpl.inc');
   		
   }
   
}