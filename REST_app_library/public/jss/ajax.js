function showAll (button){ // показываем тупо всё
    let id = button.id;
    sendGetQueryAjax(id, (res)=>{
        let arrJSON = JSON.parse(res);
        for (id of arrJSON){
            (document.getElementById(id)).style.visibility = "visible";
        }
    });
}

function showAvailable(button){ // прячем всё что взято: в res должны быть взятые книги
    let id = button.id;
    sendGetQueryAjax(id, (res)=>{
        let arrJSON = JSON.parse(res);
        for (id of arrJSON){
            (document.getElementById(id)).style.visibility = "hidden";
        }
    });
}

function showTaken(button){ // в res должны быть либо просроченные либо не взятые
    let id = button.id;
    sendGetQueryAjax(id, (res)=>{
        let arrJSON = JSON.parse(res);
        for (id of arrJSON){
            (document.getElementById(id)).style.visibility = "hidden";
        }
    });
}

function showExpired(button){ // прячем всё что в библиотеке, либо взято и не ещё не просрочено
    let id = button.id;
    sendGetQueryAjax(id, (res)=>{
        let arrJSON = JSON.parse(res);
        for (id of arrJSON){
            (document.getElementById(id)).style.visibility = "hidden";
        }
    });
}



function  sendGetQueryAjax(id, callback) {
    let xhttp = new XMLHttpRequest(); // Класс XMLHttpRequest позволяет отправлять асинхронные запросы на сервер
        xhttp.onreadystatechange = function () { //вызывается при изменении состояния обработки запроса
        if(this.readyState === 4 && this.status === 200) // означает, что обработка запроса успешно завершена
            callback(this.responseText); // вызывается в тот момент, когда успешно получен результат запроса
    };
    xhttp.open("GET",`/lib/${id}`,true); // 1-ый арг - использованный метод; 2-ой - URL,
    // по которому отправляется запрос, 3-ий - признак что запросы должен обрабатываться асинхронно (формируем запрос)
    xhttp.send(); // отправляем запрос
}

