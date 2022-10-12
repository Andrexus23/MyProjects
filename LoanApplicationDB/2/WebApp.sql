DROP DATABASE IF EXISTS WebApp;
CREATE DATABASE IF NOT EXISTS WebApp;
USE WebApp;


DROP TABLE IF EXISTS `MainApplication`;
DROP TABLE IF EXISTS `JobData`;
DROP TABLE IF EXISTS `Person`;
DROP TABLE IF EXISTS `LoanApplication`;
DROP TABLE IF EXISTS `LoanProduct`;
DROP TABLE IF EXISTS `ServiceInLoanApplication`;
DROP TABLE IF EXISTS `Service`;
DROP TABLE IF EXISTS `PassportData`;
DROP TABLE IF EXISTS `LoanAim`;

CREATE TABLE `LoanProduct`(
	`loanProductId` INT PRIMARY KEY AUTO_INCREMENT,
  	`loanProductName` VARCHAR(100) NOT NULL
);

CREATE TABLE `Service`(
	`serviceId` INT PRIMARY KEY AUTO_INCREMENT,
  	`serviceType` VARCHAR(100) NOT NULL,
  	`serviceCost` FLOAT NOT NULL
);

CREATE TABLE `LoanAim`(
	`loanAimId` INT PRIMARY KEY AUTO_INCREMENT,
	`loanAim` VARCHAR(100) NOT NULL
);

CREATE TABLE `LoanApplication`(
  `loanApplicationId` INT PRIMARY KEY AUTO_INCREMENT,
  `loanProductId` INT NOT NULL,
  `loanAimId` INT NOT NULL,
  `loanSum` FLOAT NOT NULL,
  `loanInterestRate` FLOAT NOT NULL,
  `loanTerm` INT NOT NULL,
  `year` INT NOT NULL,
  FOREIGN KEY (`loanProductId`) REFERENCES `LoanProduct`(`loanProductId`) ON DELETE CASCADE,
  FOREIGN KEY (`loanAimId`) REFERENCES `LoanAim`(`loanAimId`) ON DELETE CASCADE
);

CREATE TABLE `ServiceInLoanApplication`(
	`loanApplicationId` INT NOT NULL,
  	`serviceId` INT NOT NULL,
  	FOREIGN KEY (`loanApplicationId`) REFERENCES `LoanApplication`(`loanApplicationId`) ON DELETE CASCADE,
    FOREIGN KEY (`serviceId`) REFERENCES `Service`(`serviceId`) ON DELETE CASCADE,
  	PRIMARY KEY(`loanApplicationId`, `serviceId`)
);



CREATE TABLE `PassportData`(
	`passportDataId` INT PRIMARY KEY AUTO_INCREMENT,
  	`series` INT NOT NULL,
  	`number` BIGINT NOT NULL,
  	`dateOfIssue`  DATETIME NOT NULL,
  	`divisionCode` VARCHAR(20) NOT NULL,
  	`issuedBy` VARCHAR(200) NOT NULL,
  	`birthDate` VARCHAR(50) NOT NULL,
  	`birthPlace` VARCHAR(200) NOT NULL,
  	`registrationRegion` VARCHAR(200) NOT NULL
);

CREATE TABLE `JobData`(
	`jobDataId` INT PRIMARY KEY AUTO_INCREMENT,
  	`jobRegion` VARCHAR(200) NOT NULL,
  	`organizationName` VARCHAR(200) NOT NULL,
  	`INN` VARCHAR(12) NOT NULL,
  	`jobPosition` VARCHAR(30) NOT NULL,
    `salary` FLOAT NOT NULL,
  	`jobStartDate` DATETIME NOT NULL
);

CREATE TABLE `Person`(
	`personId` INT PRIMARY KEY AUTO_INCREMENT,
    `passportDataId` INT NOT NULL,
  	`jobDataId` INT NOT NULL,
  	`surname` VARCHAR(50) NOT NULL,
  	`name` VARCHAR(50) NOT NULL,
  	`patronymic` VARCHAR(50),
    `phoneNumber` VARCHAR(20) NOT NULL,
  	`additionalPhoneNumber` VARCHAR(20),
  	`email` VARCHAR(100),
    FOREIGN KEY (`passportDataId`) REFERENCES `PassportData`(`passportDataId`) ON DELETE CASCADE,
  	FOREIGN KEY (`jobDataId`) REFERENCES `JobData`(`jobDataId`) ON DELETE CASCADE
);


CREATE TABLE `MainApplication`(
	`mainApplication` INT PRIMARY KEY AUTO_INCREMENT,
  	`personId` INT NOT NULL,
  	`loanApplicationId` INT NOT NULL,
  	FOREIGN KEY (`personId`) REFERENCES `Person`(`personId`) ON DELETE CASCADE,
  	FOREIGN KEY (`loanApplicationId`) REFERENCES `LoanApplication`(`loanApplicationId`) ON DELETE CASCADE
);

INSERT INTO `LoanAim` (`loanAim`)
VALUES ('потребительский (товарный)'),
	   ('автокредит'),
       ('ипотека'),
       ('ссуда на получение образования'),
       ('заем на лечение');

INSERT INTO `Service` (`serviceType`, `serviceCost`)
VALUES ('Страхование жизни', 25000.00),
	   ('Юридическая помощь', 15000.00);

INSERT INTO `LoanProduct` (`loanProductName`)
VALUES ('Кредит наличными'),
	   ('Кредит на карту'),
       ('Кредит на текущий счет в банке');

INSERT INTO `LoanApplication` (`loanProductId`, `loanAimId`, `loanSum`, `loanInterestRate`, `loanTerm`, `year`)
VALUES (1, 2, 45000.00, 7.5, 12, 2022),
	   (2, 3,55000.00, 8.0, 36, 2021),
       (1, 2,30000.00, 6.2, 15, 2022),
	   (2, 2,20000.00, 4.0, 14, 2022),
       (3, 1, 1000000.00, 1.2, 18, 2021),
	   (1,4, 75000.00, 5.2, 50, 2022),
       (3, 3,90000.00, 7.9, 30, 2022);

INSERT INTO `ServiceInLoanApplication`(`loanApplicationId`,`serviceId`)
VALUES (1, 1),
	   (2, 1),
       (3, 1),
       (4, 1),
       (1, 2),
       (2, 2),
       (3, 2),
       (4, 2);

INSERT INTO `JobData`(`jobRegion`, `organizationName`, `INN`, `jobPosition`, `salary`, `jobStartDate`)
VALUES ('Республика северная Осетия - Апания', 'Организация', '540256190', 'Слесарь', 45000.00 ,'1993-04-05 10:05:00' ),
       ('Сахалинская область', 'Организация', '283700460', 'Сварщик', 60000.00 ,'1993-04-05 10:05:00'),
       ('Ульяновская область', 'Организация', '455778262', 'Бухгалтер',60000.23,'1993-04-05 10:05:00'),
       ('Смоленская область', 'Организация', '599011235','ДИректор', 42000.00,'1993-04-05 10:05:00'),
       ('Томская область', 'Организация', '599011235', 'Повар', 75000.00 , '1993-04-05 10:05:00'),
       ('Забайкальский край', 'Организация', '896644704', 'Электрик', 18000.00 ,'1993-04-05 10:05:00');

INSERT INTO `PassportData`(`series`, `number`, `dateOfIssue`, `divisionCode`, `issuedBy`, `birthDate`, `birthPlace`, `registrationRegion`)
VALUES (4393, 465970, '18.06.2019', '770-394', 'Отделом внутренних дел России по г. Пушкино', '08.05.1982', 'Россия, г. Пушкино, Юбилейная ул., д. 21 кв.45', 'Россия, г. Пушкино'),
       (4854, 869961, '08.06.2016', '960-243', 'ОВД России по г. Элиста', '02.12.1993', 'Россия, г. Элиста, Вокзальная ул., д. 3 кв.205', 'Россия, г. Элиста'),
       (4341, 577404, '13.08.2015', '800-452', 'Отделением УФМС России по г. Барнаул', '06.11.1961', 'г. Улан-Удэ', 'Россия, г. Улан-Удэ, Совхозная ул., д. 24 кв.30' ),
       (4261, 819689, '18.06.2019', '770-394', 'Отделом внутренних дел России по г. Пушкино', '08.05.1982', 'Россия, г. Пушкино, Юбилейная ул., д. 21 кв.45', 'Россия, г. Пушкино'),
       (4424, 329526, '08.06.2016', '960-243', 'ОВД России по г. Элиста', '02.12.1993', 'Россия, г. Элиста, Вокзальная ул., д. 3 кв.205', 'Россия, г. Элиста'),
       (4142, 154853, '13.08.2015', '800-452', 'Отделением УФМС России по г. Барнаул', '06.11.1961', 'г. Улан-Удэ', 'Россия, г. Улан-Удэ, Совхозная ул., д. 24 кв.30');

INSERT INTO `Person`(`jobDataId`, `passportDataId`, `surname`, `name`, `patronymic`, `phoneNumber`, `additionalPhoneNumber`, `email`)
VALUES (1, 6, 'Николюк', 'Геннадий', 'Никифорович', '+7 (964) 784-30-86', '+7 (964) 784-30-86', 'gennadiy4432@outlook.com'),
       (2, 5,  'Минеева', 'Нина', 'Феодосьевна' ,'+7 (964) 784-30-86', '+7 (964) 784-30-86', 'gennadiy4432@outlook.com'),
       (3, 4, 'Шастин', 'Прохор', 'Петрович' ,'+7 (964) 784-30-86', '+7 (964) 784-30-86', 'gennadiy4432@outlook.com'),
       (4, 3, 'Морякова', 'Таисия', 'Федоровна'  ,'+7 (964) 784-30-86', '+7 (964) 784-30-86', 'gennadiy4432@outlook.com'),
       (5, 2, 'Цыцын', 'Игнатий',  'Денисович' ,'+7 (964) 784-30-86', '+7 (964) 784-30-86', 'gennadiy4432@outlook.com'),
       (6, 1,  'Андропова', 'Василиса', 'Тарасовна' ,'+7 (964) 784-30-86', '+7 (964) 784-30-86', 'vasilisa1973@mail.ru');

INSERT INTO `MainApplication`(`personId`, `loanApplicationId`)
VALUES (1, 1),
       (1, 2),
       (2, 3),
       (3, 4),
       (4, 5),
       (5, 6),
       (6, 7);