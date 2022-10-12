USE  WebApp;
# для начала выведем фамилию, имя и название услуги, год взятия займа
SELECT `surname`, `name`, `loanProductName`, `year` FROM `MainApplication`
    INNER JOIN `Person` USING(`personId`)
    INNER JOIN `LoanApplication` USING(`loanApplicationId`)
    INNER JOIN `LoanProduct` USING(`loanProductId`)
ORDER BY `surname`;

# теперь сгрупируем по названию услуги и выведем количество заявок на каждый вид услуги в 2022 году
SELECT `loanProductName`, COUNT(`loanProductName`)  FROM `MainApplication`
    INNER JOIN `Person` USING(`personId`)
    INNER JOIN `LoanApplication` USING(`loanApplicationId`)
    INNER JOIN `LoanProduct` USING(`loanProductId`)
WHERE (`year` = 2022)
GROUP BY `loanProductName`;

# теперь выберем  столбец с названием услуги и отсортируем по убыванию количества. После
# при помощи оператора LIMIT органичим количество выводимых строк числом 1. Данный запрос - ответ на второе задание
SELECT `loanProductName`  FROM `MainApplication`
    INNER JOIN `Person` USING(`personId`)
    INNER JOIN `LoanApplication` USING(`loanApplicationId`)
    INNER JOIN `LoanProduct` USING(`loanProductId`)
WHERE (`year` = 2022)
GROUP BY `loanProductName`
ORDER BY COUNT(`loanProductName`) DESC
LIMIT 1;