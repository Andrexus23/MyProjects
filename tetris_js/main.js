import Game from './src/game.js';
import View from "./src/view.js";
import GameController from "./src/GameController.js";
const root = document.querySelector("#root");

const game = new Game(); // Game должен передавать в View состояние игрового поля
const view = new View(root, 320, 640, 20, 10);
//const view = new View(root, 320, 640, 20, 10);
const controller = new GameController(game, view);

window.game = game; // после установки game как глобальной переменной в браузере можно получить доступ к объекту game
window.view = view;
window.contoller = controller;


//console.log(game);







