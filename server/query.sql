CREATE SCHEMA IF NOT EXISTS `DnD`;

USE `DnD`;

CREATE TABLE IF NOT EXISTS `t_User`(
	`id` VARCHAR(12) PRIMARY KEY NOT NULL,
    `password` VARCHAR(128) NOT NULL,
    `x` FLOAT DEFAULT 0,
    `y` FLOAT DEFAULT 0
    );
    
DELIMITER $$

CREATE PROCEDURE AddUser(
    IN p_id VARCHAR(12),
    IN p_password VARCHAR(128)
)
BEGIN
    DECLARE existing_count INT;

    -- Check for existing records with the same id
    SELECT COUNT(*)
    INTO existing_count
    FROM users
    WHERE id = p_id;

    -- If no existing record is found, insert the new record with hashed password
    IF existing_count = 0 THEN
        INSERT INTO users (id, password) VALUES (p_id, SHA2(p_password, 256));
    ELSE
        -- Raise an error if a duplicate entry is found
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Duplicate entry found';
    END IF;
END $$

DELIMITER ;

USE `DnD`;

DELIMITER $$

CREATE PROCEDURE GetUser(
    IN p_id VARCHAR(12),
    IN p_password VARCHAR(128)
)
BEGIN
    -- 실제로 반환할 결과셋을 선택합니다.
    SELECT *
    FROM t_user
    WHERE id = p_id AND password = SHA2(p_password, 256);
END $$

DELIMITER ;