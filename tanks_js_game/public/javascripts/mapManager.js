const EMPTY_ID = 22;
const EXIT_ID = 243;
const WALL_ID = 42;

var mapManager = {
    mapData: null, // переменная для хранения карты (JSON)
    tLayer: null, // json с типом tilelayer или массив таких объектов
    xCount: 40, // ширина карты в блоках (количество блоков по горизонтали)
    yCount: 20, // высота карты в блоках
    tSize: {x:16, y:16}, // объект, содержащий размеры по ширине и высоте
    mapSize: {x:0, y:0},
    tilesets: [], // массив блоков карты в каждом из которых хранятся описания для каждого блока карты
    imgLoadCount: 0, // количество загруженных изображений
    imgLoaded: false, // все изображения загружены
    jsonLoaded: false, // json описание загружено
    view: {x:0, y:0, w: 672, h:352}, // видимая область с координатами левого верхнего угла
    mapConfig: null,

    loadMap(path){
        var request = new XMLHttpRequest(); //
        request.onreadystatechange = function (){ // функция onreadystatechange автоматически вызывается после отправки запроса
            if(request.readyState === 4 && request.status === 200){ // corr answer, can process res
                console.log(request.responseText)
                mapManager.parseMap(request.responseText); // responseText хранит текст, полученный с сервера


            }
        };

      //  console.log("SEND " + path);
        request.open("GET",  path, true);

        request.send();
        console.log("SEND " + path);
    },

    parseMap(tilesJSON){
        this.mapData = JSON.parse(tilesJSON); // разобрать json
        this.xCount = this.mapData.width; // сохранение ширины
        this.yCount = this.mapData.height; // сохранение высоты
        this.tSize.x = this.mapData.tilewidth; // сохранение размера блока
        this.tSize.y = this.mapData.tileheight;
        this.mapSize.x = this.xCount*this.tSize.x; // вычисление размера карты
        this.mapSize.y = this.yCount*this.tSize.y; // вычисление размера карты
        for(let i = 0; i < this.mapData.tilesets.length; i++){
            var img = new Image(); // создаём переменную для хранения изображений
            img.onload = function (){ // при загрузке изображения
                mapManager.imgLoadCount++; // увеличиваем счётчик
                if(mapManager.imgLoadCount === mapManager.mapData.tilesets.length){ // тройное равенство означает сравнение с учетом типа объекта
                    mapManager.imgLoaded = true; // загружены все изображения
                }
            };
            img.src = 'http://localhost:3000/levels/' + this.mapData.tilesets[i].image; // задание пути к изображению
            var t = this.mapData.tilesets[i]; // забираем tileset из карты
            var ts = {
                firstgid: t.firstgid, // c него начинается нумерация в storage
                image: img,
                name: t.name, // имя элемента рисунка
                xCount: Math.floor(t.imagewidth/mapManager.tSize.x), // горизонталь
                yCount: Math.floor(t.imageheight/mapManager.tSize.y), // вертикаль
            };
            this.tilesets.push(ts); // сохраняем tileset в массив
        } // end for
        this.jsonLoaded = true; // true, когда разобрали весь json
        /*  Функция parseMap должна быть объявлена в рамках
          mapManager */
    },
    draw(ctx){ // Функция draw предназначена для отображения карты на холсте

        if(!mapManager.imgLoaded || !mapManager.jsonLoaded){
            setTimeout(function (){mapManager.draw(ctx);}, 100); // если карта не загружена, то повторить прорисовку через 100 мс
        }else{
            if(this.tLayer === null) {
                for (var id = 0; id < this.mapData.layers.length; id++) { // обход всех слоёв map
                    var layer = this.mapData.layers[id];
                    if (layer.type === "tilelayer") {
                        // если не tilelayer - пропускаем
                        this.tLayer = layer;
                        break;
                    }
                }
            }

            ctx.clearRect(this.view.x, this.view.y, this.view.w, this.view.h);
            for(var i = 0; i < this.tLayer.data.length; i++){
                if(this.tLayer.data[i] !== 0){ // если нет данных - пропускаем
                    var tile = this.getTile(this.tLayer.data[i]); // получение блока по индексу
                    var pX = (i % this.xCount)*this.tSize.x; // Вычисляет x в пикселях
                    var pY = Math.floor(i/this.xCount)*this.tSize.y; // вычисляем y

                    if(!this.isVisible(pX, pY, this.tSize.x, this.tSize.y)) continue; // не рисуем за пределами видимой зоны
                    pX -= this.view.x; // сдвигаем видимую зону
                    pY -= this.view.y;
                    ctx.drawImage(tile.img, tile.px, tile.py, this.tSize.x,this.tSize.y, pX, pY, this.tSize.x, this.tSize.y);
                }
            }
        }
    },
    isVisible(x, y, width, height){
        if(x+width < this.view.x || y + height < this.view.y || x > this.view.x+this.view.w || y > this.view.y + this.view.h)
            return false;
        return true;
    },
    getTile(tileIndex){ // индекс блока
        var tile = {
            img: null, // изображение tileset
            px: 0, py: 0 // координаты блока в tileset
        };
        /* Переменная tileIndex хранит номер блока в общем маcсиве storage*/
        var tileset = this.getTileset(tileIndex);
        tile.img = tileset.image; // Выполняет копирование ссылки на изображение в новый объект tile.
        var id = tileIndex - tileset.firstgid; // индекс блока в tileset
        var x = id % tileset.xCount; // округление от деления на xCount даёт x в tileset
        var y = Math.floor(id/tileset.xCount);
        tile.px = x*mapManager.tSize.x;
        tile.py = y*mapManager.tSize.y;
        return tile;
    },
    getTileset(tileIndex){
        //Создается цикл поиска:
        //Создается цикл поиска:
        for(var i = mapManager.tilesets.length - 1; i >= 0; i--){ // в каждом  tilesets[i].firstgid записано число, с которого начинается нумерация блоков
            if(mapManager.tilesets[i].firstgid <= tileIndex){
                /*
                * Если искомый индекс больше начального номера бло
          ков в tilesets[i], то именно этот набор блоков нужен, он
          возвращается return tileset.*/
                // если индекс первого блока <= искомому -> этот tileset и нужен
                return mapManager.tilesets[i];
            }
        }
        return null;
    },
    parseEntities(){
        if(!mapManager.imgLoaded ||!mapManager.jsonLoaded){
            console.log("чЕ ЗА ХРЕНЬ")
            setTimeout(function () {mapManager.parseEntities();},100);
        }
        else {
            for (var j = 0; j < this.mapData.layers.length; j++) {
                if (this.mapData.layers[j].type === 'objectgroup') {
                    var entities = this.mapData.layers[j];
                    for (var i = 0; i < entities.objects.length; i++) {
                        var e = entities.objects[i];
                        // NewX NewY не используются, но пусть останутся для резерва
                        try {
                            var obj = Object.create(gameManager.factory[e.type]);
                            obj.id = e.id;
                            obj.name = e.name;
                            obj.pos_x = e.x;
                            obj.type = e.type;
                            obj.pos_y = e.y;
                            obj.NewX = e.x;
                            obj.NewY = e.y;
                            obj.size_x = e.width;
                            obj.size_y = e.height;
                            if(obj !== null) gameManager.entities.push(obj);

                            if (obj.name  === "player") {
                                gameManager.initPlayer(obj);
                                console.log("Игрок инициализирован");
                            }
                        } catch (ex) {
                            console.log("Ошибка создания: [" + e.gid + "]" + e.type + "," + ex)
                        }
                    }
                }
            }
        }
    },
    getTilesetIdx(x,y){
        var wX = x;
        var wY = y;
        var idx = Math.floor(wY / this.tSize.y) * this.xCount + Math.floor(wX / this.tSize.x);
        return this.tLayer.data[idx]
    },
    centerAt(x,y){
        /*Функция centerAt предназначена для центрирования
        области mapManager.view относительно положения игрока (x, y).*/
        if (x < this.view.w / 2)
            this.view.x = 0;
        else if(x > this.mapSize.x - this.view.w / 2)
            this.view.x = this.mapSize.x - this.view.w;
        else
            this.view.x = x - (this.view.w / 2)

        if (y < this.view.h / 2)
            this.view.y = 0;
        else if(y > this.mapSize.y - this.view.h / 2)
            this.view.y = this.mapSize.y - this.view.h;
        else
            this.view.y = y - (this.view.h / 2)
    },
    reset(){
        this.mapData= null; // переменная для хранения карты (JSON)
        this.tLayer =null; // json с типом tilelayer или массив таких объектов
        this.xCount = 20; // ширина карты в блоках (количество блоков по горизонтали)
        this.yCount =  20; // высота карты в блоках
        this.tSize = {x:16, y:16}; // объект, содержащий размеры по ширине и высоте
        this.mapSize = {x:16, y:16};
        this.tilesets= []; // массив блоков карты в каждом из которых хранятся описания для каждого блока карты
        this.imgLoadCount= 0; // количество загруженных изображений
        this.imgLoaded = false; // все изображения загружены
        this.jsonLoaded =  false; // json описание загружено
        this.view = {x:0, y:0, w:672, h:352}; // видимая область с координатами левого верхнего угла
        this.mapConfig = null;

    }
}
