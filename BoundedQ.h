//
// Created by sagib on 6/1/22.
//

#ifndef EX3_BOUNDEDQ_H
#define EX3_BOUNDEDQ_H
#include <iostream>
#include <vector>
#include <mutex>
#include <semaphore.h>
#include <unistd.h>



using namespace std;



std::mutex mtxBQ;
class BoundedQ {
private:
    std::vector<string> BQ;
    sem_t empty;
    sem_t full;
public:
    BoundedQ(int bounded) {
        sem_init(&(this->empty), 0, bounded);
        sem_init(&(this->full), 0, 0);
    }

    ~BoundedQ() {
        BQ.clear();
    }


    void insert(string x) {
        sem_wait(&empty);
        mtxBQ.lock();
        BQ.push_back(x);
        mtxBQ.unlock();
        sleep(0.1);
        sem_post(&full);
    }

    string remove() {
        sem_wait(&full);
        mtxBQ.lock();
        if (BQ.empty())
            return nullptr;
        string toReturn = BQ.at(BQ.size());
        BQ.pop_back();
        mtxBQ.unlock();
        sem_post(&empty);
        sleep(0.1);
        return toReturn;
    }

};
#endif //EX3_BOUNDEDQ_H
