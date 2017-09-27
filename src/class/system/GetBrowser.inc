<?php
/*
 *      Създател:  Ивелин Василев
 *   Наричан още:  Kан-Цар
 * Лето господне:  06.11.2013
 *
 */

class GetBrowser {
	public $Name;
	public $Version;

	public $device_deatils = array(
    'UA'              => '',
    'BROWSER_NAME'    => 'Unknown',
    'BROWSER_VER'     => '0',
    'BROWSER_SHORT'   => 'UNK',
    'DEVICE_OS'       => 'Unknown',
    'DEVICE_CATEGORY' => 'Unknown',
    'LAYOUT_ENGINE'   => 'Unknown',
    'BOT'             => 'Unknown',
	'SERVER_PROTOCOL' => 'Unknown',
	'REQUEST_URI'     => 'Unknown',
	'HTTP_HOST'       => 'Unknown'
  ) ;
	
	/*
    private $props = array("Version" => "0.0.0",
                                "Name" => "unknown",
                                "Agent" => "unknown",
                                "AllowsHeaderRedirect" => true) ;
                                */

    public function __Construct() {

    	// Load external library
    	include_once(ENV_HOME.'/extlib/devicedetection/DeviceDetection.php');
       
        $DeviceDetection = new DeviceDetection('detect');

        $this->device_deatils =  $DeviceDetection->v;

        $this->device_deatils['HTTP_HOST'] = $_SERVER['HTTP_HOST'];
        $this->device_deatils['REQUEST_URI'] = $_SERVER['REQUEST_URI'];
        $this->device_deatils['SERVER_PROTOCOL'] = $_SERVER['SERVER_PROTOCOL'];
        
       
                
        return $this->device_deatils;

    }

    public function storeDetectedDevice() {
    	
    	$dateInfo = date('Y-m-d H:m:s'); 

    	$prt_logged_user_username = isset($_SESSION['authenticatedUser']) ? $_SESSION['authenticatedUser'] : 'notloged';
    	$authenticatedUser = isset($_SESSION['authenticatedUser']) ? $_SESSION['authenticatedUser'] : '0';
    		
    	$construct_URL = $this->device_deatils['HTTP_HOST'].$this->device_deatils['REQUEST_URI'];
    	
    	$session_id = session_id();
    	
    	$http_referer = isset($_SERVER["HTTP_REFERER"])?$_SERVER["HTTP_REFERER"]:'';
    	$remote_addr = isset($_SERVER["REMOTE_ADDR"])?$_SERVER["REMOTE_ADDR"]:'';
    	
    	// Remove Mozilla/4.0 (ISA Server Connectivity Check)  and check_http/v1.4.15 (nagios-plugins 1.4.15)
    	if ( $remote_addr == '192.9.202.8' || $remote_addr == '192.9.202.208' ) {
    		return false; 
    	}
    	
    	$insert_query = "INSERT INTO access_trace (user_id, browser_name, browser_version, os, requested_resource, session_id, http_referer, remote_addr) 
    	                 VALUES 
    	                 ( $authenticatedUser, 
    	                   '{$this->device_deatils['BROWSER_NAME']}', 
    	                   '{$this->device_deatils['BROWSER_VER']}', 
    	                   '{$this->device_deatils['DEVICE_OS']}', 
    	                   '$construct_URL', 
    	                   '$session_id', 
    	                   '$http_referer', 
    	                   '$remote_addr')";
    	
    	//echo $insert_query;exit;
    	$do_insert = base::dbUse($insert_query);
    	//dbErr::getErrArray($do_insert , __METHOD__, $insert_query );
    }
        

}


