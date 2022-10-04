#include "Server.h"

Server::Server() {

}

Server::~Server() {

}

void Server::establishConnection() {
    client = socket(AF_INET, SOCK_STREAM, 0);
    if(client < 0){
        std::cout << "ERROR: cannot establish socket\n";
        exit(0);
    }else{
        cout << "Socket established. Waiting for client connection...\n";
    }
    serverAddress.sin_port = htons(PORT); // Поле sin_port содержит номер порта который намерен занять процесс.
    serverAddress.sin_family = AF_INET; // Значение поля sin_family всегда равно AF_INET.
    serverAddress.sin_addr.s_addr = htons(INADDR_ANY);

    int ret = bind(client, reinterpret_cast<sockaddr*> (&serverAddress), sizeof(serverAddress));
    // После создания сокета функция привязки связывает сокет с адресом и номером порта, указанными в addr

    if(ret < 0){ // если результат функции привязки отрицательный, значит связать процесс клиента с процессом сервера не удалось.
        std::cout << ERROR_S << "binding connection. Socket has already been established\n";
        return;
    }
    // если сокет клиента удалось связать с адресом сервера, то начинаем слушать клиентов
    int size = sizeof (serverAddress);
//    std::cout << "SERVER: Listening clients...\n";
    listen(client, 1);
    // используется сервером для принятия связи на сокет.
    server = accept(client, reinterpret_cast<sockaddr*>(&serverAddress), reinterpret_cast<socklen_t *>(&size));
    // если к ip по нашему порту было обращение с другого сокета, то мы производим accept, т.е. связываем эти 2 сокета, сокет сервер и сокет клиент.
    // чтобы они могли взаимодействовать между собой. Для этого
    if(server < 0){
        std::cout << ERROR_S << "Can't accepting client\n";
    }
    // пока соединение установлено, мы будем получать информацию из него.
}

bool Server::checkBuffer(const char *msg) {
    int i = 0;
    while(msg[i] != '\0'){
        i++;
    }
    cout << "----Check----\n";
    cout << "Number: " <<  std::atoi(msg) << endl;
    cout << "Count of symbols: " << i << endl;
    int inted = std::atoi(msg);
    if((i > 2) && (inted % 32 == 0)){
        cout << "The number can be divided into 32\n";
        cout << "-----OK------\n";
        return true;
    }
    cout << "The number can't be divided by 32\n";
    cout << "----ERROR----\n\n";
    return false;
}



void Server::loop() {
    establishConnection();

    char buffer[BUFFER_SIZE];
    bool isExit = false;
    if(server > 0){
        strcpy(buffer, "Server connected\0");
        send(server, buffer, BUFFER_SIZE, 0);
        memset(buffer, '\0', sizeof(buffer));
        cout << "Connected to the client\n";
        recv(server, buffer, BUFFER_SIZE, 0);

        isExit = false;

        while (!isExit){ // флажок.
            if(checkBuffer(buffer)){
                std::cout << "Got message from client: ";
                std::cout << buffer << std::endl;
            }
            while(!recv(server, buffer, BUFFER_SIZE, 0)){
                retryConnection();
                std::cout << "Connection established. Connected to the client\n";
            }
        }
        std::cout << "\n End of connection.\n" << endl; // пишем на стороне сервера gb и завершаем приложение
        isExit = false;
        exit(1);
    }
    close(server);
}

bool Server::retryConnection() {
    close(client);
    close(server);
    establishConnection();
    char buffer[BUFFER_SIZE];
    strcpy(buffer, "Server connected\n");
    send(server, buffer, BUFFER_SIZE, 0);
    return true;
}
