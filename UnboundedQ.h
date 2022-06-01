//
// Created by sagib on 6/1/22.
//

#ifndef EX3_UNBOUNDEDQ_H
#define EX3_UNBOUNDEDQ_H
#include <iostream>
#include <vector>
#include <mutex>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

std::mutex mtxUBQ;
class UnboundedQ{
private:
    std::vector<string> UBQ;
public:
    UnboundedQ();

    ~UnboundedQ(){
        UBQ.clear();
    }

    void insert(string x){
        mtxUBQ.lock();
        UBQ.push_back(x);
        mtxUBQ.unlock();
    }

    string remove(){
        mtxUBQ.lock();
        if(UBQ.empty())
            return nullptr;
        string toReturn = UBQ.at(UBQ.size());
        UBQ.pop_back();
        mtxUBQ.unlock();
        return toReturn;
    }

};
#endif //EX3_UNBOUNDEDQ_H
