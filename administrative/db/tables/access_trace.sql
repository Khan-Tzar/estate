
DROP TABLE `access_trace`;
CREATE TABLE `access_trace` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `access_time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `left_page_time` datetime DEFAULT NULL,
  `remote_addr` varchar(150) COLLATE utf8_bin DEFAULT NULL,
  `http_referer` varchar(150) COLLATE utf8_bin DEFAULT NULL,
  `browser_name` varchar(150) COLLATE utf8_bin DEFAULT NULL,
  `browser_version` varchar(20) COLLATE utf8_bin DEFAULT NULL,
  `os` varchar(30) COLLATE utf8_bin DEFAULT NULL,
  `requested_resource` text COLLATE utf8_bin,
  `session_id` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;