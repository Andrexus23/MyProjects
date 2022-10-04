#include "Client.h"

Client::Client() {
    bufferManager = new BufferManager;
    establishConnection();
}

Client::~Client() {
    delete bufferManager;
}

void Client::establishConnection(){
    if(client >= 0) close(client);
    client = socket(AF_INET, SOCK_STREAM, 0);
    if(client < 0){
        cout << "ERROR: cannot establish socket\n";
        exit(0);
    } else{
        cout << "Socket successfully established\n";
    }
    serverAddress.sin_port = htons(PORT); // Поле sin_port содержит номер порта который намерен занять процесс.
    serverAddress.sin_family = AF_INET; // Значение поля sin_family всегда равно AF_INET.
    // Данная функция преобразует строку символов src в сетевой адрес (типа af), затем копирует полученную структуру с адресом в dst.
    inet_pton(AF_INET, SERVER_IP, &(serverAddress.sin_addr));

    int ret = 1;
    while(ret != 0){
        std::cout << "Trying to establish connection\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        ret = connect(
                client,
                reinterpret_cast<const sockaddr *>(&serverAddress),
                sizeof(serverAddress));
    }
    std::cout << "Connection to server " << inet_ntoa(serverAddress.sin_addr)
              << " with port number: " << PORT << std::endl;

    char buffer[BUFFER_SIZE];
    std::cout << "Waiting for server confirmation...\n";
    recv(client, buffer, BUFFER_SIZE,0);
    cout << buffer << endl;
    std::cout << "Connection established\n";

}

int Client::loop() {
    bufferManager->canEnter = false;
    bufferManager->thread1 = thread([&]() {// все действия первого потока должны быть залочены
        while(true) {
            if(!serverAvailable()) {
                Client::instance().establishConnection();
            }
            unique_lock<mutex> ul(bufferManager->mtx);
            string input;
            while (!bufferManager->firstThreadWorks(input)) { cout << "Incorrect string. Input a string again\n"; };
            ul.unlock();

            while(!bufferManager->canEnter){} // ожидаем
            bufferManager->canEnter = false;
        }
    });

   // важно не допустить ситуации, когда второй поток будет раньше первого

    bufferManager->thread2 = thread([&]() {
        while(true) {
            if(!serverAvailable()) {
                Client::instance().establishConnection();
            }
            if(!(bufferManager->sharedBuffer.empty())) {
                char buffer[BUFFER_SIZE];
                unique_lock<mutex> ul(bufferManager->mtx);
                bufferManager->secondThreadWorks(); // критическая секция для второго потока
                string sum(std::to_string(bufferManager->sum));
                bufferManager->clear();
                ul.unlock();

                bufferManager->canEnter = true;
                std::cout << "Program 1 message: ";
                memcpy(buffer, sum.c_str(), BUFFER_SIZE);
                std::cout << buffer << endl;

                send(client, buffer, BUFFER_SIZE, 0);
            }
        }
    });

    bufferManager->thread1.join();
    bufferManager->thread2.join();

    close(client); // закрываем соединения
    return 0;
}


Client & Client::instance() {
    static Client thisClient;
    return  thisClient;
}



bool Client::serverAvailable() {
    int optval;
    socklen_t optlen = sizeof(optval);
    int res = getsockopt(client ,SOL_SOCKET,SO_ERROR,&optval, &optlen);
    if(optval==0 && res==0) return true;
    cout << "Connection has been interrupted!\n";
    return false;
}


