var express = require('express'); // обработчик для экспресс
var app =express();
var path = require('path');
var router = require('./routes/routes');
var bodyParser = require('body-parser');



app.set('views',path.join(__dirname,'views')); // какой каталог использовать в качестве источника файлов шаблона представления
//app.set('view engine','pug'); // сообщаем, какой шаблонизатор юзать
app.set('view engine', 'pug');
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: true}));

app.use(express.static(path.join(__dirname, "public")));
app.use('/', router);

module.exports = app;
module.exports.tableData = router.tableData;
