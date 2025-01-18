#pragma once
#include "timeUtils.h"
#include "global.h"
class GameClub
{
private:
	int tableCount, startTime, endTime, cost;
	vector<Table> tables;
	vector<Event> events;
	map<string, Client> clients;
	queue<Client> waitingClients;
	string filename;
	bool checktCorrectSring(const std::string& str);
    bool loadInput(string);
    void eventHandle(const Event&);
    void eventClubClose();


public:
     GameClub(const string filename);
     void start();

};

