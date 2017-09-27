<?php
/*
 * Творец  Ивелин Василев
 * 11.11.2015
 */

class language     {

	public static function lng_bar(  ){
		$language_bar = new baseTemplater('languageBar.tpl.inc', 'publish');
	}
	
	public static function createLangBar(){
		$getLangQuery = "select lang from language where lng_status = 'enabled'";
		$getLang = base::dbUse($getLangQuery);
	
		foreach ($getLang as $key => $value) {
	
			$_SESSION['language'] = isset($_SESSION['language']) ? $_SESSION['language'] : 'fr';
	
			if( $_SESSION['language'] == $value['lang'] ){
				print "<a class=\"{$value['lang']}N\">{$value['lang']}</a> ";
			} else {
				
				// Remove current language and switch it to the new one.
				$get_uri_string = ltrim($GLOBALS['rest']['uri_string'], $GLOBALS['rest'][0]);
				$get_uri_string = ltrim($get_uri_string, '/');
				//print "<a href=\"?language={$value['lang']}\" class=\"{$value['lang']}A\">{$value['lang']}</a> ";
				$construct_url = WEB_ROOT.'/'.$value['lang']."/$get_uri_string";
				
				print "<a href='$construct_url' class=\"{$value['lang']}A\">{$value['lang']}</a> ";
				//print_r($construct_url); echo "<br>";
			}
		}
	}

}