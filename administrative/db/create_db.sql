
-- 2017-09-26

CREATE DATABASE `estate` CHARACTER SET utf8;
drop user estate@'localhost';
FLUSH PRIVILEGES;
CREATE user 'estate'@'localhost' IDENTIFIED BY 'estate';
GRANT ALL PRIVILEGES ON estate.* TO 'estate'@'localhost';
GRANT LOCK TABLES ON estate.* TO 'estate'@'localhost';
GRANT CREATE VIEW ON estate.* TO 'estate'@'localhost';
FLUSH PRIVILEGES;


