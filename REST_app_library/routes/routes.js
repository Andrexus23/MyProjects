const express = require('express')
const bodyParser = require('body-parser');
const router = express.Router();
const lib = require("../public/storage.json")
var session = require('express-session');

const body_parser = require("express");
const {route} = require("express/lib/router");
router.use(body_parser.json());

router.get('/', (req, res, next)=>{
    res.render("input");
    next(); // переход к следующему обработчику
});


router.get('/lib', (req, res, next)=> {
    res.render("main", {title: "Library", books: lib});
});

router.get('/lib/:num', (req, res)=>{
    const id = req.params.num;
    if(id === "showAll"){
        let list = [];
        for (let i of lib) list.push(i.id);
        res.end(JSON.stringify(list));
        return;
    }
    if(id === "showAvailable"){
        let list = [];
        lib.forEach((v, i) => {
            if (v.isAvailable === "-")
                list.push(v.id)
        });
        res.end(JSON.stringify(list));
    }
    if(id === "showTaken"){
        let list = [];
        lib.forEach((v, i) => {
            let returnDate = new Date(v.returnDate + 'T23:59:59.999Z');
            let curDate = new Date();
            if (v.isAvailable === "+" || (curDate >= returnDate)) {
                list.push(v.id)
            }
        });
        res.end(JSON.stringify(list));
    }
    if(id === "showExpired"){
        let list = [];
        lib.forEach((v, i) => {
            let returnDate = new Date(v.returnDate + 'T23:59:59.999Z');
            let curDate = new Date();
            if (v.isAvailable === "+" || (curDate < returnDate)) {
                list.push(v.id)
            }
        });
        res.end(JSON.stringify(list));
    }
    for (let value of lib) {
        if (value.id == id) {
            res.render('book', {
                id: `${value.id}`, title: `${value.title}`,
                author: `${value.author}`, date: `${value.date}`, isAvailable: `${value.isAvailable}`,
                reader: `${value.reader}`, returnDate: `${value.returnDate}`
            });
            return;
        }
    }
})


router.post('/lib/read/:num', (req, res)=>{
    let id = req.params.num;
    for(let i of lib){
        if(i.id == id){
            i.reader = req.body.reader;
            i.returnDate = req.body.date;
            i.isAvailable = "-"; // isAvailable = +/-
            //req.session.message = "Reader " + i.reader + " is added";
            res.redirect('/lib/' + i.id);
            return;
        }
    }

});

router.post('/lib/return/:num', (req, res)=>{
    let id = req.params.num;
    for(let i of lib){
        if(i.id == id){
            i.reader = "-";
            i.returnDate = "-";
            i.isAvailable = "+"; // isAvailable = +/-
            res.redirect('/lib/' + i.id);
            return;
        }
    }
})

router.post('/lib/new/:num', (req, res)=>{
   let id = req.params.num;
   for(let i of lib){
      if(i.id == req.body.id){
          res.redirect('/lib/' + i.id);
          return;
      }
   }

   lib.push({
       "id": id,
       "author": req.body.author,
       "date": req.body.releaseDate,
       "title": req.body.title,
       "isAvailable": "+",
       "reader": "-",
       "returnDate": "-"
   });

    res.redirect('/lib');

});

router.post('/lib/edit/:num', (req, res)=>{
    let id = req.params.num;
    for(let i of lib){
        if(i.id == id){
            i.title = req.body.title;
            i.author = req.body.author;
            i.date = req.body.date;
            i.isAvailable = req.body.isAvailable;
            i.reader = req.body.reader;
            i.returnDate = req.body.returnDate;
            res.redirect('/lib/' + i.id);
            return;
        }
    }

});

router.post('/lib/delete/:num', (req, res)=>{
   let id =  req.params.num;
   lib.forEach((v,i)=> { // v элемент; i - его индекс
       if(v.id == id){
           lib.splice(i, 1);
           res.redirect('/lib');
       }
   });  // выполняет указанную функцию один раз для каждого элемента в массиве
});




module.exports = router;