//Author: Sagiv Antebi

#include "UnboundedQ.h"
#include "BoundedQ.h"
#include <fstream>

#define N 3
#define BOUNDED 1
#define DONE "DONE"
#define SPORTS "SPORTS"
#define NEWS "NEWS"
#define WHETHER "WHETHER"

using namespace std;

struct producerArgs {
    int id;
    int numArticles;
    int boundedProducer;
};

vector<BoundedQ> producers;
UnboundedQ SportsQ = UnboundedQ();
UnboundedQ NewsQ = UnboundedQ();
UnboundedQ WhetherQ = UnboundedQ();
BoundedQ CoPQ = BoundedQ(BOUNDED);
sem_t fullCoPQ;

void Producer(int id, int numberArticles) {
    string s;
    int cSport = 0, cNews = 0, cWhether = 0;
    int typeArt;
    int i;
    for (i = 0; i < numberArticles; ++i) {
        typeArt = rand() % 3;
        if (typeArt == 0) {
            s = "Producer " + to_string(id + 1) + " " + SPORTS + " " + to_string(cSport);
            producers[id].insert(s);
            cSport++;
        } else if (typeArt == 1) {
            s = "Producer " + to_string(id + 1) + " " + NEWS + " " + to_string(cNews);
            producers[id].insert(s);
            cNews++;
        } else {
            s = "Producer " + to_string(id + 1) + " " + WHETHER + " " + to_string(cWhether);
            producers[id].insert(s);
            cWhether++;
        }
    }
    producers[id].insert(DONE);
}


void Dispatcher() {
    string sDisp;
    int i;
    bool allEmpty = false;
    while (!allEmpty) {
        for (i = 0; i < N; ++i) {
            if (!producers[i].isEmpty()) {
                break;
            }
            allEmpty = true;
        }
        if (!allEmpty) {
            for (i = 0; i < N; ++i) {
                if (!producers[i].isEmpty()) {
                    sDisp = producers[i].remove();
                    if (sDisp.find(SPORTS) != std::string::npos) {
                        SportsQ.insert(sDisp);
                    } else if (sDisp.find(NEWS) != std::string::npos) {
                        NewsQ.insert(sDisp);
                    } else if (sDisp.find(WHETHER) != std::string::npos) {
                        WhetherQ.insert(sDisp);
                    } else if (sDisp == DONE) {
                        producers[i].emptyDone();
                    }
                }
            }
        }
    }
    SportsQ.insert(DONE);
    NewsQ.insert(DONE);
    WhetherQ.insert(DONE);
}

void CoEditors(int id) {
    switch (id) {
        case 1: {
            string s1;
            s1 = SportsQ.remove();
            while (!SportsQ.isEmpty()) {
                CoPQ.insert(s1);
                s1 = SportsQ.remove();
                if (s1 == DONE)
                    SportsQ.emptyDone();
            }
            CoPQ.insert(DONE);
            break;
        }
        case 2: {
            string s2;
            s2 = NewsQ.remove();
            while (!NewsQ.isEmpty()) {
                CoPQ.insert(s2);
                s2 = NewsQ.remove();
                if (s2 == DONE)
                    NewsQ.emptyDone();
            }
            CoPQ.insert(DONE);
            break;
        }
        case 3: {
            string s3;
            s3 = WhetherQ.remove();
            while (!WhetherQ.isEmpty()) {
                CoPQ.insert(s3);
                s3 = WhetherQ.remove();
                if (s3 == DONE)
                    WhetherQ.emptyDone();
            }
            CoPQ.insert(DONE);
            break;
        }
        default:
            cout << "default" << endl;
    }
}


void ScreenManager() {
    string sScreenManager;
    int num;
    sScreenManager = CoPQ.remove();
    while (!CoPQ.isEmpty()) {
        if (sScreenManager == DONE) {
            sem_wait(&fullCoPQ);
            sem_getvalue(&fullCoPQ, &num);
            if (num == 0) {
                CoPQ.emptyDone();
                break;
            }
        } else
            cout << sScreenManager << endl;
        sScreenManager = CoPQ.remove();
    }
}


vector<producerArgs> readConfig(char *path) {
    string myConfig;
    vector<producerArgs> vProducers;
    string id, numArticles, boundedProducers, boundedCoEditors, newLine;
    bool reading = true;
    ifstream f(path);
    getline(f, myConfig);
    while (f) {
        getline(f, id);
        getline(f, numArticles);
        getline(f, boundedProducers);
        getline(f, newLine);
        if (equal(numArticles.begin(), numArticles.end(), "")) {
            CoPQ = BoundedQ(stoi(id));
        } else {
            producerArgs p{stoi(id), stoi(numArticles), stoi(boundedProducers)};
            vProducers.push_back(p);
        }
        id.clear();
        numArticles.clear();
        boundedProducers.clear();
    }
    f.close();
    return vProducers;
}

int main(int argc, char *argv[]) {
    vector<thread> tProducers = vector<thread>();
    int i, j;
    vector<producerArgs> vProducers = readConfig(argv[1]);
    sem_init(&fullCoPQ, 0, vProducers.size());
    for (auto &it: vProducers) {
        auto newBQ = BoundedQ((it.boundedProducer));
        producers.push_back(newBQ);
        thread t(Producer, it.id - 1, it.numArticles);
        tProducers.push_back(move(t));
    }
    thread dispatcher(Dispatcher);
    thread coEditors1(CoEditors, 1);
    thread coEditors2(CoEditors, 2);
    thread coEditors3(CoEditors, 3);
    thread screenManager(ScreenManager);
    //waiting for the threads to finish
    for (i = 0; i < N; ++i) {
        tProducers[i].join();
    }
    dispatcher.join();
    coEditors1.join();
    coEditors2.join();
    coEditors3.join();
    screenManager.join();
    return 0;
}
