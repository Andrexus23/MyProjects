
SELECT `Worker`.`surname` AS "Фамилия", `Worker`.`name` AS "Имя", `Note`.`date` AS "Дата", `Workplace`.`number` AS "Место №", `Cabinet`.`number` AS "Кабинет №"
FROM `Note` INNER JOIN `Worker` ON `Note`.`workerId` = `Worker`.`workerId`
INNER JOIN `Workplace` ON `Note`.`workplaceId` = `Workplace`.`workplaceId`
INNER JOIN `Cabinet` ON `Cabinet`.`cabinetId` = `Workplace`.`cabinetId`
ORDER BY `Note`.`date`
