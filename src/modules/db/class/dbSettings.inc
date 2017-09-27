<?php
/*
 * Creator: Ivelin Vasilev
 * Date: 05.11.2012
 *
*/


class dbSettings {

	private static $PATH_CONFIG_FILE = BASE_CONFIG_FILE;

    // ========  MMPI DB ========
    // Define System section
    private static $DB_SECTION = "db_system";
    // Define System elements
    private static $dbServer   = 'dbServer';
    private static $dbUser     = 'dbUser';
    private static $dbPass     = 'dbPass';
    private static $dbName     = 'dbName';
    private static $dbPort     = 'dbPort';
    private static $dbSocket   = 'dbSocket';

    public static function set_db_section( $income_section = null){
        $db_section = self::$DB_SECTION;
    	if( $income_section ){
    		$db_section = $income_section;
    	}
    	return $db_section;
    } 
    
    // Define System methods
    public static function getDbServer( $income_section = null){
    	
    	$db_section = self::set_db_section($income_section);
		$config = parse_ini_file(self::$PATH_CONFIG_FILE, true);
		$prepareToReturn = isset($config[$db_section][self::$dbServer]) ? $config[$db_section][self::$dbServer] : '';
		
		if(!$prepareToReturn){
			die("<ERROR> DB server empty !\n");
		}
		
		return $prepareToReturn;
		
	}
	
    public static function getDbUser( $income_section = null ){
    	
    	$db_section = self::set_db_section($income_section);
    	
		$config = parse_ini_file(self::$PATH_CONFIG_FILE, true);
		$prepareToReturn = isset($config[$db_section][self::$dbUser]) ? $config[$db_section][self::$dbUser] : '';
		
        if(!$prepareToReturn){
			die("<ERROR> DB user empty !\n");
		}
		
		return $prepareToReturn;
	}
	
    public static function getDbPass( $income_section = null ){
    	
    	$db_section = self::set_db_section($income_section);
    	
		$config = parse_ini_file(self::$PATH_CONFIG_FILE, true);
		$prepareToReturn = isset($config[$db_section][self::$dbPass]) ? $config[$db_section][self::$dbPass] : '';
		
        if(!$prepareToReturn){
			die("<ERROR> DB password empty !\n");
		}
		
		return $prepareToReturn;
	}
	
    public static function getDbName( $income_section = null ){
    	
    	$db_section = self::set_db_section($income_section);
    	
		$config = parse_ini_file(self::$PATH_CONFIG_FILE, true);
		$prepareToReturn = isset($config[$db_section][self::$dbName]) ? $config[$db_section][self::$dbName] : '';
		
        if(!$prepareToReturn){
			die("<ERROR> DB name empty !\n");
		}
		
		return $prepareToReturn;
	}
	
    public static function getDbPort( $income_section = null ){
    	
    	$db_section = self::set_db_section($income_section);
    	
		$config = parse_ini_file(self::$PATH_CONFIG_FILE, true);
		$prepareToReturn = isset($config[$db_section][self::$dbPort]) ? $config[$db_section][self::$dbPort] : '';
		
        if(!$prepareToReturn){
			die("<ERROR> DB port empty !\n");
		}
		
		return $prepareToReturn;
	}
	
    public static function getDbSocket( $income_section = null ){
    	
    	$db_section = self::set_db_section($income_section);
    	
		$config = parse_ini_file(self::$PATH_CONFIG_FILE, true);
		$prepareToReturn = isset($config[$db_section][self::$dbSocket]) ? $config[$db_section][self::$dbSocket] : '';
		
        if(!$prepareToReturn){
			die("<ERROR> DB socket empty !\n");
		}
		
		return $prepareToReturn;
	}

}
