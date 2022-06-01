#include <thread>
#include "UnboundedQ.h"
#include "BoundedQ.h"

#define N 5
#define NUM_ARTICLES 5
#define BOUNDED 3
#define DONE "DONE"
#define SPORTS "SPORTS"
#define NEWS "NEWS"
#define WHETHER "WHETHER"

using namespace std;


string typeArticle[3] = {SPORTS, NEWS, WHETHER};

vector<BoundedQ> producers;
UnboundedQ SportsQ = UnboundedQ();
UnboundedQ NewsQ = UnboundedQ();
UnboundedQ WhetherQ = UnboundedQ();
BoundedQ CoPQ = BoundedQ(BOUNDED * 3);


void createProducerBoundedQ(int num, int bounded) {
    for (int i = 0; i < num; ++i) {
        auto newBQ = BoundedQ(bounded);
        producers.push_back(newBQ);
    }
}

void addProducerArticle(int id, string typeArt, int counter) {
    string s = "Producer " + to_string(id) + " " + typeArt + " " + to_string(counter);
    cout << s << endl;
    producers.at(id).insert(s);
}

void Producer(int id, int numberArticles) {
    int cSport = 0, cNews = 0, cWhether = 0;
    for (int i = 0; i < numberArticles; ++i) {
        string typeArt = typeArticle[rand() % 3];
        if (typeArt == SPORTS) {
            cSport++;
            addProducerArticle(id, typeArt, cSport);
        }
        if (typeArt == NEWS) {
            cNews++;
            addProducerArticle(id, typeArt, cNews);
        } else {
            cWhether++;
            addProducerArticle(id, typeArt, cWhether);
        }
    }
    producers.at(id).insert(DONE);
}

bool checkIfAllProducersEmpty() {
    for (int i = 0; i < N; ++i) {
        if (!producers[i].isEmpty()) {
            return false;
        }
    }
    return true;
}

void Dispatcher() {
    int count = 0;
    string s;
    while (1) {
        if (!checkIfAllProducersEmpty()) {
            for (int i = 0; i < N; ++i) {
                if (producers[i].isEmpty()) {
                    continue;
                }
                s = "";
                s = producers[i].remove();
                if (s.find(SPORTS) != std::string::npos) {
                    SportsQ.insert(s);
                    cout << "Inserted to the  “S dispatcher queue”" << endl;
                } else if (s.find(NEWS) != std::string::npos) {
                    NewsQ.insert(s);
                    cout << "Inserted to the  “N dispatcher queue”" << endl;
                } else if (s.find(WHETHER) != std::string::npos) {
                    WhetherQ.insert(s);
                    cout << "Inserted to the  “W dispatcher queue”" << endl;
                } else if (s == DONE) {
                    producers[i].emptyDone();
                }
            }
        }
        else{
            SportsQ.insert(DONE);
            NewsQ.insert(DONE);
            WhetherQ.insert(DONE);
            cout<<DONE<<"\n\n\n\n";
            break;
        }
    }
}

void CoEditors(int id) {
    cout << "My CoEditors id is " << id << endl;
}


void ScreenManager() {
    cout << "My ScreenManager" << endl;
}


int main() {
    createProducerBoundedQ(N, BOUNDED);
    vector<thread> tProducers = vector<thread>();
    for (int i = 0; i < N; ++i) {
        thread t(Producer, i, NUM_ARTICLES);
        tProducers.push_back(move(t));
    }
    thread dispatcher(Dispatcher);
    thread coEditors1(CoEditors, 1);
    thread coEditors2(CoEditors, 2);
    thread coEditors3(CoEditors, 3);
    thread screenManager(ScreenManager);
    for (int i = 0; i < N; ++i) {
        tProducers[i].join();
    }
    dispatcher.join();
    coEditors1.join();
    coEditors2.join();
    coEditors3.join();
    screenManager.join();
    return 0;
}
