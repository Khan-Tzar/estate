
CREATE TABLE `enum_values` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` varchar(64) NOT NULL,
  `subtype` varchar(16) DEFAULT NULL,
  `key` varchar(64) NOT NULL,
  `value` varchar(256) NOT NULL,
  `description` varchar(128) DEFAULT NULL,
  `active` tinyint(1) NOT NULL,
  `sortindex` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_enum_values_unq_type_subtype_key` (`type`,`subtype`,`key`),
  UNIQUE KEY `idx_enum_values_unq_type_subtype_sortindex` (`type`,`subtype`,`sortindex`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8