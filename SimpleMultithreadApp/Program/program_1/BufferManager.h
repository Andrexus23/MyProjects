#ifndef PROGRAM_1_BUFFERMANAGER_H
#define PROGRAM_1_BUFFERMANAGER_H
#include <iostream>
#include <thread> // для работы с потоками
#include "mutex"
#include "locale"
#include "algorithm"
#include <cstdlib>
#include "unistd.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include "netdb.h"
#include "netinet/in.h"
#include <iostream>
#include "cstring"
#define SERVER_IP "127.0.0.1"
#define PORT 7652
#define BUFFER_SIZE 64

using namespace std;

struct BufferManager{
    BufferManager();
    ~BufferManager();
    static bool valid(string & input);
    bool firstThreadWorks(string & input);
    void secondThreadWorks();
    void clear();
    thread thread1;
    thread thread2;
    mutex mtx;
    string sharedBuffer;
    int sum;
    bool canEnter;
};

#endif //PROGRAM_1_BUFFERMANAGER_H
