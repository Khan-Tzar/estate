<?php
/*
 * Creator Ivelin Vasilev
 * Date: 05.02.2013
 * @version $Id: ldapApi.inc 5523 2015-10-05 17:12:35Z ivasilev $
 */

class ldapApi {

  private static $instance; //store the single instance of the database
  public  $ldapconnection = '';
  public  $ldapbind = '';
  public  $ldapsearch = '';
  public  $return = false;
  private $ldaphost = '';
  private $ldap_host_failover = '';
  private $ldapport = '';
  private $ldap_opt_protocol_version;
  private $ldapTarget = '';
  private $cuser = '';
  private $cpass = '';
  private $basedn = '';
  private $justthese = '';
  private $filter = '';

  function set_cuser($set_cuser){
  	$this->cpass = $set_cuser;
  }
  
  function set_cpass($set_cpass){
  	$this->cpass = $set_cpass;
  }
  
  function __construct($ldapCredentials = array()){
    $this->ldapTarget = $ldapCredentials['target'];
  	$this->ldaphost = baseSettings::getLdapHost($this->ldapTarget);
  	$this->ldap_host_failover = baseSettings::getLdapHost($this->ldapTarget, 'ldap_host_failover');
  	$this->ldapport = baseSettings::getLdapPort($this->ldapTarget);
  	
  	if(isset($ldapCredentials['user']) && isset($ldapCredentials['pass'])){
  	 $this->cuser = $ldapCredentials['user'];
     $this->cpass = $ldapCredentials['pass'];
  	} else {
  	 $this->cuser = baseSettings::getLdapUser($this->ldapTarget);
     $this->cpass = baseSettings::getLdapPassword($this->ldapTarget);
  	}
    
  }

 public function getGroupMembers( $doByArray = array() ){

   	 $getSearch = $this->ldap_search($doByArray);
   	 $getEntry = ldap_first_entry($this->ldapconnection, $getSearch);
     $getResult = ldap_get_attributes($this->ldapconnection, $getEntry);

     return $getResult;
   }

  function ldap_search( $doByArray = array() ){

  	// Fit filter
  	if ( ! isset($doByArray['filter']) ){
  	   $this->filter = baseSettings::getLdapFilter($this->ldapTarget);
  	} else {
  	   $this->filter = $doByArray['filter'];
  	}

  	// Fit attributes
    if ( ! isset($doByArray['attributes']) ){

  	   $this->justthese = baseSettings::getLdapAttributesl();
  	} else {
  	   $this->justthese = $doByArray['attributes'];
  	}

  	$this->basedn = baseSettings::getLdapBaseDn($this->ldapTarget);

    $this->ldapsearch = ldap_search($this->ldapconnection, $this->basedn, $this->filter , $this->justthese);

    return $this->ldapsearch;
  }

  function setLdapOptions(){

  	$this->ldap_opt_protocol_version = baseSettings::getLdapOption($this->ldapTarget, 'ldap_opt_protocol_version');

  	if($this->ldap_opt_protocol_version) {
  	  // Set ldap_opt_protocol_version
       ldap_set_option($this->ldapconnection, LDAP_OPT_PROTOCOL_VERSION, $this->ldap_opt_protocol_version);
  	}

    $this->ldap_opt_debug_level = baseSettings::getLdapOption($this->ldapTarget, 'ldap_opt_debug_level');

  	if($this->ldap_opt_debug_level) {
  	  // Set ldap_opt_debug_level
       ldap_set_option($this->ldapconnection, LDAP_OPT_DEBUG_LEVEL, $this->ldap_opt_debug_level);
  	}


  }

  function get_ldap(){
  	// Initialize LDAP connection
    $this->ldap_connect();
    if ($this->ldapconnection) {

       // Set LDAP Options
       $this->setLdapOptions();

       // binding to ldap server
       $this->ldap_bind();
       if ($this->ldapbind) {
       	//echo "LDAP bind successful...";
       } else {
       	//echo "LDAP bind failed...";
       	$this->ldap_connect( $this->ldap_host_failover );
       	// Set LDAP Options
       	$this->setLdapOptions();
       	$this->ldap_bind();
       }
       
       // verify binding
       if ($this->ldapbind) {
         //echo "LDAP bind successful...<br />";
         //cliColors::infoColorStatic("\n<INFO> LDAP bind successful... ! \n");
       }
       else {   
         if($this->return){
           return (601);	
         }
         cliColors::errorColorStatic("<ERROR> LDAP bind failed... ! \n");
         exit (601);
       }
      } else {
        if($this->return){
           return (601);	
        }
        exit(600);
      }

  }

  function ldap_bind(){
  	
  	$this->ldapbind = @ldap_bind($this->ldapconnection, $this->cuser, $this->cpass);	
    return $this->ldapbind;
  }

  function ldap_connect( $get_host = null ){
  	
  	$ldaphost = $this->ldaphost;
  	if($get_host){
  		$ldaphost = $get_host;
  	}

  	if ($this->ldapport) {
  	  $this->ldapconnection = ldap_connect($ldaphost, $this->ldapport)  or die("Could not connect to LDAP server.");
  	} else {
  	  $this->ldapconnection = ldap_connect($ldaphost)  or die("Could not connect to LDAP server.");
  	}


    return $this->ldapconnection;
  }

  function getByDistinguishedName( $getDistinguishedName = null ){

  	   // $this->ldapsearch = ldap_search($this->ldapconnection, $this->basedn, $this->filter , $this->justthese);
  	  $ldap_search = ldap_search($this->ldapconnection, $this->basedn, "distinguishedName=".$getDistinguishedName, array('cn', 'mail'));
      $getEntry = ldap_first_entry($this->ldapconnection, $ldap_search);
      if($getEntry == false){
      	
      	echo "False search for distinguishedName=".$getDistinguishedName."\n";
      	return false;
      	
      }
      $entryAttributes = ldap_get_attributes($this->ldapconnection, $getEntry);
      $entry_mail = isset($entryAttributes['mail'][0]) ? strtolower($entryAttributes['mail'][0]) : '';
    return $entry_mail;
  }

  function ldap_get_values_len($getEntryId = null, $getAttribute = null) {

  	$ldap_get_values_len = ldap_get_values_len ($this->ldapconnection, $getEntryId, $getAttribute);

  	$returnValue = bin2hex($ldap_get_values_len[0]);

    return $returnValue;
  }

    // Ensure singleton connection
  public static function getInstance( $ldapCredentials = array() ){
     if(!self::$instance){
        self::$instance = new ldapApi($ldapCredentials);
      }
     return self::$instance;
  }

}
