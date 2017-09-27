<?php
/*
 * Creator Ivelin Vasilev
 * Date: 05.02.2013
 */

/*
 * Remove or comment old_passwords = 1 in my.cnf
 * Restart MySQL.
 * If you don’t, MySQL will keep using the old password format,
 * which will mean that you cannot upgrade the passwords using the builtin PASSWORD() hashing function.
 * The old password hashes are 16 characters, the new ones are 41 characters.
 *
 * Connect to the database, and run the following query:
 * SELECT user, Length(Password) FROM mysql.user;
 *
 * To update the password for each user, run the following:
 * SET PASSWORD FOR 'root'@'localhost'=PASSWORD('ssmtroot');
 * FLUSH PRIVILEGES;
 *
 * Singleton representation of the class
 */

class DbDbi extends mysqli {

  public  $die = true;
  public $newLine;
  private $dbServer;
  private $dbName;
  private $dbUser;
  private $dbPass;
  private $dbPort;
  private $dbSocket;
  public $link;
  public $dbSelect;
  public $dbQuery;
  public $credential = array();
  private static $instance; //store the single instance of the database
  public $savepoints;

  function __construct($dbCredentials = array()){

    ( php_sapi_name() == 'cli' && empty($_SERVER['REMOTE_ADDR'])  )  ? $this->newLine = "\n" : $this->newLine = "<br />";

    if ( count($dbCredentials) == 0) {
      $this->dbServer = dbSettings::getDbServer();
      $this->dbName = dbSettings::getDbName();
      $this->dbUser = dbSettings::getDbUser();
      $this->dbPass = dbSettings::getDbPass();
      $this->dbPort = dbSettings::getDbPort();
      $this->dbSocket = dbSettings::getDbSocket();
      	  }elseif ( count($dbCredentials) > 1 ) {
      $this->dbServer = $dbCredentials['dbServer'];
      $this->dbName = $dbCredentials['dbName'];
      $this->dbUser = $dbCredentials['dbUser'];
      $this->dbPass = $dbCredentials['dbPass'];
      $this->dbPort = $dbCredentials['dbPort'];
      $this->dbSocket = $dbCredentials['dbSocket'];
    }
    $this->dbconnect($this->dbServer, $this->dbUser, $this->dbPass, $this->dbName, $this->dbPort, $this->dbSocket );
    $this->savepoints = array();
  }

  // Ensure singleton connection
  public static function getDb( $income_db = null ){
    // Set the credentials.
    $setDbCredentials['dbServer'] = dbSettings::getDbServer($income_db);
    $setDbCredentials['dbName'] = dbSettings::getDbName($income_db);
    $setDbCredentials['dbUser'] = dbSettings::getDbUser($income_db);
    $setDbCredentials['dbPass'] = dbSettings::getDbPass($income_db);
    $setDbCredentials['dbPort'] = dbSettings::getDbPort($income_db);
    $setDbCredentials['dbSocket'] = dbSettings::getDbSocket($income_db); 
    // Open singleton connection
    $getDb = new dbDbi($setDbCredentials);
    
    return $getDb;
    
  }
  
  // Ensure singleton connection
  public static function getInstance( $dbCredentials = array() ){
    if(!self::$instance){
      self::$instance = new dbDbi($dbCredentials);
    }
    return self::$instance;
  }

  function dbconnect( $dbServer = '', $dbUser = '', $dbPass = '', $dbName = '', $dbPort = '', $dbSocket = '' ) {
    
  	$dbPort = intval($dbPort);
    $fault = null;
    $this->link = mysqli_connect($dbServer, $dbUser, $dbPass, $dbName, $dbPort, $dbSocket);
    // Set charackter set to be UTF8
    mysqli_query($this->link, 'SET NAMES "utf8"');
    mysqli_query($this->link, 'SET CHARACTER SET "utf8"'); 
    mysqli_query($this->link, 'SET COLLATION_CONNECTION=utf8_general_ci'); 
    mysqli_set_charset($this->link, 'utf8');

    if ( ! $this->link ) {
       $fault =  $this->newLine.'DB ERROR: '.mysqli_connect_errno().'!'.$this->newLine;
    }

    if ( $fault && $this->die == true ) {
    	  die($fault);
    } else {
    	  echo $fault;
    }
  }

  function dbClose(){
    mysqli_close($this->link) ;
  }

  function dbExec( $q = '' ) {
     if( $q == '') {
      return false;
    }
    $qr = mysqli_query($this->link, $q); //zadavame stoinostite

    if(mysqli_errno($this->link) > 0 ) { // mysql_errno-proverqva dali ima greshka
      return array('error' => mysqli_error($this->link), 'error_statement' => "$q", 'error_number' => mysqli_errno($this->link));
    }

    if( strtoupper( substr($q, 0, 6) ) ==='CALL') {

        while($row = mysqli_fetch_assoc($qr))
         {
          $fetchArray[] = $row;
         }


      return $fetchArray;
    } else {
      return false;
    }
  }

  function dbLastId(){
    return mysqli_insert_id($this->link);
    return $qr;
  }

  function dbAutocommit( $getWhat = TRUE ) {
    return mysqli_autocommit($this->link, $getWhat);
  }

  function dbRollback() {
    return mysqli_rollback( $this->link );
  }


  function dbCommit() {
    return mysqli_commit($this->link);
  }

  function dbStartTransaction(){
    $result = $this->dbUse("START TRANSACTION");
    if(! isset($result['error'])){
      return 1;
    }
    else{
      if(ENVIRONMENT != 'prod'){
        echo $result['error'];
      }
      else{
        echo 'An error occurred, while starting the transaction. '.$GLOBALS['message_error'];
      }
      return 0;
    }
  }

  function dbSetSavepoint($name){
    $result = $this->dbUse("SAVEPOINT $name");
    if(! isset($result['error'])){
      return 1;
    }
    else{
      if(ENVIRONMENT != 'prod'){
        echo $result['error'];
      }
      else{
        echo 'An error occurred, while creating a savepoint. '.$GLOBALS['message_error'];
      }
      return 0;
    }
  }

  function dbReleaseSavepoint($name){
    $result = $this->dbUse("RELEASE SAVEPOINT $name");
    if(! isset($result['error'])){
      return 1;
    }
    else{
      if(ENVIRONMENT != 'prod'){
        echo $result['error'];
      }
      else{
        echo 'An error occurred, while deleting a savepoint. '.$GLOBALS['message_error'];
      }
      return 0;
    }
  }

  function dbRollbackToSavepoint($name){
    if(! isset($name)){
      echo 'No savepoint name passed to dbi::dbRollbackToSavepoint()';
      return 0;
    }

    $result = $this->dbUse("ROLLBACK TO $name");
    if(! isset($result['error'])){
      return 1;
    }
    else{
      if(ENVIRONMENT != 'prod'){
        echo $result['error'];
      }
      else{
        echo 'An error occurred, while trying to rollback to a savepoint. '.$GLOBALS['message_error'];
      }
      return 0;
    }
  }

  
  function real_escape_string( $income_raw_string = '' ) {

	$escaped_string = $this->link->real_escape_string($income_raw_string);

	return $escaped_string;
  }

  function dbUse( $q = '' ) {

    $q = trim($q);
    if( $q == '') {
      return false;
    }

    $qr = mysqli_query($this->link, $q); //zadavame stoinostite

    // Check for error in the query
    if(mysqli_errno($this->link) > 0 ) { // mysql_errno-proverqva dali ima greshka
     return array('error' => mysqli_error($this->link), 'error_statement' => "$q", 'error_number' => mysqli_errno($this->link));
    }

    if( strtoupper( substr($q, 0, 6) ) === 'INSERT' ) {
      return mysqli_insert_id($this->link);
    }
    else if( strtoupper( substr($q, 0, 6) ) === 'SELECT' || strtoupper( substr($q, 0, 4) ) === 'SHOW' ) {

      $a = array();
      while($r = mysqli_fetch_assoc( $qr ) ) { // preminava ciklichno prez funkciqta i se zapisva v $r
        $a[] = $r;
      }

      mysqli_free_result($qr);

      return $a;
    }
    else {
      return mysqli_affected_rows($this->link);
    }
  }


}

