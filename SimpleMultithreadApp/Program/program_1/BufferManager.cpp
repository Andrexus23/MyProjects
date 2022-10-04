#include "BufferManager.h"

BufferManager::BufferManager(){
}

BufferManager::~BufferManager() {
}

bool BufferManager::valid(string & input){ // проверка, что строка состоит только из цифр и не превышает 64 символа.
    if(input.size() > 64) return false;
    for(char i : input){
        if(!isdigit(i)) return false;
    }
    return true;
}

bool BufferManager::firstThreadWorks(string &input) {
    cout << "Thread 1: Input string:\n";
    getline(cin, input);

    if (input.empty() || (!valid( input))) {
        sharedBuffer = "";
        return false;
    }

    // После проверки строка должна быть отсортирована по убыванию
    std::sort(input.begin(), input.end(), [](char a, char b) { return a > b; });

    //  все элементы, значение которых чётно, заменены на латинские буквы «КВ».
    int inc = 0;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] % 2 == 0) {
            inc++;
        }
    }
    int oldSize = input.size();
    int newSize = input.size() + inc;
    string copy;
    copy.resize(newSize);
    int done = 0;
    for (int i = 0; i < newSize; i++) {
        if (input[i - done] % 2 == 0) {
            copy[i] = 'K';
            copy[i + 1] = 'B';
            i++;
            done++;
        } else copy[i] = input[i - done];
    }
    input.clear();
    sharedBuffer = copy;
    return true;
}

void BufferManager::secondThreadWorks() {

    string copy(sharedBuffer);
    cout << "Thread 2: Shared buffer: " << copy << endl;
    for(auto i : copy){
        if(isdigit(i)){
            int el = (int)i - 48;
            sum += el;
        }
    }
    cout <<  "Thread 2: Total sum: " << sum << endl;
}

void BufferManager::clear() {
    sharedBuffer.clear();
    sum = 0;
}


