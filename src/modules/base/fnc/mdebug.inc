<?php
/*
 * Творец  Ивелин Василев
 * Date : 24.03.2016
 */

// Debug function
function mdebug($income_details = null, $debug_type = null){
	
	if( php_sapi_name() == 'cli' && empty($_SERVER['REMOTE_ADDR']) ) {
	    print_r($income_details);
	    if($debug_type == 'trace'){     print_r(debug_backtrace()); }
	    echo "\n";
	} else {
    	echo "<pre>";print_r($income_details);
	    if($debug_type == 'trace'){     print_r(debug_backtrace()); }
	    echo"</pre>";
	}
}

// Exit after the debug 
function emdebug($income_details = null, $debug_type = null){
	mdebug($income_details, $debug_type);
	exit;
}