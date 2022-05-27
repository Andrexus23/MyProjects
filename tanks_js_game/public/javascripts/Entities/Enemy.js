

var Enemy = Entity.extend({
    lifetime: 50,
    move_x: 1,
    move_y: 0,
    speed: 2,
    killed: false,
    direction: 1,
    NewX: 368,
    NewY: 16,
    pos_x: 368,
    pos_y: 16,
    draw: function (ctx) {
        switch (this.direction) {
            case 1:
                spriteManager.drawSprite(ctx, "enemy_right", this.pos_x, this.pos_y);
                break;
            case -1:
                spriteManager.drawSprite(ctx, "enemy_left", this.pos_x, this.pos_y);
                break;
            case 2:
                spriteManager.drawSprite(ctx, "enemy_down", this.pos_x, this.pos_y);
                break;
            case -2:
                spriteManager.drawSprite(ctx, "enemy_up", this.pos_x, this.pos_y);
                break;
            default:
                break;
        }
    },
    update() {
       // console.log(this.move_x + ", " + this.move_y);
        physicsManager.update(this);
    },
    kill() {
        this.killed = true;
        gameManager.kill(this);
       // console.log("Enemy killed");
        //soundManager.play("/audio/enemy_death_sound.mp3");
    },
    fire: function () {
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
        //console.log("Создан объект: " + r.name +
          //  " (" + r.move_x + r.move_y + ")");
        gameManager.entities.push(r);
        //soundManager.play('audio/shot.mp3');
    },
    onTouchMap() {
        this.direction = this.direction *-1;
        this.move_x = this.move_x * -1;
       // this.move_y = this.move_y*-1;

    },
    onTouchEntity(obj) {
        if(obj.type === "Player"){
            obj.kill();
        }
    }
});
