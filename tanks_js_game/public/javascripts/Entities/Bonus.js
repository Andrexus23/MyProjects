var Bonus = Entity.extend({
    pos_x: 0,
    pos_y: 0,
    killed: false,
    draw: function (ctx){
        spriteManager.drawSprite(ctx, "bonus", this.pos_x, this.pos_y);
    }, // прорисовка объекта
    // уничтожение объекта
    kill(){
        this.killed = true;
        gameManager.kill(this);
    },
    update() {
        physicsManager.update(this);
    }
});
