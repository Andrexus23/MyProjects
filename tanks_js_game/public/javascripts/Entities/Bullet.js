var Bullet = Entity.extend({
    move_x: 0,
    move_y: 0,
    speed: 12,
    direction: 0,
    NewX: 0,
    damage: 50,
    NewY: 0,
    size_x: 4,
    size_y: 4,
    killed: false,
    draw(ctx){
        spriteManager.drawSprite(ctx, "bullet", this.pos_x, this.pos_y);

    },
    update(){
        physicsManager.update(this);
    },
    onTouchEntity: function(aim){
        if (aim !== null){
            if(aim.type === "Enemy" || aim.type === "Player"){
                aim.lifetime -= this.damage;
               // console.log(aim.name + ":" + aim.lifetime + " left");
                if(aim.lifetime <= 0) {
                    aim.kill();
                }
            }
            if(aim.type === "Mine") aim.kill();
           // console.log("bullet " + this.move_x + "," + this.move_y + " killed" );
            this.kill();
        }

    },
    onTouchMap: function (idx){
        this.kill();
    },
    kill: function (){
        this.killed = true;
        gameManager.kill(this);
    }
});
