<?php
/*
 * Творец  Ивелин Василев
 * Date 10.09.2013
 *
 */

class baseTemplater extends base {

  private $template;

   function __construct($template = null, $action = null ) {
      
    if (isset($template)) {
      $this->load($template);
    }
            
    if( $action == 'publish' ){
      self::publish();
    }
            
   }

   // Try to construct template path by its name 
   public static function get_template_location($template){
     	
     $location = '';
     // Take file details
     $get_pathinfo  = pathinfo($template);
     	
     if($get_pathinfo['dirname'] === '.'){
         
     // Make first letter Capital
     $template_first_letter_capital = ucfirst($template);
     // Split template name in array
     preg_match_all('/[A-Z][^A-Z]*/', $template_first_letter_capital, $split_in_array);
          
     if ( isset($split_in_array[0]) && isset($split_in_array[0][0]) ) {
       // Make whole string lowercase
       $moduleName = strtolower($split_in_array[0][0]);
     }
         
     // Construct final location
     $location = ROOT."/src/modules/$moduleName/tpl/$template";
     	
     }
     return $location;
   }
     
   public function load($template) {
     /*
      * This function loads the template file
      */

     $template_location = self::get_template_location($template);
       
     if($template_location){
      $template = $template_location;
     }
              
     if (!is_file($template)){
       print_r("File not found: $template");
     } elseif (!is_readable($template)){
       print_r("Could not access file: $template");
     } else {
       $this->template = $template;
     }
   }

   public function set($var, $content){
      $this->$var = $content;
   }

   public function concat($var, $content){
      $this->$var .= $content;
   }

   public function publish($output = true){
     /*
      * Prints out the theme to the page
      * However, before we do that, we need to remove every var witin {} that are not set
      * @params
      *  $output - whether to output the template to the screen or to just return the template
      */
     ob_start();
     require $this->template;
     $content = ob_get_clean();

     print($content);
   }
  
   public function parse(){
     /*
      * Function that just returns the template file so it can be reused
      */
     ob_start();
     require $this->template;
     $content = ob_get_clean();
     return $content;
    }
}
