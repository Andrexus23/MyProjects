#ifndef PROGRAM_1_CLIENT_H
#define PROGRAM_1_CLIENT_H
#include "BufferManager.h"
#include <csignal>

class Client{
public:
    Client();
    void establishConnection();
    int loop();
    static Client & instance();
    bool serverAvailable();
    ~Client();
private:
    sockaddr_in serverAddress;
    int client = -1;
    BufferManager * bufferManager;

};
#endif //PROGRAM_1_CLIENT_H
