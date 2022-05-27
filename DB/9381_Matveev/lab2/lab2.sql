CREATE DATABASE IF NOT EXISTS lab2;
USE lab2;

DROP TABLE IF EXISTS `SessionFilm`;
DROP TABLE IF EXISTS `FilmGenre`;
DROP TABLE IF EXISTS `Film`;
DROP TABLE IF EXISTS `Ticket`;
DROP TABLE IF EXISTS `SessionHall`;
DROP TABLE IF EXISTS `Hall`;
DROP TABLE IF EXISTS `SessionInCinema`;
DROP TABLE IF EXISTS `Cinema`;
DROP TABLE IF EXISTS `Category`;
DROP TABLE IF EXISTS `Genre`;
DROP TABLE IF EXISTS `Session`;





CREATE TABLE `Film`
(
`filmId` SERIAL PRIMARY KEY,
`filmName` VARCHAR(50),
 `director` VARCHAR(50),
`operator` VARCHAR(50),
`mainActors` VARCHAR(1000),
`production` VARCHAR(50),
`availabilityOfPrizes` VARCHAR(500),
`sessionDuration` FLOAT,
`advertFrame` VARCHAR(1000),
`rentalCost` FLOAT
);

CREATE TABLE `Genre`
(
  `genreId` SERIAL PRIMARY KEY,
  `name` varchar(30)
);

CREATE TABLE `FilmGenre`
(
  `filmId` BIGINT  UNSIGNED NOT NULL,
  `genreId` BIGINT  UNSIGNED NOT NULL,
  FOREIGN KEY (`filmId`)  REFERENCES `Film`(`filmId`) ON DELETE CASCADE,
  FOREIGN KEY (`genreId`)  REFERENCES `Genre`(`genreId`) ON DELETE CASCADE,
  PRIMARY KEY(`filmId`, `genreId`)
);


CREATE TABLE `Session`
(
    `sessionId` SERIAL PRIMARY KEY,
    `dateAndTime` DATETIME
);

CREATE TABLE `SessionFilm`
(
    `sessionId` BIGINT  UNSIGNED NOT NULL,
    `filmId`  BIGINT  UNSIGNED NOT NULL,
    FOREIGN KEY (`sessionId`)  REFERENCES `Session`(`sessionId`) ON DELETE CASCADE,
    FOREIGN KEY (`filmId`)  REFERENCES `Film`(`filmId`) ON DELETE CASCADE,
    PRIMARY KEY (`sessionId`, `filmId`)
);

CREATE TABLE `Category`(
  `categoryId`   SERIAL PRIMARY KEY,
  `name` VARCHAR(50) NOT NULL
);

CREATE TABLE `Cinema`
(
  `cinemaId` SERIAL PRIMARY KEY,
  `categoryId` BIGINT  UNSIGNED NOT NULL,
  `name` VARCHAR(50) NOT NULL,
  `location` VARCHAR(1000) NOT NULL,
  `capacity` INT NOT NULL,
  FOREIGN KEY (`categoryId`)  REFERENCES `Category`(`categoryId`) ON DELETE CASCADE
);



CREATE TABLE `Hall`
(
    `hallId` SERIAL PRIMARY KEY,
    `hallNumber` INT UNSIGNED,
    `seatsCount` INT UNSIGNED,
    `cinemaId` BIGINT  UNSIGNED NOT NULL,
     FOREIGN KEY (`cinemaId`)  REFERENCES `Cinema`(`cinemaId`) ON DELETE CASCADE
);

CREATE TABLE `Ticket`
(
  `ticketId` SERIAL PRIMARY KEY,
  `chairNumber` INT NOT NULL,
  `price` FLOAT NOT NULL ,
  `hallId` BIGINT UNSIGNED NOT NULL,
  `sessionId` BIGINT UNSIGNED NOT NULL,
   FOREIGN KEY (`sessionId`)  REFERENCES `Session`(`sessionId`) ON DELETE CASCADE,
   FOREIGN KEY (`hallId`)  REFERENCES `Hall`(`hallId`) ON DELETE CASCADE
);

CREATE TABLE `SessionInCinema`
(
    `cinemaId`  BIGINT  UNSIGNED NOT NULL,
    `sessionId` BIGINT UNSIGNED  NOT NULL,
    FOREIGN KEY (`sessionId`)  REFERENCES `Session`(`sessionId`) ON DELETE CASCADE,
    FOREIGN KEY (`cinemaId`)  REFERENCES `Cinema`(`cinemaId`) ON DELETE CASCADE,
    PRIMARY KEY(`cinemaId`, `sessionId`)
);


CREATE TABLE `SessionHall`
(
     `hallId` BIGINT UNSIGNED NOT NULL,
     `sessionId` BIGINT UNSIGNED NOT NULL,
     FOREIGN KEY (`hallId`)  REFERENCES `Hall`(`hallId`) ON DELETE CASCADE,
     FOREIGN KEY (`sessionId`)  REFERENCES `Session`(`sessionId`) ON DELETE CASCADE,
     PRIMARY KEY(`hallId`, `sessionId` )
);

INSERT INTO `Film` (`filmName`, `director`, `operator`,  `mainActors`, `production`, `availabilityOfPrizes`, `sessionDuration`, `advertFrame`, `rentalCost`)
VALUES  ('Вечные', 'Хлоя Чжао' ,'Бен Дэвис', 'Джемма Чан Ричард Мэдден Анджелина Джоли Сальма Хайек', 'Дисней Студиос', '-', 156.0, '/home/andrey/lab2_picts/1.png', 50000.2),
        ('Йеллоустоун', 'Тейлор Шеридан', 'Бен Ричардсон', 'Кевин Костнер Джеки Уивер', 'Paramount Network', '-' ,60.0, '/home/andrey/lab2_picts/274px-YellowstoneLogoseries.webp', 95254.3),
        ('Челюсти', 'Стивен Спилберг', 'Билл Батлер', 'Рой Шайдер Роберт Шоу Ричард Дрейфус Лоррейн Гэри', 'Universal Pictures', 'Оскар Лучший фильм Лучший монтаж', 130.0, '/home/andrey/lab2_picts/1.png', 40200.3),
        ('Дом у дороги' , 'Джоэл Сильвер', 'Дин Канди', 'Патрик Суэйзи Бен Газзара Келли Линч Сэм Эллиотт',  'Silver Pictures', 'Золотая Малина (1990)',114.5, '/home/andrey/lab2_picts/200px-Road_haus.jpg', 55220.3),
        ('Мальчишник в Вегасе', 'Тодд Филлипс', 'Ларри Шер', 'Брэдли Купер Эд Хелмс Зак Галифианакис Джастин Барта', '	Legendary Pictures',  'Премия «Золотой глобус»', 100, '/home/andrey/lab2_picts/The_Hangover.jpg', 76879.2);

INSERT INTO `Genre` (`name`)
VALUES ('фэнтези'),
        ('триллер'),
        ('вестерн'),
        ('боевик'),
        ('комедия');

INSERT INTO `FilmGenre` (`filmId`, `genreId`)
VALUES (3, 3),
       (2, 2),
       (1, 1),
       (4,4),
       (5,5);



INSERT INTO `Session`(`dateAndTime`)
VALUES ('2012-02-26 09:34:00.000'),
       ('2013-03-01 09:12:00.000'),
       ('2013-03-02 19:12:01.000'),
       ('2013-02-02 09:12:00.000'),
       ('2013-04-09 14:32:00.005'),
       ('2013-06-26 13:12:00.000'),
       ('2014-02-26 09:34:00.000'),
       ('2011-08-01 09:12:00.000'),
       ('2013-03-02 15:02:01.000'),
       ('2012-02-02 09:22:00.000'),
       ('2013-05-07 14:32:00.005'),
       ('2013-06-02 12:17:00.000');

INSERT INTO `SessionFilm`(`sessionId`, `filmId`)
VALUES (1, 3),
       (2, 1),
       (3, 5),
       (4, 2),
       (5, 4);


INSERT INTO `Category`(`name`)
VALUES ('Большой'),
       ('Средний'),
       ('Маленький');

INSERT INTO `Cinema`(`name`, `location`, `capacity`, `categoryId`)
VALUES ('Мираж Синема', 'Полюстровский пр., 84А, Калининский район, Санкт-Петербург, 194021', 200, 1),
       ('Кинопаркинг', 'ул. Академика Павлова, 5, Санкт-Петербург, 197022', 300, 1),
       ('Формула Кино Сити Молл', 'Коломяжский пр., 17 А, Санкт-Петербург, 197348', 250, 2),
       ('Формула Кино Родео Драйв', 'пр. Культуры, 1, Санкт-Петербург, 195274', 240, 3),
       ('Художественный', 'Невский пр., 67, Санкт-Петербург, 191025', 300, 2);


INSERT INTO `Hall`(`hallNumber`, `seatsCount`, `cinemaId`)
VALUES (1, 200, 1),
       (2, 200, 1),
       (1, 300, 2),
       (3, 100, 3),
       (3, 100, 3),
       (3, 100, 3),
       (1, 200, 4),
       (2, 100, 4),
       (1, 200, 5);

INSERT INTO `SessionHall`(`sessionId`, `hallId`)
VALUES (1, 1),
       (2, 1),
       (2, 2),
       (3, 3),
       (4, 4),
       (4, 5),
       (5, 5),
       (6, 5),
       (6, 6),
       (7, 6),
       (7, 7),
       (8, 7),
       (9, 7),
       (10, 8),
       (11, 9),
       (12, 9);

INSERT INTO `Ticket`(`chairNumber`, `price` , `sessionId`, `hallId`)
VALUES (1, 250.0, 1, 1),
       (2, 250.0, 1, 1),
       (3, 250.0, 1, 1),
       (1, 300.0, 2, 1),
       (2, 300.0, 2, 2),
       (3, 300.0, 2, 2),
       (1, 250.0, 3, 3),
       (2, 250.0, 3, 3),
       (3, 250.0, 3, 3),
       (1, 210.0, 4, 1),
       (2, 210.0, 4, 1),
       (3, 210.0, 4, 2),
       (1, 250.0, 5, 2),
       (2, 250.0, 5, 3),
       (10, 290.0, 6, 3),
       (15, 250.0, 7, 4),
       (20, 250.0, 7, 5),
       (21, 250.0, 8, 6),
       (22, 300.0, 8, 7),
       (23, 300.0, 9, 7),
       (40, 300.0, 10, 8),
       (14, 250.0, 11, 8),
       (13, 250.0, 11, 8),
       (17, 250.0, 12, 9),
       (50, 210.0, 12, 9);



INSERT INTO `SessionInCinema`(`sessionId`, `cinemaId`)
VALUES (1, 1),
       (2, 1),
       (3, 2),
       (4, 2),
       (5, 3),
       (6, 3),
       (7, 4),
       (8, 4),
       (9, 5),
       (10, 5),
       (11, 2),
       (12, 3),
       (11,1),
       (10, 3);










