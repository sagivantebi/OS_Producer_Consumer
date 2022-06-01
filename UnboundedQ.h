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
#include <thread>
#include <pthread.h>
#include <queue>

using namespace std;

class UnboundedQ {
private:
    bool done;
    queue<string> UBQ;
    pthread_mutex_t mtxUBQ;
    sem_t full;
public:
    UnboundedQ() {
        done = false;
        UBQ = queue<string>();
        pthread_mutex_init(&mtxUBQ, NULL);
        sem_init(&(this->full), 0, 0);
    }

    void insert(string x) {
        pthread_mutex_lock(&mtxUBQ);
        UBQ.push(x);
        pthread_mutex_unlock(&mtxUBQ);
        sem_post(&full);
    }

    string remove() {
        sem_wait(&full);
        pthread_mutex_lock(&mtxUBQ);
        string toReturn = UBQ.front();
        UBQ.pop();
        pthread_mutex_unlock(&mtxUBQ);
        return toReturn;
    }

    void emptyDone(){
        this->done = true;
    }
    bool isEmpty(){
        return this->done;
    }

};

#endif //EX3_UNBOUNDEDQ_H
