<?php
/*
 * Разкрасител Ивелин Василев
 * Лето: 06.11.2012
 *
 *  cliColors::customColorStatic("<INFO> Test  \n", 'yellow');
    cliColors::customColorStatic("<INFO> Skip  \n", 'light_gray');
    cliColors::customColorStatic("<INFO> Skip  \n");
 */

class cliColors {
        private static $foreground_colors = array('black'=>'0;30',
                                                  'dark_gray'=>'1;30',
                                                  'blue'=>'0;34',
                                                  'sky'=>'1;39',
                                                  'light_blue'=>'1;34',
                                                  'green'=>'0;32',
                                                  'light_green'=>'1;32',
                                                  'cyan'=>'0;36',
                                                  'light_cyan'=>'1;36',
                                                  'red'=>'0;31',
                                                  'light_red'=>'1;31',
                                                  'purple'=>'0;35',
                                                  'light_purple'=>'1;35',
                                                  'brown'=>'0;33',
                                                  'yellow'=>'1;33',
                                                  'light_gray'=>'0;37',
                                                  'white'=>'1;37');

        private static $background_colors = array('black'=>'40',
                                                  'red'=>'41',
                                                  'green'=>'42',
                                                  'yellow'=>'43',
                                                  'blue'=>'44',
                                                  'magenta'=>'45',
                                                  'cyan'=>'46',
                                                  'light_gray'=>'47');

		public function __construct() {
			// Set up shell colors
		}

		// Simple switcher of collors odd and even
        public static function switch_color( &$get_color = null ){

        	if($get_color == "#fff"){
              $get_color = "#eee";
            } else { $get_color = "#fff"; }

            return $get_color;
	    }

	    public static function add_file_line($get_file = null, $get_line = null){

	      // String to return !
	      $file_line_string = '';
	      // Check is file is defined
	      if($get_file){
	       $file_line_string .= " File: $get_file \n";
	      }
          // Check is line is defined
          if($get_line){
	       $file_line_string .= " Line: $get_line";
	      }
         return $file_line_string;
	    }

         public static function customColorStatic($string, $get_color = 'light_purple' ){
           $timeValue = date("H:i:s");
	       $colored_string = "\033[" . self::$foreground_colors[$get_color] . "m";

           $colored_string .=  $string . "\033[0m";
           echo  $colored_string;
	     }


         public static function infoColorStatic($string, $get_file = null, $get_line = null){
           $timeValue = date("H:i:s");
	       $colored_string = "\033[" . self::$foreground_colors['light_green'] . "m";
           //$colored_string .=  "\t[$timeValue]".$string . "\033[0m";

	       // Get file and line
           $file_line_string = self::add_file_line($get_file, $get_line);

           $colored_string .=  $string . $file_line_string. "\033[0m";
           echo  $colored_string;
	     }

	     public static function warningColorStatic($string, $get_file = null, $get_line = null){
           $colored_string = "";
	       $colored_string .= "\033[" . self::$foreground_colors['light_purple'] . "m";

	       // Get file and line
           $file_line_string = self::add_file_line($get_file, $get_line);

           $colored_string .=  $string . $file_line_string. "\033[0m";
           echo  $colored_string;
	     }

	     public static function attentionColorStatic($string, $get_file = null, $get_line = null){
           $colored_string = "";
	       $colored_string .= "\033[" . self::$foreground_colors['yellow'] . "m";

	       // Get file and line
           $file_line_string = self::add_file_line($get_file, $get_line);

           $colored_string .=  $string . $file_line_string. "\033[0m";
           echo  $colored_string;
	     }

         public static function errorColorStatic($string, $get_file = null, $get_line = null){
	       $colored_string = "\033[" . self::$foreground_colors['light_red'] . "m";

	       // Get file and line
           $file_line_string = self::add_file_line($get_file, $get_line);

           $colored_string .=  $string . $file_line_string. "\033[0m";
           echo  $colored_string;
	     }

		// Returns colored string
		public function getColoredString($string, $foreground_color = null, $background_color = null) {
			$colored_string = "";

			// Check if given foreground color found
			if (isset(self::$foreground_colors[$foreground_color])) {
				$colored_string .= "\033[" . self::$foreground_colors[$foreground_color] . "m";
			}
			// Check if given background color found
			if (isset(self::$background_colors[$background_color])) {
				$colored_string .= "\033[" . self::$background_colors[$background_color] . "m";
			}

			// Add string and end coloring
			$colored_string .=  $string . "\033[0m";

			return $colored_string;
		}

        public function infoColor($string) {
			echo $this->getColoredString($string, "light_green")."\n";
		}

        public function errorColor($string) {
			echo $this->getColoredString($string, "light_red")."\n";
		}

		// Returns all foreground color names
		public function getForegroundColors() {
			return array_keys(self::$foreground_colors);
		}

		// Returns all background color names
		public function getBackgroundColors() {
			return array_keys(self::$background_colors);
		}
	}

?>