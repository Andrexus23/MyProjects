var eventsManager = {
    bind: [],// сопоставление клавиш действиям. Массив bind позволяет при необходимости заменить клавишу действия или использовать несколько клавиш для одного и того же действия
    action: [], // действия. Словарь action в качестве ключа исп-ет строковое поле (код действия), в качестве значения использует true или false - флаги того, надо ли выполнять действие или нет (соответственно)
    setup: function (canvas){
        this.bind[87] = 'up'; // вверх
        this.bind[65] = 'left'; // влево
        this.bind[83] = 'down'; // вниз
        this.bind[68] = 'right'; // вправо
        this.bind[32] = 'fire'; // пробел
        this.bind[13] = 'restart'; // enter заново
        canvas.addEventListener("mousedown", this.onMouseDown);
        canvas.addEventListener("mouseup", this.onMouseUp);
        document.body.addEventListener("keydown", this.onKeyDown);
        document.body.addEventListener("keyup", this.onKeyUp);
    },
    onMouseDown: function (event){
        eventsManager.action["fire"] = true;
        console.log("Fire")
    },
    onMouseUp: function (event){
        eventsManager.action["fire"] = false;
    },
    onKeyDown: function (event){
        var action = eventsManager.bind[event.keyCode];
        if(action){
            eventsManager.action[action] = true;
            //console.log(event.keyCode);
        }
    },
    onKeyUp: function (event){
        var action = eventsManager.bind[event.keyCode];
        if(action){
            eventsManager.action[action] = false;
        }
    }
};
