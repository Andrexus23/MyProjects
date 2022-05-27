function store() {
    var input = document.getElementById("input");
    var name = input.value;
    if(name !== ""){
        localStorage.setItem("name", name); // устанавливвает введённое имя в local
        window.location.href = ("./main.html"); // переходит по ссылке и загружает окно игры после регистрации
    }else{
        window.alert("Please enter who you are...");
    }

}

function setName() {
    if(localStorage.hasOwnProperty("name")){
        let name = localStorage.getItem("name");
        let input = document.getElementById("input");
        input.value = name;
    }
}