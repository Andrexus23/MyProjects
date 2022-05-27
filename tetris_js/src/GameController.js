export default class GameController {
    constructor(game, view) {
        this.game = game;
        this.view = view;
        this.areWePlaying = false;
        this.intervalId = null;
        document.addEventListener('keydown', this.handleKeyDown.bind(this));
        document.addEventListener('keyup', this.handleKeyUp.bind(this));
        this.playList = [];
        this.name = localStorage.getItem("name");
        this.view.visualizeInitialScreen();
        this.showExistingTable();
    }

    updateGame(){
        this.game.moveDown();
        this.updateView();
    }

    updateView(){
        const curState = this.game.getState();
        if(curState.gameOver){
            this.view.visualizeGameOverScreen(curState);
        }
        else  if (!this.areWePlaying) {
            this.view.visualizePauseScreen();
        }
        else{
            this.view.visualizeMainScreen(curState);
        }
    }

    play(){
        this.areWePlaying = true;
        this.startTimer();
        this.updateView();
    }



    pause(){
        this.areWePlaying = false;
        this.stopTimer();
        this.updateView();
    }

    startTimer(){
        // изменение скорости игры в зависимости от уровня
        const speed = (1000 - this.game.getState().level*100);

        if(!this.intervalId) {
            this.intervalId = setInterval(() => {
                this.updateGame();
            }, speed > 0 ? speed : 100); // вызываем метод moveDown с интервалои 1 с
            // макс v = 100 мс. (0 быть не может)
        }


    }

    stopTimer(){
        if(this.intervalId)
            clearInterval(this.intervalId);
        this.intervalId = null;
    }

    handleKeyDown(event)
    {
        const state = this.game.getState();

        switch (event.keyCode) {
            case 13: // enter
                if(state.gameOver){
                    this.reset();
                }
                else if(this.areWePlaying) {
                   this.pause();
                }else{
                    this.play();
                }
                console.log('Событие keydown: ' + 'ENTER');
                break;
            case 37: // левая стрелка
                this.game.moveLeft();
                this.updateView();
                console.log('Событие keydown: ' + 'ArrowLeft');
                break;
            case 38: // верхняя
                this.game.rotateFigure();
                this.updateView();
                console.log('Событие keydown: ' + 'ArrowUp');
                break;
            case 39: // правая
                this.game.moveRight();
                this.updateView();
                console.log('Событие keydown: ' + 'ArrowRight');

                break;
            case 40: // нижняя
                this.stopTimer();
                this.game.moveDown();
                this.updateView();
                break;
        }
    }

    reset(){
        let curScore = game.score;
        this.game.reset();
        this.updateTable(curScore);
        this.play();
    }

    handleKeyUp(event){
        switch (event.keyCode) {
            case 40: // НИЖНЯЯ СТРЕЛКА
                this.startTimer();
                console.log('Событие keyup: ' + 'ArrowDown');
                break;
        }
    }

    updateTable(curScore){

        if(localStorage.hasOwnProperty('records')){
            this.playList = JSON.parse(localStorage.getItem('records'));
            this.playList.push({name: localStorage.getItem("name"), score: curScore});
            this.playList.sort(function (a,b) {
                return b.score - a.score;
            });

            while(this.playList.length>5){
                this.playList.pop();
            }

            localStorage.setItem('records', JSON.stringify(this.playList));
        }
        else{
            this.playList = [];
            this.playList.push({name:this.name, score: curScore});
            localStorage.setItem('records', JSON.stringify(this.playList));
        }
        this.showTable();
    }

    showTable(){
        var table = '<table class="simple-little-table">';
        for( var i = 0; i < this.playList.length; i++ ){
            table += '<tr>';
            table += '<td>' + (Number(i)+1) +'</td>';
            table += '<td>' + this.playList[i].name +'</td>';
            table += '<td>' + this.playList[i].score +'</td>';
            table += '</tr>';
        }
        table += '</table>';
        document.getElementById('table_div').innerHTML = '<h2>Records table</h2>';
        document.getElementById('table_div').innerHTML += table;
        document.getElementById('table_div').innerHTML+='<button id="button" onclick="window.location=\'index.html\'">На стартовую страницу</button>';
}

    showExistingTable(){
        if(localStorage.hasOwnProperty('records')) {
            this.playList = JSON.parse(localStorage.getItem('records'));
            localStorage.setItem('records', JSON.stringify(this.playList));
        }
        else{
            this.playList = [];
            localStorage.setItem('records', JSON.stringify(this.playList));
        }
        this.showTable();
    }
}

