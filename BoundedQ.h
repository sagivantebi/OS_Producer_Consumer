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
#include <thread>
#include <pthread.h>
#include <string>
#include <queue>


using namespace std;


class BoundedQ {
private:
    queue<string> BQ;
    sem_t empty;
    sem_t full;
    pthread_mutex_t mtxBQ;
    bool done;
public:
    BoundedQ(int bounded) {
        this->done = false;
        this->BQ = queue<string>();
        sem_init(&(this->empty), 0, bounded);
        sem_init(&(this->full), 0, 0);
        pthread_mutex_init(&mtxBQ, NULL);
    }

    void insert(string x) {
        sem_wait(&empty);
        pthread_mutex_lock(&mtxBQ);
        BQ.push(x);
        pthread_mutex_unlock(&mtxBQ);
        sem_post(&full);
    }

    string remove() {
        sem_wait(&full);
        pthread_mutex_lock(&mtxBQ);
        string toReturn = BQ.front();
        BQ.pop();
        pthread_mutex_unlock(&mtxBQ);
        sem_post(&empty);
        return toReturn;
    }

    void emptyDone(){
        this->done = true;
    }
    bool isEmpty(){
        return this->done;
    }

};

#endif //EX3_BOUNDEDQ_H
