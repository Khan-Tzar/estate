<?php 
// Аirmonger: Ivelin Vasilev
// Date: 2016.02.18

use \Src\Autoloader;

require_once(ROOT.'/src/Autoloader.inc');
// Зареждане на автоматичният зареждач
Autoloader::register();

// Define Web Root УРЛ-то със все домейн и път
define("WEB_ROOT", Base::getUrl());


// Open singleton connection
$localDb = DbDbi::getInstance();

// Split URL in rest array
Rest::splitRest();
// Detect language
Rest::checkLanguage();

// Include language
include_once(ROOT."/src/modules/language/translation/lang_".$GLOBALS['rest']['language'].".inc");
