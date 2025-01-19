#include "GameClub.h"


GameClub::GameClub(const string filename) {
	this->filename = filename;
};

void GameClub::start() {
	 if (!loadInput(filename)) {
		 throw std::invalid_argument("input error");
	 }

	 cout << timeParserMtoHHMM(startTime) << endl;

	 for (const auto& event : events) {
		 eventHandle(event);
	 }

	 eventClubClose();

	 cout << timeParserMtoHHMM(endTime) << endl;
	 for (auto& table : tables) {
		 cout << table.ID << " " << table.MoneyTime / 60 * cost << " " << timeParserMtoHHMM(table.busyTime) << endl;
	 }
 }

//Выводит имена людей в алфавитном порядке, которые остались в клубе после закрытия
void GameClub::eventClubClose() {
	for (auto it = clients.begin(); it != clients.end(); ) {
		tables[it->second.tableID - 1].busy = false;
		tables[it->second.tableID - 1].MoneyTime += roundToNearestHour(endTime - it->second.sessionStart);
		tables[it->second.tableID - 1].busyTime += (endTime - it->second.sessionStart);
		cout << timeParserMtoHHMM(endTime) << " " << "11" << " " << it->second.name << endl;
		it = clients.erase(it);
	}
}

void GameClub::eventID1(const Event& event){
    if (event.time < startTime) {
            cout << timeParserMtoHHMM(event.time) << " " << "13" << " " << "NotOpenYet" << endl;
            return;
        }
        if (clients.find(event.details[0]) == clients.end()) {
            clients[event.details[0]].name = event.details[0];
        }
        else {
            cout << timeParserMtoHHMM(event.time) << " " << "13" << " " << "YouShallNotPass" << endl;
            return;
        }
}

void GameClub::eventID2(const Event& event) {
    Client* cl = &clients[event.details[0]];
        if (cl->tableID == -1) {
            if (tables[stoi(event.details[1]) - 1].busy == false) {
                cl->sessionStart = event.time;
                cl->tableID = stoi(event.details[1]);
                tables[stoi(event.details[1]) - 1].busy = true;
            }
            else {
                cout << timeParserMtoHHMM(event.time) << " " << "13" << " " << "PlaceIsBusy" << endl;
                return;
            }
        }
        else if (cl->tableID == tables[stoi(event.details[1])].ID) {
            cout << timeParserMtoHHMM(event.time) << " " << "13" << " " << "PlaceIsBusy" << endl;
            return;
        }
        else {
            if (tables[stoi(event.details[1]) - 1].busy == false) {
                cl->sessionStart = event.time;
                tables[cl->tableID - 1].busy = false;
                tables[cl->tableID - 1].MoneyTime += roundToNearestHour(event.time - cl->sessionStart);
                tables[cl->tableID - 1].busyTime += (event.time - cl->sessionStart);
                cl->sessionStart = event.time;
                cl->tableID = stoi(event.details[1]);
                tables[stoi(event.details[1]) - 1].busy = true;
                return;
            }
            else {
                cout << timeParserMtoHHMM(event.time) << " " << "13" << " " << "PlaceIsBusy" << endl;
                return;
            }
    }
}

void GameClub::eventID3(const Event& event){
    for (int i = 0; i < tables.size(); i++) {
            if (tables[i].busy == false) {
                cout << timeParserMtoHHMM(event.time) << " " << "13" << " " << "ICanWaitNoLonger!" << endl;
                return;
            }
            else {
                if (waitingClients.size() > 2 * tableCount) {
                    cout << timeParserMtoHHMM(event.time) << " " << "11" << " " << event.details[0] << endl;
                    return;
                }
                else {
                    waitingClients.push({ event.details[0], -1, -1 });
                    return;
                }
            }

        }
}

void GameClub::eventID4(const Event& event){
     Client* cl = &clients[event.details[0]];
        if (cl->tableID == -1) {
            cout << timeParserMtoHHMM(event.time) << " " << "13" << " " << "ClientUnknown" << endl;
            return;
        }
        if (waitingClients.size())
        {
            Client* queueCl = &clients[waitingClients.front().name];
            queueCl->tableID = cl->tableID;
            queueCl->sessionStart = event.time;
            tables[cl->tableID - 1].MoneyTime += roundToNearestHour(event.time - cl->sessionStart);
            tables[cl->tableID - 1].busyTime += (event.time - cl->sessionStart);
            clients.erase(cl->name);
            cout << timeParserMtoHHMM(event.time) << " " << "12" << " " << queueCl->name << " " << queueCl->tableID << endl;
            waitingClients.pop();
            return;
        }
        else {
            tables[cl->tableID - 1].busy = false;
            tables[cl->tableID - 1].MoneyTime += roundToNearestHour(event.time - cl->sessionStart);
            tables[cl->tableID - 1].busyTime += (event.time - cl->sessionStart);
            clients.erase(cl->name);
            return;
        }
}

void GameClub::eventHandle(const Event& event) {

    cout << timeParserMtoHHMM(event.time) << " " << event.ID;
    for (const auto& detail : event.details) cout << " " << detail;
    cout << endl;

    if (event.ID == 1) {
        eventID1(event);
    }

    else if (clients.find(event.details[0]) == clients.end()) {
        cout << timeParserMtoHHMM(event.time) << " " << "13" << " " << "ClientUnknown" << endl;
        return;
    }

    else if (event.ID == 2) {
        eventID2(event);
    }
    else if (event.ID == 3) {
        eventID3(event);
    }
    else if (event.ID == 4) {
        eventID4(event);
    }
    else {
        cerr << "Unknown event ID: " << event.ID << endl;
    }
    return;
}

bool GameClub::loadInput(string filename) {
    //input file
    ifstream infile(filename);
    if (!infile) {
        cerr << "Failed to open file: " << filename << endl;
        return false;
    }

    string fileline{};
    if (!getline(infile, fileline) || !checktCorrectSring(fileline)) {
        cout << "Invalid input format at line 1 " << "\"" << fileline << "\"" << endl;
        return false;
    }
    tableCount = std::stoi(fileline);
    tables.resize(tableCount);
    for (int i = 0; i < tableCount; ++i) {
        tables[i].ID = i + 1;
    }

    if (!getline(infile, fileline)) {
        cout << "Invalid input format at line 2 " << endl;
        return false;
    }

    bool isValidFormat =
        checktCorrectSring(fileline.substr(0, 2)) &&
        fileline[2] == ':' &&
        checktCorrectSring(fileline.substr(3, 2)) &&
        fileline[5] == ' ' &&
        checktCorrectSring(fileline.substr(6, 2)) &&
        fileline[8] == ':' &&
        checktCorrectSring(fileline.substr(9, 2)) &&
        fileline.size() == 11;

    if (!isValidFormat) {
        cout << "Invalid input format at line 2: \"" << fileline << "\"" << endl;
        return false;
    }

    std::istringstream sstream(fileline);
    string sTime, eTime;
    sstream >> sTime >> eTime;
    startTime = timeParserHHMMtoM(sTime);
    endTime = timeParserHHMMtoM(eTime);


    if (!getline(infile, fileline) || !checktCorrectSring(fileline)) {
        cout << "Invalid input format at line 3: " << "\"" << fileline << "\"" << endl;
        return false;
    }
    cost = stoi(fileline);

    int lineNumber = 4;
    while (getline(infile, fileline)) {
        if (!checktCorrectSring(fileline)) {
            cout << "Invalid input format at line " << lineNumber << ": \"" << fileline << "\"" << endl;
            return false;
        }
        istringstream eventStream(fileline);
        string time;
        int id;
        if (!(eventStream >> time >> id)) {
            cout << "Invalid input format at line " << lineNumber << endl;
            return false;
        }

        vector<string> details;
        string detail;
        while (eventStream >> detail) {
            details.push_back(detail);
        }
        events.push_back({ timeParserHHMMtoM(time), id, details });
        ++lineNumber;
    }
    return true;
}

bool GameClub::checktCorrectSring(const std::string& str) {
    for (char ch : str) {
        if (!((ch >= 'a' && ch <= 'z') ||
            (ch >= '0' && ch <= '9') ||
            ch == '_' ||
            ch == '-' ||
            ch == ' ' ||
            ch == ':')) {
            return false;
        }
    }
    return true; 
}