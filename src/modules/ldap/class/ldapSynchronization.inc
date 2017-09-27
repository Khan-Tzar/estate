<?php
/*
 * Творец  Ивелин Василев
 * По прякор Хан-Цар
 * Лето 30.09.2013 след новата ера.
 * Creator Ivelin Vasilev
 * @version $Id: ldapSynchronization.inc 5523 2015-10-05 17:12:35Z ivasilev $
 *
 */

class ldapSynchronization {

   public static function userInArray( $getValue = null ){

     $user = array();
     $BunchArray = explode(",", $getValue );
 	 for ( $Iter_1 = 0; $Iter_1 <= 2; $Iter_1++) {
	  switch ($Iter_1) {
	     case 0:
	          @list ( $Throw_1, $user['UserName'] ) = explode( "=", $BunchArray[$Iter_1] );
	         break;
	     case 1:
	          @list ( $Throw_1, $user['DepartmenT'] ) = explode( "=", $BunchArray[$Iter_1] );
	         break;
 		}
	 }

	 return $user;
   }

   public static function insert_user_access( $get_user_id, $get_grade, $get_ins_access ){

     /* ----  CHECK IF THIS USER ALREADY HAVE ACCESS LEVEL RECORD AND INSERTS IF NOT  ---- */
     $sqlAccessQuery = "SELECT COUNT(*) AS RES FROM USER_ACCESS WHERE `USER_ID`= $get_user_id";
     $sql_access_check = baseModule::dbUse($sqlAccessQuery);
     if ($sql_access_check[0]['RES'] == 0) {
       $insert_query = "INSERT INTO USER_ACCESS (`USER_ID`, `GRADE`, `ACCESS2`) VALUES ($get_user_id, '$get_grade', '$get_ins_access')";
       $sql_access_insert = baseModule::dbUse($insert_query);
       dbErr::getCliErr($sql_access_insert, __METHOD__, $insert_query);
     }
   }

   public static function treatUser( $getValue = null ){

   	global $ldapApi;
     $getUserResult =  array();
     $returnUserResult =  array();
   	 $user = ldapSynchronization::userInArray($getValue);

   	 $UserName = trim($user['UserName']);
   	 $DepartmenT = trim($user['DepartmenT']);

	 if(($UserName!='')||($DepartmenT!='')){
        // Get user details
	 	$doByArray = array("filter"=>"CN=" . $UserName . "", "attributes" => array("mail","department", "manager", 'sAMAccountName'));
        $getUserResult = $ldapApi->getGroupMembers($doByArray);
        $getUser = ldapSynchronization::userInArray($getUserResult['manager'][0]);
        $returnUserResult['mail'] = strtolower(trim($getUserResult['mail'][0]));
        $returnUserResult['mail'] = baseModuleHoard::treatMail($UserName, $returnUserResult['mail']);
        $returnUserResult['department'] = strtolower(trim($getUserResult['department'][0]));
        $returnUserResult['sAMAccountName'] = strtolower(trim($getUserResult['sAMAccountName'][0]));

        // Get Manager details
        $manager = ldapSynchronization::userInArray($getUserResult['manager'][0]);

        $managerUserName = trim($manager['UserName']);

        if( $managerUserName ){
          $doByArray = array("filter"=>"CN=" . $managerUserName . "", "attributes" => array("mail","department", "manager", 'sAMAccountName'));
          $getManagerResult = $ldapApi->getGroupMembers($doByArray);
          $returnUserResult['manager_mail'] = strtolower(trim($getManagerResult['mail'][0]));
          $returnUserResult['manager_mail'] = baseModuleHoard::treatMail($managerUserName, $returnUserResult['manager_mail']);
          $returnUserResult['manager_department'] = strtolower(trim($getManagerResult['department'][0]));
          $returnUserResult['manager_sAMAccountName'] = strtolower(trim($getManagerResult['sAMAccountName'][0]));
        }


	 }

	 return $returnUserResult;
   }

   public static function update_key_people( $get_sam_account_name = null, &$get_changed_emploee, $get_table = 'USERS' ){

   	   $sam_account_name = $get_sam_account_name;

   	   // Get user ID
   	   $get_bg_ldap_id = baseModuleHoard::getId_sAMAccountName($sam_account_name, $get_table);

   	   // If user ID not found then search in maried people
   	   if (! isset($get_bg_ldap_id[0]['ID']) ){
   	   	 $sam_account_name = baseModule::marriedMapping($get_sam_account_name);
   	   	 $get_bg_ldap_id = baseModuleHoard::getId_sAMAccountName($sam_account_name, $get_table);
   	   }

   	   // Finaly do update
	  // if ( isset($get_bg_ldap_id[0]['ID']) && ($get_bg_ldap_id[0]['KEY_PERSON'] != 1)){
	   if ( isset($get_bg_ldap_id[0]['ID'])){
		  $update_query = "UPDATE $get_table SET KEY_PERSON = 1 WHERE ID = {$get_bg_ldap_id[0]['ID']}";
		  $update_result = baseModule::dbUse($update_query);
		  if($update_result > 0){
		    $emploee['username'] = $get_sam_account_name;
		    $emploee['department'] = $get_bg_ldap_id[0]['DEPARTMENT'];
		    $get_changed_emploee[$get_table][] = $emploee;
		  }
		} else {
           cliColors::errorColorStatic("<ERROR> Emploee $sam_account_name not found... ! \n");
		}



   }

   public static function insertInUser( $getUserArray = null, $getTable = 'USERS' ){

   	  // Set default value for table BASE
   	  $getTable = ($getTable) ? $getTable : 'USERS';

   	  $userQuery = "INSERT INTO $getTable (`ID`,
   	                                   `FNAME`,
   	                                   `LNAME`,
   	                                   `INITIALS`,
   	                                   `PHONE`,
   	                                   `MOBILE`,
   	                                   `EMAIL`,
   	                                   `DEPARTMENT`,
   	                                   `DEPARTMENT_ID`,
   	                                   `COUNTRY`,
   	                                   `MANAGER_ID`,
   	                                   `POSITION`,
   	                                   `DISTINGUISHEDNAME`,
   	                                   `SAMACCOUNTNAME`,
   	                                   `LDAP_TITLE`,
   	                                   `STATUS`)
    			    VALUES ('{$getUserArray['sidId']}',
    			            '{$getUserArray['fname']}',
    			            '{$getUserArray['lname']}',
    			            '{$getUserArray['initials']}',
    			            '{$getUserArray['phone']}',
    			            '{$getUserArray['mobile']}',
    			            '{$getUserArray['mail']}',
    			            '{$getUserArray['department']}',
    			            '{$getUserArray['department_id']}',
    			            '{$getUserArray['country']}',
    			            '{$getUserArray['manager_id']}',
    			            '{$getUserArray['description']}',
    			            '{$getUserArray['distinguishedName']}',
    			            '{$getUserArray['title']}',
    			            '{$getUserArray['sAMAccountName']}','1')";

   	  $doInsert = baseModule::dbUse($userQuery);
   	  dbErr::getCliErr($doInsert, __METHOD__, $userQuery);

      return;

   }

   public static function updateUser( $getUserArray = null, $getTable = 'USERS' ){

   	  // Set default value for table BASE
   	  $getTable = ($getTable) ? $getTable : 'USERS';

   	  $userQuery = "UPDATE $getTable
   	                   SET `FNAME`='{$getUserArray['fname']}',
   	                       `LNAME`='{$getUserArray['lname']}',
   	                       `INITIALS`='{$getUserArray['initials']}',
   	                       `PHONE`='{$getUserArray['phone']}',
   	                       `MOBILE`='{$getUserArray['mobile']}',
             		       `EMAIL`='{$getUserArray['mail']}',
             		       `DEPARTMENT`='{$getUserArray['department']}',
             		       `DEPARTMENT_ID`='{$getUserArray['department_id']}',
             		       `COUNTRY`='{$getUserArray['country']}',
             		       `MANAGER_ID` = '{$getUserArray['manager_id']}',
             		       `POSITION` = '{$getUserArray['description']}',
             		       `DISTINGUISHEDNAME` = '{$getUserArray['distinguishedName']}',
             		       `SAMACCOUNTNAME` = '{$getUserArray['sAMAccountName']}',
             		       `LDAP_TITLE` = '{$getUserArray['title']}',
             		       `STATUS`='1'
             		 WHERE `ID`='{$getUserArray['sidId']}'";

   	/*  
    if ( $getUserArray['sAMAccountName'] == 'olimem' ) {
   	 print_r($userQuery);
    }*/
  
   	  $doQeury = baseModule::dbUse($userQuery);
   	  dbErr::getCliErr($doQeury, __METHOD__, $userQuery);

      return;

   }

   public static function getUserEmailByNameDepartment( $getUser = array(), $getTable = 'USERS' ){


   	  // Set default value for table BASE
   	  $getTable = ($getTable) ? $getTable : 'USERS';

   	  $getUser['fname'] = isset($getUser['fname']) ? $getUser['fname'] : '';
      $getUser['lname'] = isset($getUser['lname']) ? $getUser['lname'] : '';
      $getUser['department'] = isset($getUser['department']) ? $getUser['department'] : '';

   	  //cliColors::infoColorStatic("\n<INFO> Check LDAP SID : $ldapSid \n");
   	  $sqlQuery = "SELECT EMAIL
   	                 FROM $getTable
                    WHERE FNAME = '{$getUser['fname']}'
                      AND LNAME = '{$getUser['lname']}'
                      AND DEPARTMENT = '{$getUser['department']}'
                      AND STATUS=1 ";

   	  $getResult = baseModule::dbUse($sqlQuery);

      dbErr::getCliErr($getResult, __METHOD__, $sqlQuery);
      return $getResult[0]['EMAIL'];

   }

   public static function checkBaseAndUserTables( $ldapSid = null, $getTable = 'USERS' ){

      $column_sid = 'SID';

   	  if ( $getTable == 'USERS' ) { // When we have BASE this table should be Joined with USERS
   	  	$joinTable = 'USERS';
   	  } elseif ( $getTable == 'FRLDAP_USERS' ){ // When we have FRLDAP_BASE this table should be Joined with FRLDAP_USERS
   	  	$joinTable = 'FRLDAP_USERS';
   	  	$column_sid = 'SIDFR';
   	  }


   	  //cliColors::infoColorStatic("\n<INFO> Check LDAP SID : $ldapSid \n");
   	  $sqlQuery = "SELECT b.`ID`, u.ID AS CNT_U
                        FROM BASE b
                        LEFT JOIN $joinTable u
                          ON b.`ID` = u.`ID`
                       WHERE b.`$column_sid` = '$ldapSid'";

   	  $getResult = baseModule::dbUse($sqlQuery);

      dbErr::getCliErr($getResult, __METHOD__, $sqlQuery);
      return $getResult;

   }

   public static function registerSid( $ldapSid = null, $get_column = 'SID' ){

   	  // Set default value for table BASE
   	  $get_column = ($get_column) ? $get_column : 'SID';
   	  cliColors::infoColorStatic("\n<INFO> Register new LDAP $get_column : $ldapSid \n");
   	  $newSidQuery = "INSERT INTO BASE (`$get_column`) VALUES ('$ldapSid')";
   	  baseModule::dbUse($newSidQuery);
      $getSidId = baseModule::dbLastId();

      return $getSidId;

   }

   public static function getLocalDbUserSid( $ldapSid = null, $getColumn = 'SID', $where_column = 'SID' ){

   	  // Set default value SID
   	  $getColumn = ($getColumn) ? $getColumn : 'SID';
   	  // Set default value SID
   	  $where_column = ($where_column) ? $where_column : 'SID';

   	  $return = null;
   	  
   	  $getLocalDbUserSidQuery = "SELECT $getColumn FROM BASE WHERE `$where_column`= '$ldapSid'";
   	  //echo $getLocalDbUserSidQuery;//exit;
   	  $getLocalDbUserSid = baseModule::dbUse($getLocalDbUserSidQuery);
   	  
   	  if(isset($getLocalDbUserSid[0])){
   	  	$return = $getLocalDbUserSid[0][$getColumn];
   	  }
   	  
   	  return $return;

   }

   public static function treatDepartment( $user_entry = array() ){

   	  if (!isset($user_entry['department'][0])){
   	  	$department = '---';
   	  } else if ($user_entry['department'][0] == '' && $user_entry['co'][0]== 'France'){
       	 $department = 	trim($user_entry['co'][0]);
       } else{
         $department = trim( $user_entry['department'][0] );
       }
       return $department;
   }

   public static function writeLdapUserImage( $userPreStack = array() ){
       // Here we write the pictures used in the LDAP phones part
	   $myFile = $userPreStack['sAMAccountName'].".jpg";
       //echo $myFile; exit;
	   $fh = @fopen(ROOT."/../phones/images/".$myFile, 'w');
	   @fwrite($fh, $userPreStack['image']);
	   @fclose($fh);

	   $fh2 = @fopen(ROOT."/images/LDAP_img/".$myFile, 'w');
	   @fwrite($fh2, $userPreStack['image']);
	   @fclose($fh2);

	   /*echo ROOT."/../phones/images/".$myFile."\n";
	   echo ROOT."/images/LDAP_img/".$myFile."\n";
	   exit;*/
	   
   }

   public static function getLdapUserStack( $userPreStack = array() ){

   	 $getLdapApi = $userPreStack['ldapApi'];
   	 $entry_iteration = $userPreStack['entry_iteration'];

   	 $userStack2['getLdapSid'] = $getLdapApi->ldap_get_values_len ($entry_iteration, "objectsid");
   	 
   	 // Set First Name
   	 $userStack2['fname'] = isset($userPreStack['user_entry']['givenName'][0]) ? ucfirst(trim($userPreStack['user_entry']['givenName'][0])) : '';

   	 // Set Last Name
     $userStack2['lname'] = isset($userPreStack['user_entry']['sn'][0]) ? ucfirst(trim($userPreStack['user_entry']['sn'][0])) : '';

     // Set User initials
     $userStack2['initials'] = isset($userPreStack['user_entry']['initials'][0]) ? ucfirst(trim($userPreStack['user_entry']['initials'][0])) : '';

     // Set Phone
     $userStack2['phone'] = isset($userPreStack['user_entry']['telephoneNumber'][0]) ? trim($userPreStack['user_entry']['telephoneNumber'][0]) : '';

     // Set Mobile
     $userStack2['mobile'] = isset($userPreStack['user_entry']['mobile'][0]) ? trim($userPreStack['user_entry']['mobile'][0]) : '';

     // Set User Name
     $userStack2['username'] = isset($userPreStack['user_entry']['cn'][0]) ? trim($userPreStack['user_entry']['cn'][0]) : '';

     // Set Manager Dis Name
     //$userStack2['manager_dn'] = isset($userPreStack['user_entry']['manager'][0]) ? $userPreStack['user_entry']['manager'][0] : '';
     if (isset($userPreStack['user_entry']['manager'][0])) {
   	   $userStack2['manager_dn'] =	$userPreStack['user_entry']['manager'][0];
   	 }

   	 // Set Manager Distinguished Name
   	 $userStack2['distinguishedName'] =	isset($userPreStack['user_entry']['distinguishedName'][0]) ? $userPreStack['user_entry']['distinguishedName'][0] : '';

     // Set Country
     $userStack2['country'] = isset($userPreStack['user_entry']['company'][0]) ? $userPreStack['user_entry']['company'][0] : '';

     // Set Initials
     $userStack2['initials'] = isset($userPreStack['user_entry']['initials'][0]) ? $userPreStack['user_entry']['initials'][0] : '';

     // Set Description
   	 $userStack2['description'] =	isset($userPreStack['user_entry']['description'][0]) ? $userPreStack['user_entry']['description'][0] : 'UNDEFINED';

   	 // Set Title
   	 $userStack2['title'] =	isset($userPreStack['user_entry']['title'][0]) ? $userPreStack['user_entry']['title'][0] : 'UNDEFINED';

     if (isset($userPreStack['user_entry']['mail'][0])) {
   	   // Set user mail
       $check_username        = $userStack2['fname']." ".$userStack2['lname'];
       $userStack2['mail']     = baseModuleHoard::treatMail($check_username, $userPreStack['user_entry']['mail'][0]);
   	 } else {
   	 	$userStack2['mail'] = '';
   	 }

     // Get department
     $userStack2['department'] = ldapSynchronization::treatDepartment( $userPreStack['user_entry'] );

     // Put facke id
     $userStack2['department_id'] = '';

     // Get sAMAccountName
     $userStack2['sAMAccountName'] = $userPreStack['user_entry']['sAMAccountName'][0];
     
     // Get picture
     $userStack2['image'] = @ldap_get_values_len( $userPreStack['ldapApi']->ldapconnection, $userPreStack['entry_iteration'], "thumbnailPhoto");
     $userStack2['image'] = $userStack2['image'][0];
     
     /*if( $userStack2['sAMAccountName'] == 'ivasilev'){
     //	$jpeg_data = ldap_get_values_len( $ldapconn, $i, "thumbnailPhoto");
     	$fh2 = @fopen("/instances/phpdev/www/ivas_HR/prototypes/ttable_ivas/ivas_test.jpg", 'w');
     	fwrite($fh2, $userStack2['image'][0]);
     	fclose($fh2);
     }*/
    return $userStack2;

   }
}
