var spriteManager = {
    image: new Image(), // рисунок с объектами
    sprites: [],
    imgLoaded: false, // изображения загружены
    jsonLoaded: false, // json загружен
    loadAtlas(atlasJson, atlasImg) {
       // console.log(atlasJson);
        var request = new XMLHttpRequest();  // подготовить запрос на разбор атласа
        request.onreadystatechange = function (){
            if (request.readyState === 4 && request.status === 200) {
                spriteManager.parseAtlas(request.responseText); // успешно получили атлас
            }
        }
        request.open("GET", atlasJson, true); // асинхронный запрос на разбор атласа
        request.send(); // отправили запрос
        this.loadImg(atlasImg); // загрузка изображения

    },
    loadImg(imgName){ // загрузка изображения
        this.image.onload = function () {
            spriteManager.imgLoaded = true;
        }
            this.image.src = imgName; // путь к изображению
             console.log("Загружен спрайт " + imgName);

    },
    parseAtlas(atlasJSON){
        var atlas = JSON.parse(atlasJSON);
        for(var name in atlas.frames){
            var frame = atlas.frames[name].frame; // получение спрайта и сохранение в frame
            this.sprites.push({name:name, x:frame.x, y:frame.y, w: frame.w, h:frame.h});
        }
        this.jsonLoaded = true; // когда разобрали весь атлас - true
    },
    drawSprite(ctx,name,x, y){ // если изображение не загружено, то повторить запрос через 100 мс

        if(!this.imgLoaded || !this.jsonLoaded){

            setTimeout(function () {
                spriteManager.drawSprite(ctx,name, x, y);
            }, 100);
        }
        else {
            var sprite = this.getSprite(name);
            //console.log(name);
            if (sprite === null) {
                console.error(`Sprite with name: ${name} doesn't exists!`);
                return;
            }

            //
            if(!mapManager.isVisible(x, y, sprite.w , sprite.h))
                return;

            x-=mapManager.view.x;
            y-=mapManager.view.y;
            // сдвиг координат, тк координаты спрайта передаются относительно карты, а не относительно видимой части карты.
            ctx.drawImage(this.image, sprite.x, sprite.y ,sprite.w, sprite.h, x, y, sprite.w, sprite.h);
            // sprite.x, y координаты спрайта относительно атласа
            // sprite.w,h размеры спрайта
        }
    },
    getSprite(name){ // получение спрайта по имени
        for (var i = 0; i < this.sprites.length; i++){
            var s = this.sprites[i];
            if(s.name === name)
                return s;
        }
        return null;
    }


};
