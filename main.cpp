#include <thread>
#include "UnboundedQ.h"
#include "BoundedQ.h"

#define N 5
#define BOUNDED 5
using namespace std;


string typeArticle[3] = {"Sports", "News", "Whether"};

vector<BoundedQ *> producers;
UnboundedQ *Sports, *News, *Whether;
BoundedQ *CoPQ = new BoundedQ(BOUNDED * 3);


void createProducerBoundedQ(int num, int bounded) {
    for (int i = 0; i < num; ++i) {
        auto *newBQ = new BoundedQ(bounded);
        producers.push_back(newBQ);
    }
}


struct producerNew {
    int id;
    string typeA = typeArticle[rand() % 3];
    int counter;
};

void Producer(int id) {
    cout << "My Producer id is" << id << endl;
}

void Dispatcher() {
    cout << "My Dispatcher" << endl;
}

void CoEditors(int id) {
    cout << "My CoEditors id is " << id << endl;
}


void ScreenManager() {
    cout << "My ScreenManager" << endl;
}


int main() {
    createProducerBoundedQ(N, BOUNDED);
    thread tProducers[N] = {};
    for (int i = 0; i < N; ++i) {
        tProducers[i] = thread(Producer, i);
    }
    thread dispatcher(Dispatcher);
    thread coEditors1(CoEditors, 1);
    thread coEditors2(CoEditors, 2);
    thread coEditors3(CoEditors, 3);
    thread screenManager(ScreenManager);
    screenManager.join();
    return 0;
}
