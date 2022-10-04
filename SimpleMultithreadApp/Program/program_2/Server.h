#ifndef PROGRAM_2_SERVER_H
#define PROGRAM_2_SERVER_H

#include <iostream>
#include "cstring"
#include "cstdlib"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"
#include "thread"
#include "chrono"
#define PORT 7652
#define ERROR_S "SERVER ERROR: "
#define BUFFER_SIZE 129
#define CLOSE_CONNECTION_SYMBOL '#'

using namespace std;

class Server{
public:
    Server();
    ~Server();
    void establishConnection();
    void loop();
    bool retryConnection();
    static bool checkBuffer(const char* msg);
private:
    int client = -1; // дескрипторы клиента и сервера
    int server = -1;
    sockaddr_in serverAddress;

};
#endif //PROGRAM_2_SERVER_H
