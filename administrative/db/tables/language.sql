CREATE TABLE `language` (
  `language_id` int(4) NOT NULL AUTO_INCREMENT,
  `lang` varchar(32) NOT NULL,
  `lang_description` varchar(200) DEFAULT NULL,
  `lng_status` enum('enabled','disabled') DEFAULT 'disabled',
  PRIMARY KEY (`language_id`),
  UNIQUE KEY `lang` (`lang`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED