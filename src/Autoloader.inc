<?php
namespace Src;

class Autoloader{

    public static function register(){
    	/* Load under src/class */
    	spl_autoload_register(array(__CLASS__, 'autoloadSrcClass'));
    	/* Load under src/modules */
    	spl_autoload_register(array(__CLASS__, 'kubairLoad'));

    	// Load mdebug function
    	require_once(ROOT.'/src/modules/base/fnc/mdebug.inc');       
    }

    public static function kubairLoad( $getRawClassName ){

    	// Make first letter Capital
    	$class = ucfirst($getRawClassName);
    
    	// exit
    	$exitCode = 0;
    	// Split words in array
    	preg_match_all('/[A-Z][^A-Z]*/', $class, $results);
    
    	if ( isset($results[0]) && isset($results[0][0]) ) {
    		// Make whole string lowercase
    		$moduleName = strtolower($results[0][0]);
    	}
    
    	$location = ROOT."src/modules/$moduleName/class/$getRawClassName.inc";

    	if (file_exists($location)) {
    		require_once($location);
    	}
    
    }
    
    public static function autoloadSrcClass($class){
    	$startFind = ROOT."/src/class";
    	exec('find '.$startFind." -name $class.inc", $output);
    	foreach($output as $getData) {
    	 require_once($getData);
    	}
    }
 }


