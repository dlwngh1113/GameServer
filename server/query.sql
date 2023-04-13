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

DELIMITER //
CREATE PROCEDURE smo_AddUser(
	_name		VARCHAR(10)
)
BEGIN
	INSERT INTO t_User
    (name, level, x, y, exp, hp, placeId)
    VALUES
    (_name, 1, 0, 0, 0, 50, 0);
END //
DELIMITER ;

CREATE TABLE r_Place(
	id			INT,
    width		INT,
    height		INT);

DELIMITER //
CREATE PROCEDURE smo_LoadPlaces()
BEGIN
	SELECT * FROM r_Place;
END //
DELIMITER ;

ALTER TABLE t_User
ADD CONSTRAINT pk_t_user PRIMARY KEY(name);

ALTER TABLE r_Place
ADD CONSTRAINT pk_r_place PRIMARY KEY(id);