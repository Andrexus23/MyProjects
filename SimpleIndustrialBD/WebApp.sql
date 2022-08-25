DROP DATABASE IF EXISTS WebApp;
CREATE DATABASE IF NOT EXISTS WebApp;
USE WebApp;


DROP TABLE IF EXISTS `Department`;
DROP TABLE IF EXISTS `Worker`;
DROP TABLE IF EXISTS `Note`;
DROP TABLE IF EXISTS `Cabinet`;
DROP TABLE IF EXISTS `Workplace`;


CREATE TABLE `Department`(
	`departmentId` INT PRIMARY KEY AUTO_INCREMENT,
  	`name` VARCHAR(100)
);

CREATE TABLE `Worker`(
	`workerId` INT PRIMARY KEY AUTO_INCREMENT,
  	`surname` VARCHAR(50),
  	`name`  VARCHAR(50)
);



CREATE TABLE `Cabinet` (
    `cabinetId` INT PRIMARY KEY AUTO_INCREMENT,
    `departmentId` INT NOT NULL,
    `number` INT,
    FOREIGN KEY (`departmentId`) REFERENCES `Department` (`departmentId`) ON DELETE CASCADE
);

CREATE TABLE `Workplace`(
    workplaceId INT PRIMARY KEY AUTO_INCREMENT,
    `cabinetId` INT NOT NULL,
    `number` INT,
    FOREIGN KEY (`cabinetId`) REFERENCES `Cabinet` (`cabinetId`) ON DELETE CASCADE
);

CREATE TABLE `Note` (
    `workerId` INT NOT NULL,
    `date` DATE,
    workplaceId INT NOT NULL,
    FOREIGN KEY (`workerId`) REFERENCES `Worker` (`workerId`) ON DELETE CASCADE,
    FOREIGN KEY (workplaceId) REFERENCES `Workplace` (workplaceId) ON DELETE CASCADE,
    PRIMARY KEY (`workerId`,  `date`)
);

INSERT INTO `Worker` (`surname`, `name`)
VALUES ('Попова', 'Анна'),
       ('Соколова', 'Амина'),
       ('Соколов', 'Евгений'),
       ('Лапшина', 'Елизавета'),
       ('Кузнецов', 'Никита'),
       ('Кузин', 'Артём'),
       ('Кочеткова', 'Ева'),
       ('Широкова', 'Алёна');


INSERT INTO `Department` (`name`)
VALUES ('Финансово-экономический департамент'),
       ('Департамент логистики'),
       ('Производственный департамент'),
       ('Коммерческий департамент');

INSERT INTO `Cabinet` (`departmentId`, `number`)
VALUES (1, 1),
       (1, 2),
       (1, 3),
       (2, 4),
       (2, 5),
       (2, 6),
       (2, 7),
       (3, 8),
       (3, 9),
       (3, 10),
       (4, 11),
       (4, 12),
       (4, 13),
       (4, 14);

INSERT INTO `Workplace` (`cabinetId`, `number`)
VALUES (1, 1),
       (1, 2),
       (1, 3),
       (2, 1),
       (2, 2),
       (3, 1),
       (3, 2),
       (3, 3),
       (4, 1),
       (5, 1),
       (6, 1),
       (6, 2),
       (7, 1),
       (8, 1),
       (9, 1),
       (9, 2),
       (9, 3),
       (10, 1),
       (11, 1),
       (11, 2),
       (12, 1),
       (13, 1),
       (14, 1),
       (14, 2);

INSERT INTO `Note` (workplaceId, `workerId`, `date`)
VALUES ( 24, 1, '2022-06-20'),
       ( 23, 8, '2022-06-20'),
       ( 6, 4, '2022-06-20'),
       ( 7, 6, '2022-06-20'),

       (1, 7, '2022-06-21'),
       (2, 8, '2022-06-21'),
       (9, 2, '2022-06-21'),
       (4, 3, '2022-06-21'),

       (2, 6, '2022-06-28'),
       (1, 7, '2022-06-28'),
       (15, 2, '2022-06-28'),
       (16, 4, '2022-06-28'),
       (19, 1, '2022-06-28'),

       (2, 7, '2022-07-04'),
       (13, 8, '2022-07-04'),

       (1, 3, '2022-07-06'),
       (9, 1, '2022-07-06'),
       (22, 8, '2022-07-06'),

       (4, 8, '2022-07-07'),

       (11, 1, '2022-07-11'),
       (17, 6, '2022-07-11'),

       (1, 5, '2022-07-14'),
       (18, 4, '2022-07-14'),
       (12, 6, '2022-07-14'),
       (16, 7, '2022-07-14'),

       (15, 4, '2022-07-15'),
       (14, 3, '2022-07-15'),

        (8, 2,'2022-07-16'),
        (17, 1, '2022-07-16'),
       (14, 6, '2022-07-16'),
       (13, 3, '2022-07-17');