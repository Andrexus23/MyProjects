export default class Game{ // класс игры
    constructor() {
        this.reset();
    }

    static pointsMap = {
      '1': 50,
      '2': 100,
      '3': 200,
      '4': 800
    };

    rotateFigure(){ // самая умная реализация
        this.rotateFigCells(); // по умолчанию крутим по часовой стрелке
        if(this.isImpossibleToSetFigureHere()){ // если такой поворот в условиях координат фигуры неккоректен, вращаем обратно против чс
            this.rotateFigCells(false);
        }
    }

    get level(){ // уровень зависит от количества удалённых линий. Уровень повышается каждые 10 линий
       return Math.floor(this.lines * 0.1) + 1;
    }

    rotateFigCells(clockwise = true){ // поворот матрицы как по чс так и против неё
        const blocks = this.activeFigure.blocks;
        const length = blocks.length;
        const x = Math.floor(length/2);
        const y = length  - 1;

        for(let i = 0; i < x; i++){
            for(let j  = i; j < y - i; j++){
                const temp = blocks[i][j];
                if(clockwise) { // по чс
                    blocks[i][j] = blocks[y - j][i];
                    blocks[y - j][i] = blocks[y - i][y - j];
                    blocks[y - i][y - j] = blocks[j][y - i];
                    blocks[j][y - i] = temp;
                }
                else{ // против чс
                    blocks[i][j] = blocks[j][y - i];
                    blocks[j][y - i] = blocks[y - i][y - j];
                    blocks[y - i][y - j] = blocks[y - j][i];
                    blocks[y - j][i] = temp;
                }
            }
        }

    }

    moveDown(){
        if(this.topOut){ // если ставить больше некуда, то всё -> возврат (а этот метод отвечает за генерацию новых фигур и без него
            // updataView не имеет графического смысла )
            return;
        }

        this.activeFigure.y += 1;
        if(this.isImpossibleToSetFigureHere()){
            this.activeFigure.y -= 1;
            this.setFigure(); // установка фигуры
            this.updateScore(this.eraseLines()); // удаление фулл-строк
            this.updateFigures(); // генераaция новой фигуры
        }

        if(this.isImpossibleToSetFigureHere()){
            this.topOut = true;
        }

    }

    moveLeft(){
        this.activeFigure.x -= 1;
        if(this.isImpossibleToSetFigureHere()){
            this.activeFigure.x += 1;
        }
    }


    moveRight(){
        this.activeFigure.x += 1;
        if(this.isImpossibleToSetFigureHere()){
            this.activeFigure.x -= 1;
        }
    }


    isImpossibleToSetFigureHere(){ // проверка на выход за границу диапазона и на свободность ячейки
        const {
            x: figureX,
            y: figureY,
            blocks
        } = this.activeFigure;
        for(let y = 0; y < blocks.length; y++){
            for (let x = 0; x < blocks[y].length; x++){
                // проверяем, выходит ли за границы диапазона ячейка с координатами левого верхнего угла формы
                // + сдвиг начиная с 0 до размера рамки формы
                // также в последней части условия сделана проверка - занята ли данная ячейка другой фигурой ?
                if((blocks[y][x]) &&
                    (
                        (this.field[figureY + y] === undefined || this.field[figureY + y][figureX + x] === undefined) ||
                        (this.field[figureY + y][figureX + x])
                    ))
                    return true;
            }
        }
        return false;
    }

    reset(){ // полностью стирает все данные
        this.score = 0;
        this.lines = 0;
        this.topOut = false;
        this.field = this.createField();
        this.activeFigure = this.createFigure();
        this.nextFigure = this.createFigure();
    }

    setFigure(){ //  позволяет скопировать значения активной фигуры на карту
        const blocks = this.activeFigure.blocks;
        for(let y = 0; y < this.activeFigure.blocks.length; y++){
            for(let x = 0; x < this.activeFigure.blocks[y].length; x++){
                if(blocks[y][x]){
                    /* нули копироваться не будут (+исключает возможность ошибки
                    когда функция проверки за границы диапазона вернёт true (то есть саму фигуру поставить можно) но при этом всю матрицу фигуры - нет */
                    this.field[this.activeFigure.y + y][this.activeFigure.x + x] = blocks[y][x];
                }
            }
        }
    }

    eraseLines(){ // метод, стирающий линии. Будет вызываться в moveDown если линии. Метод возвращает количество удалённых линий
        const rows = 20;
        const cols = 10;
        let lines = [];
        for(let y = rows - 1; y >=0; y--){
            let blocksCount = 0;
            for(let x = 0; x < cols; x++){
                if(this.field[y][x]){
                    blocksCount++;
                }
            }
            if(blocksCount === 0){
                break;
            }
            else if(blocksCount < cols) {
                continue;
            }else if(blocksCount === cols){
                lines.unshift(y); // если вся строка заполнена фигурами то отмечаем её, записывая её индекс в специальный массив.
                // важно отметить что индексы строк, которые следует удалить, мы записываем  в начало (push_front)
                // для того чтобы при удалении когда строка с меньшим индексом будет удалена и сверху будет вставлена новая,
                // исключить возможность затеряться другой полной строке (так как индексы поменяются)
                // и если мы будем всегда расстрельные строки вставлять в начало, то при удалении младшей строки перераспределение индексов не
                // коснётся старшей
                }
        }

        for(let index of lines){
            this.field.splice(index, 1); // удаляем 1 массив из стакана начиная с индекса index
            this.field.unshift(new Array(cols).fill(0)); // вставляем сверху в стакан одну пустую строку взамен удалённой
        }
        return lines.length;
    }

    updateScore(erasedLines){
       if(erasedLines > 0){
            this.score += Game.pointsMap[erasedLines]; // очки с каждым уровнем увеличиваются в некоторое количество раз
            this.lines += erasedLines;
        }
    }

    getState() { // позволяет возвращать состояние игрового поля, которое можно передавать в класс View
        const field = this.createField();
        const {y:figY, x:figX, blocks:blocks} = this.activeFigure; // реструктуризация
        for (let y = 0; y < this.field.length; y++) {
            field[y] = [];
            for (let x = 0; x < this.field[y].length; x++) {
                field[y][x] = this.field[y][x];
            }
        } // скопировали значение поля

        for (let y = 0; y < this.activeFigure.blocks.length; y++) { // теперь копируем фигуру
            for (let x = 0; x < this.activeFigure.blocks[y].length; x++) {
                if (this.activeFigure.blocks[y][x]) {
                    field[figY + y][figX + x] = blocks[y][x];
                }
            }
        }

        return {
            score: this.score,
            level: this.level,
            lines: this.lines,
            nextFigure: this.nextFigure,
            field,
            gameOver: this.topOut
        };
    }


    createField(){ // метод, позволяющий создать копию игрового поля
        const field = [];
        for(let y = 0; y < 20; y++){
            field[y] = [];
            for(let x = 0; x < 10; x++){
                field[y][x] = 0;
            }
        }
        return field;

    }

    createFigure(){ // генерация рандомным образом одной из 7 фигур
        const ind = Math.floor(Math.random()*7);
        const figureShape = 'JILOZST'[ind];
        const figure = {};
        switch (figureShape){
            case 'I':
                figure.blocks = [
                    [1,1,1,1],
                    [0,0,0,0],
                    [0,0,0,0],
                    [0,0,0,0]
                ];
                break;
            case 'J':
                figure.blocks = [
                    [2,2,2],
                    [0,0,2],
                    [0,0,0]

                ];
                break;
            case 'O':
                figure.blocks = [
                    [0,3,3,0],
                    [0,3,3,0],
                    [0,0,0,0],
                    [0,0,0,0]
                ];
                break;
            case 'L':
                figure.blocks = [
                    [4,4,4],
                    [4,0,0],
                    [0,0,0]
                ];
                break;
            case 'Z':
                figure.blocks = [
                    [5,5,0],
                    [0,5,5],
                    [0,0,0]
                ];
                break;
            case 'S':
                figure.blocks = [
                    [0,6,6],
                    [6,6,0],
                    [0,0,0]
                ];
                break;
            case 'T':
                figure.blocks = [
                    [7,7,7],
                    [0,7,0],
                    [0,0,0]
                ];
                break;
            default:
                throw new Error('Неизвестный тип');

        }

        figure.x = Math.floor((10 - figure.blocks[0].length)/2);
        figure.y = 0;

        return figure;
    }


    updateFigures(){
        this.activeFigure = this.nextFigure;
        this.nextFigure = this.createFigure();
    }
}