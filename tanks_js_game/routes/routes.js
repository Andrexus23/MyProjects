var express = require('express');
var router = express.Router();
const fileName = '../storage/table';
let tableData = require(fileName);


/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('main');
});

router.put("/", function (req, res){
  if(tableData[req.query.name]){
    if(parseInt(tableData[req.query.name]) <= parseInt(req.query.record)){
      tableData[req.query.name] =req.query.record;
    }
  } else{
    tableData[req.query.name] =req.query.record;
  }

  res.status(200);
});

router.get("/table/", function (req, res){
  let pairs =  Object.entries(tableData);
  pairs.sort(function (a, b){
    return b[1] - a[1];
  });
  res.render("table", {pairs});

});

module.exports = router;
module.exports.tableData = tableData;

/*
 Object.entries() метод возвращает массив собственных перечисляемых свойств указанного объекта
 в формате [key, value], в том же порядке, что и в цикле for...in
 */
