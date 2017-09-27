<?php
/*
 * Creator Ivelin Vasilev
 * Date: 30.03.2015
 * @version $Id: ldapApiHoard.inc 5649 2015-11-16 08:43:08Z nvalkanova $
 */

class ldapApiHoard {

   public static function get_just_a_bind( $employee_distinguishedName = null, $get_ldap = 'ldap_fr', $get_pass = null ){
		$ldap_api_get = new ldapApi(array('target' => $get_ldap, 'user' => $employee_distinguishedName, 'pass' => $get_pass,));	
		
		$ldap_api_get->set_cuser($employee_distinguishedName);
		$ldap_api_get->set_cpass($get_pass);
		// To not exit in case of error. 
        $ldap_api_get->return = true;
		@$ldap_api_get->get_ldap();
		
		//print_r($ldap_api_get);
		if(isset($ldap_api_get->ldapbind) && $ldap_api_get->ldapbind != 1 ){
		   return false;
		}
	 return true;
   }	

   public static function getLdapAccountAttributes( $incomeSamaccountname = null, $incomeLdap = null ){

   	 $ldapApi = new ldapApi(array('target' => $incomeLdap));

     /* ----  CONNECTING TO THE LDAP DATABASE ---- */
     $baseDn = baseSettings::getLdapBaseDn($incomeLdap);
     $justThese = baseSettings::getLdapAttributesl();
     // Get Api
     $ldapApi->get_ldap();
     // Do LDAP search
     //$ldapSearch = $ldapApi->ldap_search();
     $searchLdap = ldap_search($ldapApi->ldapconnection, $baseDn,"sAMAccountName=$incomeSamaccountname", $justThese);
     $ldapError = ldap_error($ldapApi->ldapconnection);
     $ldap_count_entries = ldap_count_entries($ldapApi->ldapconnection,$searchLdap);

     if ( $ldap_count_entries === 0 ){
     	$regali['error'][] = "No result found for $incomeSamaccountname";
     } else {
        $getEntry = ldap_first_entry($ldapApi->ldapconnection, $searchLdap);
        $getAttributes = ldap_get_attributes($ldapApi->ldapconnection, $getEntry);

        // print_r($get_attributes['objectSid']);exit;
        $regali['fname'] =  ucfirst(trim($getAttributes['givenName'][0]));
        $regali['lname'] =  ucfirst(trim($getAttributes['sn'][0]));
        $regali['username'] =  trim($getAttributes['cn'][0]);
        $regali['manager'] =  isset($getAttributes['manager'][0]) ? $getAttributes['manager'][0] : '';
        $regali['department'] = isset($getAttributes['department'][0]) ? trim($getAttributes['department'][0]) : '';
        $regali['sAMAccountName'] = strtolower(trim($getAttributes['sAMAccountName'][0]));
        $regali['mail'] = isset($getAttributes['mail'][0]) ? strtolower(trim($getAttributes['mail'][0])) : '' ;
        $regali['country'] = isset($getAttributes['company'][0]) ? trim($getAttributes['company'][0]) : '';
        $regali['initials'] = isset($getAttributes['initials'][0]) ? trim($getAttributes['initials'][0]) : '';
        $regali['distinguishedName'] = isset($getAttributes['distinguishedName'][0]) ? trim($getAttributes['distinguishedName'][0]) : '';
        $regali['objectsid'] = $ldapApi->ldap_get_values_len ($getEntry, "objectSid");
        $regali['memberOf'] = isset($getAttributes['memberOf']) ? $getAttributes['memberOf'] : '';
     }
     return $regali;
   }

}
