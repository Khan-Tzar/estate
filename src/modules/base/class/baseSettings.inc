<?php
/*
 * Creator: Ivelin Vasilev
 * update: Ana Bozhilova
 * Date: 06.08.2015
 *
*/

class baseSettings {

	// Conf file location
	private static $BASE_CONFIG_FILE = BASE_CONFIG_FILE;
	// Section
    private static $GLOBAL = 'global';
    // Entities under sections
    private static $web_root = 'web_root';
     // Global
    public static function getWebRoot(){
    	$config = parse_ini_file(self::$BASE_CONFIG_FILE, true);
    	$prepareToReturn = isset($config[self::$GLOBAL][self::$web_root]) ? $config[self::$GLOBAL][self::$web_root] : '';
    	return $prepareToReturn;
    }
    
    public static function getConfiguration( $section = 'global'  ){
    	$config = parse_ini_file(self::$BASE_CONFIG_FILE, true);
    	$prepareToReturn = isset($config[$section]) ? $config[$section] : '';
    	return $prepareToReturn;
    }
    
    // ========  LDAP  ========
    private static $LDAP = "ldap";
    // Define System elements
    private static $ldap_user = "ldap_user";
    private static $ldap_password = "ldap_password";
    private static $ldap_host = "ldap_host";
    private static $ldap_port = "ldap_port";
    private static $ldap_base_dn = "ldap_base_dn";
    private static $ldap_attributes = "ldap_attributes";
    private static $ldap_filter = "ldap_filter";
    
    public static function getLdapUser( $ldapTarget = null ){
    	$config = parse_ini_file(self::$BASE_CONFIG_FILE, true);
    	$ldapTarget = $config[self::$LDAP][$ldapTarget][self::$ldap_user];
    	$prepareToReturn = isset($ldapTarget) ? $ldapTarget : '';
    	// Remove trailing white spaces
    	$prepareToReturn = trim($prepareToReturn);
    	return $prepareToReturn;
    }
    
    public static function getLdapPassword( $ldapTarget = null ){
    	$config = parse_ini_file(self::$BASE_CONFIG_FILE, true);
    	$ldapTarget = $config[self::$LDAP][$ldapTarget][self::$ldap_password];
    	$prepareToReturn = isset($ldapTarget) ? $ldapTarget : '';
    	// Remove trailing white spaces
    	$prepareToReturn = trim($prepareToReturn);
    	return $prepareToReturn;
    }
    
    public static function getLdapHost( $ldapTarget = null, $get_option = null ){
    
    	$which_entity = self::$ldap_host;
    	if($get_option){
    		$which_entity = $get_option;
    	}
    	$config = parse_ini_file(self::$BASE_CONFIG_FILE, true);
    	$ldapTarget = $config[self::$LDAP][$ldapTarget][$which_entity];
    	$prepareToReturn = isset($ldapTarget) ? $ldapTarget : '';
    	// Remove trailing white spaces
    	$prepareToReturn = trim($prepareToReturn);
    	return $prepareToReturn;
    }
    
    public static function getLdapPort( $ldapTarget = null ){
    	$config = parse_ini_file(self::$BASE_CONFIG_FILE, true);
    	$ldapTarget = $config[self::$LDAP][$ldapTarget][self::$ldap_port];
    	$prepareToReturn = isset($ldapTarget) ? $ldapTarget : '';
    	// Remove trailing white spaces
    	$prepareToReturn = trim($prepareToReturn);
    	return $prepareToReturn;
    }
    
    public static function getLdapBaseDn( $ldapTarget = null ){
    	$config = parse_ini_file(self::$BASE_CONFIG_FILE, true);
    	$ldapTarget = $config[self::$LDAP][$ldapTarget][self::$ldap_base_dn];
    	$prepareToReturn = isset($ldapTarget) ? $ldapTarget : '';
    	// Remove trailing white spaces
    	$prepareToReturn = trim($prepareToReturn);
    	return $prepareToReturn;
    }
    
    public static function getLdapAttributesl( $getEntity = null ){
    	$config = parse_ini_file(self::$BASE_CONFIG_FILE, true);
    	$prepareToReturn = isset($config[self::$LDAP][self::$ldap_attributes]) ? $config[self::$LDAP][self::$ldap_attributes] : '';
    
    	if ( $getEntity != null ){
    		return $prepareToReturn[$getEntity];
    	}
    	return $prepareToReturn;
    }
    
    public static function getLdapFilter( $ldapTarget = null ){
    	$config = parse_ini_file(self::$BASE_CONFIG_FILE, true);
    	$ldapTarget = $config[self::$LDAP][$ldapTarget][self::$ldap_filter];
    	$prepareToReturn = isset($ldapTarget) ? $ldapTarget : '';
    	// Remove trailing white spaces
    	$prepareToReturn = trim($prepareToReturn);
    	return $prepareToReturn;
    }
    
    public static function getLdapOption( $ldapTarget = null, $getOption = null ){
    	$config = parse_ini_file(self::$BASE_CONFIG_FILE, true);
    	$ldapTarget = $config[self::$LDAP][$ldapTarget];
    	$prepareToReturn = isset($ldapTarget) ? $ldapTarget : '';
    	// Remove trailing white spaces
    	$prepareToReturn = trim($prepareToReturn[$getOption]);
    	return $prepareToReturn;
    }
}
