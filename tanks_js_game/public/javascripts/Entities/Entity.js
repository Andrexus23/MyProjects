var Entity ={
    pos_x: 0, // позиция
    pos_y: 0,
    size_x: 0, // размеры
    size_y: 0,
    type: "",
    id: 0,
    extend: function (extendProto){ // расширение сущности Создается новая переменная object, в которую копируются все поля и функции Entity.
        var object = Object.create(this); // создание нового объекта
        for(var property in extendProto){ // для всех свойств нового объекта
            if(this.hasOwnProperty(property) || typeof object[property] === 'undefined'){
                object[property] = extendProto[property];
            }
        }
        /*Значение поля или функции с именем property копируется из extendProperty в object.*/
        return object;
    }
}

