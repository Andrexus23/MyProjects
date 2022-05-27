

function startGame(){
    gameManager.initGame();
}

var gameManager = {
    name: null,
    factory: {}, // фабрика объектов, которая используется в функции parseEntities менеджера карты
    entities: [],
    sounds: [],
    score: 0,
    fireNum: 0,
    player: null,
    laterKill: [],
    levels: [],
    canvas: null,
    ctx: null,
    currentLevel: 0,
    scoreElement: undefined,
    hpElement: undefined,
    infoElement: undefined,
    infoBlock: undefined,
    canvasBlock: undefined,
    intervalMain: null,
    intervalFire: null,
    infoBlockTimeout: null,

    initGame: function () {
        this.canvas = document.getElementById("canvasId");
        this.scoreElement = document.getElementById("score");
        this.hpElement = document.getElementById("hp");
        this.infoElement = document.getElementById("gameInfo");
        this.infoBlock = document.getElementById("gameInfoBlock");
        this.canvasBlock = document.getElementById("canvasBlock");
        this.ctx = this.canvas.getContext('2d');
        this.levels = ["levels/level_1.json", "levels/level_2.json"];
        this.sounds = [ 'audio/shot_sound.mp3',
        'audio/get_bonus_sound.mp3', 'audio/victory_sound.mp3', 'audio/game_over.mp3', 'audio/enemy_death.mp3'];
        soundManager.init();
        soundManager.loadArray(this.sounds);
        mapManager.loadMap(this.levels[this.currentLevel]);
        console.log("Начало игры")
        mapManager.xCount = 40; // ширина карты в блоках (количество блоков по горизонтали)
        mapManager.yCount = 20; // высота карты в блоках
        mapManager.tSize = {x: 16, y: 16}; // объект, содержащий размеры по ширине и высоте
        mapManager.view = {x: 0, y: 0, w: 672, h: 352};

        spriteManager.loadAtlas("levels/sprites.json", "levels/spritesheet.png");
        gameManager.factory['Player'] = Player;
        gameManager.factory['Enemy'] = Enemy;
        gameManager.factory['Bullet'] = Bullet;
        gameManager.factory['Bonus'] = Bonus;
        gameManager.factory['Mine'] = Mine;
        mapManager.parseEntities();
        eventsManager.setup(this.canvas);
        this.play();
    },

    update() {
        //console.log("update");
        if (this.player === null) {

            return;
        }

        this.player.move_x = 0; // по умолчанию игрок никуда не двигается
        this.player.move_y = 0;

        // поймали событие - обрабатываем
        if (eventsManager.action["up"]) {
            this.player.move_x = 0;
            this.player.move_y = -1;
        }
        if (eventsManager.action["down"]) {
            //console.log("Движение вниз");
            this.player.move_x = 0;
            this.player.move_y = 1;
        }
        if (eventsManager.action["left"]) {
            this.player.move_y = 0;
            this.player.move_x = -1;
        }
        if (eventsManager.action["right"]) {
            this.player.move_y = 0;
            this.player.move_x = 1;
        }

        if (eventsManager.action["fire"]) {
            this.player.fire();
            eventsManager.action["fire"] = false;
         }


        this.entities.forEach(function (event) {
            try {
                event.update();
            } catch (ex) {
                //console.log(ex)
            }
        });
        // удаление всех объектов, попавших в laterKill
        for (var i = 0; i < this.laterKill.length; i++) {
            var idx = this.entities.indexOf(this.laterKill[i]);
            if (idx > -1) {
                this.entities.splice(idx, 1); // удаление из массива 1 объекта
            }
        }
        if (this.laterKill.length > 0) // очистка массива laterKill
        {

            this.laterKill.length = 0;
        }

        if (this.player === null) {
            return;
        }

        mapManager.centerAt(this.player.pos_x, this.player.pos_y);
        this.draw(this.ctx);
    },

    play() {
            this.intervalMain = setInterval(updateWorld, 50);
            this.intervalEnemy = setInterval(enemyFire, 1000);
            console.log("Интервалы установлены")

    },

    kill: function (obj) {
        this.laterKill.push(obj);
        // console.log("add " + obj.name + " to the death list");
        if(obj.type === "Enemy")
            soundManager.play("audio/enemy_death.mp3");
        if(obj.type === "Player"){
            soundManager.play("audio/game_over.mp3");
            this.clearIntervals();
            this.showLabel(`
                    Вы проиграли!<br>
                    Ваше количество очков:
                    <span>${this.score}</span>
                    <br>
                    Нажмите ENTER, чтобы начать игру заново`);
            this.infoBlock.style.display = "block";
            this.canvasBlock.style.display = "none";
            let self = this;
            let restart = setInterval(function () {
                if (eventsManager.action["restart"]) {
                    console.log(self.intervalMain);
                    clearInterval(restart);
                    self.infoBlock.style.display = "none";
                    self.canvasBlock.style.display = "block";
                    self.restart();
                }
            }, 100);

        }
    },

    draw() {
        mapManager.draw(this.ctx);
        for (let e = 0; e < this.entities.length; e++) {
            //  console.log("Отрисовка" + this.entities[e].name + ": " + this.entities[e].pos_x + "," + this.entities[e].pos_y);
            this.entities[e].draw(this.ctx);
        }
    },
    addScore(number) {
        this.score += number;
        this.scoreElement.innerHTML = this.score;
    },


    initPlayer: function (obj) {
         console.log("initPlayer")
        this.player = obj;
         console.log(this.player)
    },

    nextLevel: function () {
        this.clearIntervals();
        this.entities = [];
        this.currentLevel++;
        this.player = null;

        if (this.currentLevel === this.levels.length) {
                    soundManager.play("audio/victory_sound.mp3")
                    let name = prompt("Введите  имя: ");

                    this.updateTable(name, this.score);
                    this.clearIntervals();
                    this.showLabel(`
                    Вы выиграли!<br>
                    Ваше количество очков:
                    <span>${this.score}</span>
                    <br>
                    Нажмите ENTER, чтобы начать игру заново
                    <br>
                    Нажмите ПРОБЕЛ, чтобы увидеть таблицу рекордов`);

                    this.currentLevel = -1;
                    let self = this;

                    eventsManager["fire"] = false;
                    eventsManager["restart"] = false;

                    let makeChoice = setInterval(function () {
                        if (eventsManager.action["restart"]) {
                            console.log(self.intervalMain);
                                clearInterval(makeChoice);
                                self.infoBlock.style.display = "none";
                                self.canvasBlock.style.display = "block";
                                self.restart();
                            }
                        if (eventsManager.action["fire"]) {
                            window.location.href += "table/";

                        }
                    }, 100);
            return;
        }
        mapManager.reset();
        mapManager.loadMap(this.levels[this.currentLevel]);
        mapManager.parseEntities();
        console.log(this.player);
        this.play();
    },

    updateTable(name, score) { // асинхронный запрос на обновление таблицы рекордов
        let request = new XMLHttpRequest();
        request.onreadystatechange = function () {
            if (request.readyState === 4 && request.status === 200) {

            }
        };
        request.open("PUT", `/?name=${name}&record=${score}`, true);
        // Метод PUT подразумевает, что мы передаём всё, что нужно в URL. Тела запроса нет.
        request.send();
    },

    showLabel(text){ // отображение информацию
        this.canvasBlock.style.display = "none";
        this.infoBlock.style.display = "block";
        this.infoElement.innerHTML = text;
    },

    restart(){
        this.entities = [];
        this.player = null;
        this.currentLevel = 0;
        this.addScore(-this.score);
        mapManager.reset();
        mapManager.loadMap(this.levels[this.currentLevel]);
        mapManager.parseEntities();
        console.log(this.player);

        eventsManager.action["up"] = false;
        eventsManager.action["down"] = false;
        eventsManager.action["right"] = false;
        eventsManager.action["left"] = false;
        eventsManager.action["restart"] = false;
        eventsManager.action["fire"] = false;
        this.play();
    },

    clearIntervals(){
      clearInterval(this.intervalMain);
      clearInterval(this.intervalEnemy);

        console.log("Интервалы стерты")
        this.intervalMain = null;
        this.intervalEnemy = null;
    }

}


function updateWorld(){
    gameManager.update();
}

function enemyFire(){ // устанавливает периодичность выстрела врага раз в 1 секунду
    gameManager.entities.forEach(function (event) {
        try {
            if(event.type === "Enemy"){
                event.fire();
            }
        } catch (ex) {
            //console.log(ex)
        }
    });
}







