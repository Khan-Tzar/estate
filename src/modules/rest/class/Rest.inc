<?php
/*
 * 
 * Framework Fanagoria
 * Творец  Ивелин Василев
 * Date: 2017.09.25
*/
class Rest   {
  
  public static function checkLanguage(){

  	switch($GLOBALS['rest'][0]){
  	  case "fr":
  	  case "de":
  	  case "ru":
  	  case "cn":
  	  case "es":
  	  case "bg":
  	  case "en":
  	  	$GLOBALS['rest']['language'] = $GLOBALS['rest'][0];
  		$_SESSION['language'] = $GLOBALS['rest']['language'];
  		return;
  	    break;
  	}
  	
  	$lang_abrev = '';
  	
  	if(isset($_REQUEST['language']) && ($_REQUEST['language'] == "fr" ||
  			$_REQUEST['language'] == "es" ||
  			$_REQUEST['language'] == "de" ||
  			$_REQUEST['language'] == "ru" ||
  			$_REQUEST['language'] == "bg" ||
  			$_REQUEST['language'] == "en")){
  		$lang_abrev = $_REQUEST['language'];
  	}
  	elseif(isset($_SESSION['language']) && !isset($_REQUEST['language'])){
  		$lang_abrev = $_SESSION['language'];
  	}else{
  		$langs = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'], 0, 2);
  	    switch($langs){
  	    	case "fr":
  	    	case "de":
  	    	case "ru":
  	    	case "cn":
  	    	case "es":
  	        case "bg":
  	    	  $lang_abrev = $langs;
  	    	 break;
  	    	default:
  	    	  $lang_abrev = 'en';
  	    }
  	    $_SESSION['language'] = $lang_abrev;
  		$GLOBALS['rest']['language'] = $lang_abrev;
  	}
  	
  	$_SESSION['language'] = $lang_abrev;
  	$GLOBALS['rest']['language'] = $lang_abrev;
  	
  }
  
  public static function getArguments( $request_uri = array() ){
  	// Подаваме масива от УРЛ-то за да изрежем всичко до модула а модула е дефиниран тука REST_INDEX_MODULE
  	$arguments_raw_array = array();
  	// Remove elements up to the module REST_INDEX_MODULE
  	foreach ( $request_uri as $key => $value ){
  		if( $key <= REST_INDEX_MODULE ){
  			continue;
  		}else {
  			$arguments_raw_array[] = $value;
  		}
  	}
  	 
  	return $arguments_raw_array;
  }
  
  public static function макеArgumentsInAssociativeArray( $arguments_raw_array = array() ){
  	 
  	$arguments_array = array();
  	//mdebug($request_uri);exit;
  	foreach ( $arguments_raw_array as $key => $value ){
  		// Check odd and even
  		$odd_even = $key % 2;
  		if ( $odd_even == 0 ) {
  			//echo "Firs<br>";
  			if( isset($arguments_raw_array[$key+1])){
  				//echo "Second<br>";
  				$arguments_array[$value] = urldecode($arguments_raw_array[$key+1]);
  			}
  		}
  	}
  	 
  	return $arguments_array;
  }
  
  public static function splitRest(){
  
  	// REST URL
  	$request_uri = '';
  	$_SERVER['REQUEST_URI']=str_replace(';', '', $_SERVER['REQUEST_URI']);
  	$_SERVER['REQUEST_URI']=trim($_SERVER['REQUEST_URI']);
  	$raw_request_uri = str_replace(URL_SUFFIX_DIR, '', $_SERVER['REQUEST_URI']);
  
  	$request_uri = str_replace('?'.$_SERVER['QUERY_STRING'], '', $raw_request_uri);
  
  	// Премахване на излишните наклонени черти.
  	$request_uri_string = trim($request_uri,'/');
  	$request_uri = explode('/', $request_uri_string);
  	 
  	// Подаваме масива от УРЛ-то за да изрежем всичко до модула а модула е дефиниран тука REST_INDEX_MODULE
  	$arguments_raw_array = rest::getArguments($request_uri);
  	 
  	$arguments_array = rest::макеArgumentsInAssociativeArray($arguments_raw_array);
  	 
  	$request_uri['rest_module'] = isset($request_uri[REST_INDEX_MODULE])?$request_uri[REST_INDEX_MODULE]:'';
  	$request_uri['rest_module'] = urldecode($request_uri['rest_module']);
  
  	$request_uri['rest_sub_module'] = isset($request_uri[REST_INDEX_MODULE+1])?$request_uri[REST_INDEX_MODULE+1]:'';
  	$request_uri['rest_sub_module'] = urldecode($request_uri['rest_sub_module']);
  	$request_uri['rest_arguments'] = $arguments_array;
  	$request_uri['uri_string'] = $request_uri_string;
  	$GLOBALS['rest'] = $request_uri;
  
  }

}