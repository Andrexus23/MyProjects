export default class View{
    static colors = {
        '1': 'blue',
        '2': 'cyan',
        '3': 'orange',
        '4': 'green',
        '5': 'yellow',
        '6': 'purple',
        '7': 'red'
    };

    constructor(elem, width, height, rows, cols){
        this.element = elem;
        this.width = width;
        this.height = height;
        this.currentPlayer = localStorage.getItem("name");
        this.cns = document.getElementById("panel"); // создаём холст и заполняем его поля для панели
        this.ctx = this.cns.getContext('2d');
        this.cns.width = 300;
        this.cns.height = 400;

        this.canvas = document.getElementById("field_canvas"); // создаём холст и заполняем его поля
        this.context = this.canvas.getContext('2d');
        this.canvas.width = this.width;
        this.canvas.height = this.height;
        this.fieldBorderWidth = 3;
        this.feieldX = this.fieldBorderWidth;
        this.fieldY = this.fieldBorderWidth;
        this.fieldWidth = this.width; // ширина стакана 320; высота стакана 640.
        this.fieldHeight = this.height;

        this.fieldInnerWidth = this.fieldWidth - this.fieldBorderWidth*2;
        this.fieldInnerHeight = this.fieldHeight - this.fieldBorderWidth*2;

        this.blockWidth = this.fieldInnerWidth / cols;
        this.blockHeight = this.fieldInnerHeight / rows;



       // this.element.appendChild(this.canvas); // добавляем в элемент (элемент - корневой элемент) холст

    }


    visualizeMainScreen(state){ // отображение игрового поля
        // нужно стереть предыдущую фигуру
       this.clearScreen(); // очистить холст
       this.visualizeField(state.field); // отобразить холст
       this.visualizePanel(state.level, state.score, state.lines, state.nextFigure);
    }

    clearScreen(){
        this.context.clearRect(0, 0, this.width, this.height); // очищаем ВЕСЬ холст
        this.ctx.clearRect(0,0, this.cns.width, this.cns.height);
    }

    visualizeInitialScreen(){
        this.context.fillStyle = 'black';
        this.context.font = '18px "Courier New"';
        this.context.textAlign = 'center';
        this.context.textBaseline = 'middle';
        this.context.fillText('Press ENTER to start', this.width/2, this.height/2);
    }

    visualizePauseScreen(){
       // this.context.clearRect(0, 0, this.width, this.height);
       // this.context.strokeRect(0, 0, this.width, this.height);
        this.context.fillStyle = 'rgba(114,114,114,0.60)';
        this.context.fillRect(0,0, this.width, this.height);
        this.context.fillStyle = 'black';
        this.context.font = '18px "Courier New"';
        this.context.textAlign = 'center';
        this.context.textBaseline = 'middle';
        this.context.fillText('Press ENTER to resume', (this.width/2), this.height/2);
    }


    visualizeGameOverScreen(state){
        this.clearScreen();

        this.context.fillStyle = 'black';
        this.context.font = '18px "Courier New"';
        this.context.textAlign = 'center';
        this.context.textBaseline = 'middle';
        this.context.fillText('GAME OVER', this.width/2, this.height/2 - 48);
        this.context.fillText(`Score: ${state.score}`, this.width/2, this.height/2);
        this.context.fillText('Press ENTER to restart', this.width/2, this.height/2 + 48);

    }

    visualizeField(field){
        for(let y = 0; y < field.length; y++){
            const row = field[y];
            for(let x = 0; x < row.length; x++){
                const block = row[x];
                if(block){
                    this.visualizeBlock(
                        this.feieldX + (x*this.blockWidth),
                        this.fieldY + (y*this.blockHeight),
                          this.blockWidth, this.blockHeight,
                          View.colors[block]);
                }

            }
        }
        this.context.strokeStyle = 'black';
        this.context.lineWidth = this.fieldBorderWidth;
        this.context.strokeRect(0,0, this.fieldWidth, this.fieldHeight);
    }

   visualizePanel(level, score, lines, nextFigure){
        this.ctx.textAlign = 'start'; // формат текста по левому краю
        this.ctx.textBaseline = 'top'; // формат текста по верхнему краю
        this.ctx.fillStyle = 'black'; // цвет текста
        this.ctx.font = '14px "Courier New"';
        this.panelX =  0;
        this.panelY = 0;
        this.ctx.fillText(`Player: ${this.currentPlayer}`, this.panelX,  this.panelY);
        this.ctx.fillText(`Level: ${level}`, this.panelX, this.panelY + 20);
        this.ctx.fillText(`Score: ${score}`, this.panelX, this.panelY + 40);
        this.ctx.fillText(`Lines: ${lines}`, this.panelX, this.panelY + 60);
        this.ctx.fillText('Next:', this.panelX, this.panelY + 80);

        for(let y = 0; y < nextFigure.blocks.length; y++){
            for(let x = 0; x < nextFigure.blocks[y].length; x++){
                const block = nextFigure.blocks[y][x];
                if(block){ // рисуем следующий блок
                    this.visualizeNext(this.panelX + (x*this.blockWidth*0.5),
                           this.panelY + 120 + (y*this.blockHeight*0.5),
                        this.blockWidth *0.5,
                        this.blockHeight *0.5,
                        View.colors[block]);
                }
            }
        }
        this.ctx.strokeRect(this.panelX, this.panelY+100, this.blockWidth*2, this.blockHeight*2.5)

    }

    visualizeNext(x, y, width, height, color){
        this.ctx.fillStyle = color; // цвет заливки
        this.ctx.lineWidth = 2; // толщина 2 пикселя
        this.ctx.strokeStyle = 'black';
        this.ctx.fillRect(x, y, width, height); // x, y - левый верхний угол прямоугольника
        this.ctx.strokeRect(x,y,width, height);
    }

    visualizeBlock(x, y, width, height, color){
        this.context.fillStyle = color; // цвет заливки
        this.context.lineWidth = 2; // толщина 2 пикселя
        this.context.strokeStyle = 'black';
        this.context.fillRect(x, y, width, height); // x, y - левый верхний угол прямоугольника
        this.context.strokeRect(x,y,width, height);
    }


}
