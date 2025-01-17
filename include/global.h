#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;


struct Table {
    int ID = -1;
    bool busy = false;
    int MoneyTime = 0;
    int busyTime = 0;
};

struct Client {
    string name;
    int sessionStart = -1;
    int tableID = -1;
};

struct Event {
    int time = 0;
    int ID = -1;
    vector<string> details;

};

ostream& operator<<(ostream& os, const Event& event) {
    os << "Time: " << event.time << ", Event ID: " << event.ID << ", Details: ";
    for (auto& i : event.details) {
        cout << i << " ";
    }
    return os;
}

int tableCount, startTime, endTime, cost;
vector<Table> tables;
vector<Event> events;
map<string, Client> clients;
queue<Client> waitingClients;