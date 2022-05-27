const express = require('express') // подключение express
const server = express(); // создаем объект приложения
const router = require("./routes/routes"); // создаём маршруты
let bodyParser = require('body-parser') // извлекает всю основную часть потока входящих запросов и предоставляет ее в req.body
let cookieParser = require('cookie-parser')





server.use(cookieParser()); // Модуль «cookie-parser» обеспечивает работу с  Cookies
server.use(bodyParser.json()); // будет использоваться для разбора запросов в формате JSON от браузера
server.use(bodyParser.urlencoded({extended: true}));
server.use('/public', express.static('public')); // для создания общедоступного каталога

server.set("views", `./views`);
server.set("view engine", "pug"); // Подключение обработчика шаблонов pug, шаблоны - в папке views

server.use('/', router);
server.listen(3000); // начинаем прослушивать подключения на 3000 порту
module.exports = router;