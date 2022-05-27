var physicsManager = {

    update: function (obj){
       // console.log(obj.name + ": " + obj.pos_x + ", "+ obj.pos_y + "(" +
     //   obj.move_x + ", " + obj.move_y + ")");

        switch (obj.type){
            case 'Player':
            case 'Enemy':
                if (obj.move_x === -1) {
                    obj.direction = -1;
                }
                if (obj.move_x === 1) {
                    obj.direction = 1;
                }
                if (obj.move_y === -1) {
                    obj.direction = -2;
                }
                if (obj.move_y === 1) {
                    obj.direction = 2;
                }

                if (obj.move_x === 0 && obj.move_y === 0) {
                    //console.log("stop");
                    return "stop";
                }
                break;
            default:
                break;
        }

        if (obj.move_x === 0 && obj.move_y === 0) {
            return "stop"; // нулевая скорость движения
        }

        var newX = obj.pos_x + Math.floor(obj.move_x * obj.speed);
        var newY = obj.pos_y + Math.floor(obj.move_y * obj.speed);

        var tileset = this.checkMove(obj, newX, newY);
        var buf_x = newX;
        var buf_y =newY;
        var i = 0;
        var j = 0;

        if(tileset !== EMPTY_ID) {
            if (obj.pos_x < newX) {
                for (i = newX; i >= obj.pos_x; i--) {
                    tileset = this.checkMove(obj, i, obj.pos_y);
                    if(tileset !== EMPTY_ID){
                       newX = i+1;
                       break;
                    }
                }
            } else{
                for (i = newX; i < obj.pos_x; i++) {
                    tileset = this.checkMove(obj, i, obj.pos_y);
                    if(tileset !== EMPTY_ID){
                        newX = i-1;
                        break;
                    }
                }
            }

            if(obj.pos_y < newY){
                for (i = newY; i >= obj.pos_y; i--) {
                    tileset = this.checkMove(obj, obj.pos_x, i);
                    if(tileset !== EMPTY_ID){
                        newY = i+1;
                        break;
                    }
                }
            } else{
                for (i = newY; i < obj.pos_y; i++) {
                    tileset = this.checkMove(obj, obj.pos_x, i);
                    if(tileset !== EMPTY_ID){
                        newY = i-1;
                        break;
                    }
                }
            }
        }

       // console.log("newX: " +newX);

        var entity = this.entityAtXY(obj, newX, newY);

        if (entity !== null && obj.onTouchEntity) { // на пути сущность
            obj.onTouchEntity(entity);
        }
        if(tileset !== EMPTY_ID && obj.onTouchMap) // обработка столкновения с картой (стена)
            obj.onTouchMap(tileset);


        if(tileset === EMPTY_ID){ // всё чисто => можно двигаться дальше
            obj.pos_x =  newX;
            obj.pos_y = newY;
        }
        return "move";
    },
    entityAtXY: function (obj, x, y){ // поиск объекта по координатам (а именно определение столкновения с объектом по данным координатам)
        for(var i = 0; i < gameManager.entities.length; i++){
            var e = gameManager.entities[i]; // все объекты карты
            if(e.name !== obj.name){ // имя не совпадает (имена уникальны)
                if(x + obj.size_x < e.pos_x || // не пересекаются
                    y + obj.size_y < e.pos_y ||
                    x > e.pos_x + e.size_x ||
                    y > e.pos_y + e.size_y)
                    continue;
                return e;
            }
        }
        return null;
    },

    checkMove(obj, x, y){

        //console.log(obj.type + ":" + obj.size_x + ": " + obj.size_y);
        let tileset = mapManager.getTilesetIdx(x, y); // говорит нам тип блока, у которого  координаты левого верхнего
        // угла таковы

      //   console.log("   Левый верхний "  + tileset + " (" + x + " ," +y + ")");

        if(tileset === EMPTY_ID) {
            tileset = mapManager.getTilesetIdx(x + obj.size_x, y + obj.size_y);
           // console.log("   Правый нижний "  + tileset + " (" + (x + obj.size_x) + " ," + (y + obj.size_y) + ")");
        }
        if(tileset === EMPTY_ID) {
            tileset = mapManager.getTilesetIdx(x + obj.size_x, y);
          // console.log("   Правый верхний "  + tileset + " (" + (x + obj.size_x) + " ," + y + ")");
        }

        if(tileset === EMPTY_ID){
            tileset = mapManager.getTilesetIdx(x, y + obj.size_y);
        //    console.log("   Левый нижний "  + tileset + " (" + x  + " ," + (y + obj.size_y) +")");
        }


        return tileset;
    }
};
