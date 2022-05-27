

var Player = Entity.extend({
    lifetime: 100,
    move_x: 0,
    move_y: 0,
    speed: 4,
    direction: 1,
    NewX: 0,
    NewY: 0,
    pos_x: 0,
    pos_y: 0,
    draw: function (ctx){ // рисуем Player
        //console.log("Рисуем")
        switch (this.direction) {
            case 1:
                spriteManager.drawSprite(ctx, "player_right", this.pos_x, this.pos_y);
                break;
            case -1:
                spriteManager.drawSprite(ctx, "player_left", this.pos_x, this.pos_y);
                break;
            case 2:
                spriteManager.drawSprite(ctx, "player_down", this.pos_x, this.pos_y);
                break;
            case -2:
                spriteManager.drawSprite(ctx, "player_up", this.pos_x, this.pos_y);
                break;
            default:
                break;
        }

    },
    fire: function (){ // выстрел
        var r = Object.create(Bullet);
        r.direction = this.direction;
        r.size_x = 14;
        r.size_y = 14;
        r.type = "Bullet";
        r.name = "" + (++gameManager.fireNum);
        r.move_x = this.move_x;
        r.move_y = this.move_y;
       // console.log("fire");
        switch (this.move_x + 2*this.move_y){
            case -1: // появиться слева от игрока
                r.pos_x = this.pos_x - r.size_x/2;
                r.pos_y = this.pos_y;
                break;
            case 1: // появиться справа от игрока
                r.pos_x = this.pos_x + r.size_x/2;
                r.pos_y = this.pos_y;
                break;
            case -2:
                r.pos_x = this.pos_x;
                r.pos_y = this.pos_y - this.size_y/2; // появиться сверху от игрока
                break;
            case 2:
                r.pos_x = this.pos_x;
                r.pos_y = this.pos_y + this.size_y/2; // появиться снизу от игрока
                break;
            default:
                return;
        }
        console.log("Создан объект: " + r.name +
        " (" + r.move_x + r.move_y + ")");
        gameManager.entities.push(r);
        soundManager.play('audio/shot_sound.mp3');
    },
    kill() {
        this.killed = true;
       // soundManager.play('audio/game_over.mp3');
        gameManager.kill(this);

    },
    update: function (){
        //console.log("Вызов менеджера физики")
        gameManager.hpElement.innerHTML = this.lifetime;
        physicsManager.update(this);
    },
    onTouchMap(ts){
        if(ts === EXIT_ID){
            gameManager.nextLevel();

        }
    },

    onTouchEntity(obj){ // при контакте с бонусом - собираем
        if (obj.type === "Bonus") {
            //this.gameManager.soundsManager.playSound("bonus");
            gameManager.addScore(50);
            soundManager.play("audio/get_bonus_sound.mp3")
            obj.kill();
        }
        if (obj.type === "Enemy") {
            // умираем либо когда 0 хп, либо при прямом контакте с врагом или миной
            this.kill();
        }
        if(obj.type === "Mine"){
            console.log("Мина")
            obj.kill();
            this.kill();
        }
    }
});
