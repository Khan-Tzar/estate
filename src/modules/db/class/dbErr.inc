<?php
/*
 * Creator Ivelin Vasilev
 * Date: 07.11.2012
 */

class dbErr extends base{

       public static function getCliErr( $income = '', $method = '', $query = ''){

          	 cliColors::errorColorStatic("<ERROR> in method: $method ! \n");
          	 cliColors::errorColorStatic("<ERROR> Query: $query ! \n");

	   }
      
	   
       public static function getErrArray( $income = '', $method = '', $query = '' ){

           if ( isset($income['error'])  ) {
          	 $income['method'] = $method;
          	 $income['query'] = $income['error_statement'];
mdebug($income);
          	// dbFormSendMail::formSendMail( $income );
          	 if (php_sapi_name() == 'cli' && empty($_SERVER['REMOTE_ADDR'])  ){
          	 	self::getCliErr($income, $method, $query);
          	 } else {
          	 	cliColors::errorColorStatic('<ERROR> In sql statemnt ! '."\n");
          	 }

             exit(1);
          }

	   }



	}
