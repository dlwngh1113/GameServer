use SMO;

CREATE TABLE r_MetaDatas(
	sectorWidthCount		INT,
    sectorHeightCount 		INT);
    
CREATE TABLE t_User(
	name		VARCHAR(10),
    level		INT,
    x			INT,
    y			INT,
    exp			INT,
    hp			INT,
    placeId		INT);
    
DELIMITER //
CREATE PROCEDURE smo_GetUser(
	IN		_name		VARCHAR(10)
)
BEGIN
	SELECT * FROM t_User AS a
    WHERE a.name = _name;
END //
DELIMITER ;