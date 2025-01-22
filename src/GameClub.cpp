#include "GameClub.h"

GameClub::GameClub(const string filename) : filename(filename) {};

void GameClub::start()
{
    if (!loadInput(filename))
    {
        throw invalid_argument("input error");
    }

    cout << timeParserMtoHHMM(startTime) << endl;

    for (const auto& event : events)
    {
        eventHandle(event);
    }

    eventClubClose();

    cout << timeParserMtoHHMM(endTime) << endl;
    for (auto& table : tables)
    {
        cout << table.ID << " " << table.MoneyTime / 60 * cost << " " << timeParserMtoHHMM(table.busyTime) << endl;
    }
}

// Выводит имена людей в алфавитном порядке, которые остались в клубе после закрытия
void GameClub::eventClubClose()
{
    for (auto it = clients.begin(); it != clients.end();)
    {
        tables[it->second.tableID - 1].MoneyTime += roundToNearestHour(endTime - it->second.sessionStart);
        tables[it->second.tableID - 1].busyTime += (endTime - it->second.sessionStart);
        cout << timeParserMtoHHMM(endTime) << " " << "11" << " " << it->second.name << endl;
        it = clients.erase(it);
    }
}

void GameClub::eventID1(const Event& event)
{
    if (event.time < startTime)
    {
        cout << timeParserMtoHHMM(event.time) << " " << "13" << " " << "NotOpenYet" << endl;
        return;
    }
    if (clients.find(event.details[0]) != clients.end())
    {
        cout << timeParserMtoHHMM(event.time) << " " << "13" << " " << "YouShallNotPass" << endl;
        return;
    }

    clients[event.details[0]].name = event.details[0];
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

void GameClub::eventID3(const Event& event)
{
    for (int i = 0; i < tables.size(); i++)
    {
        if (tables[i].busy == false)
        {
            cout << timeParserMtoHHMM(event.time) << " " << "13" << " " << "ICanWaitNoLonger!" << endl;
            return;
        }
        else
        {
            if (waitingClients.size() > 2 * tableCount)
            {
                cout << timeParserMtoHHMM(event.time) << " " << "11" << " " << event.details[0] << endl;
                return;
            }
            else
            {
                waitingClients.push({ event.details[0], -1, -1 });
                return;
            }
        }
    }
}

void GameClub::eventID4(const Event& event) {
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

void GameClub::eventHandle(const Event& event)
{

    cout << timeParserMtoHHMM(event.time) << " " << event.ID;
    for (const auto& detail : event.details)
        cout << " " << detail;
    cout << endl;

    if (event.ID == 1)
    {
        eventID1(event);
    }

    else if (clients.find(event.details[0]) == clients.end())
    {
        cout << timeParserMtoHHMM(event.time) << " " << "13" << " " << "ClientUnknown" << endl;
        return;
    }

    else if (event.ID == 2)
    {
        eventID2(event);
    }
    else if (event.ID == 3)
    {
        eventID3(event);
    }
    else if (event.ID == 4)
    {
        eventID4(event);
    }
    else
    {
        cerr << "Unknown event ID: " << event.ID << endl;
    }
    return;
}

// Файл считывает строчки и уже обрабатывает для скорости
bool GameClub::loadInput(string filename)
{
    // input file
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "Failed to open file: " << filename << endl;
        return false;
    }

    string fileline{};
    //Столов не может быть 0
    if (!getline(infile, fileline) || !isDigitsOnly(fileline) || !((fileline[0] - '0') > 0))
    {
        cout << "Invalid input format at line 1 " << "\"" << fileline << "\"" << endl;
        return false;
    }
    // Инициализируем указанное в файле кол-во столов
    tableCount = stoi(fileline);
    tables.resize(tableCount);
    for (int i = 0; i < tableCount; ++i)
    {
        tables[i].ID = i + 1;
    }

    fileline = "";

    // Инициализируем временные переменные
    if (!getline(infile, fileline) || !isValidTimeString(fileline))
    {
        cout << "Invalid input format at line 2: \"" << fileline << "\"" << endl;
        return false;
    }

    istringstream sstream(fileline);
    string sTime, eTime;
    sstream >> sTime >> eTime;
    startTime = timeParserHHMMtoM(sTime);
    endTime = timeParserHHMMtoM(eTime);

    fileline = "";

    if (!getline(infile, fileline) || !isDigitsOnly(fileline) || !((fileline[0] - '0') > 0))
    {
        cout << "Invalid input format at line 3: " << "\"" << fileline << "\"" << endl;
        return false;
    }
    cost = stoi(fileline);

    // Считывание событий
    int lineNumber = 4;
    while (getline(infile, fileline))
    {
        if (!isEventValidFormat(fileline))
        {
            cout << "Invalid input format at line " << lineNumber << ": \"" << fileline << "\"" << endl;
            return false;
        }

        istringstream eventStream(fileline);
        string time;
        int id;
        eventStream >> time >> id;

        vector<string> details;
        string detail;
        while (eventStream >> detail)
        {
            details.push_back(detail);
        }
        events.push_back({ timeParserHHMMtoM(time), id, details });
        ++lineNumber;
    }

    return true;
}

const vector<Event>& GameClub::getEvents() const { return events; };


// XX:XX XX:XX
inline bool GameClub::isValidTimeString(const string& fileline)
{
    if (fileline.size() != 11) return false;

    // Проверка формата XX:XX XX:XX
    if (!isdigit(fileline[0]) || !isdigit(fileline[1]) || fileline[2] != ':' ||
        !isdigit(fileline[3]) || !isdigit(fileline[4]) || fileline[5] != ' ' ||
        !isdigit(fileline[6]) || !isdigit(fileline[7]) || fileline[8] != ':' ||
        !isdigit(fileline[9]) || !isdigit(fileline[10])) {
        return false;
    }

    // Извлечение первого времени (часы и минуты)
    int hours1 = (fileline[0] - '0') * 10 + (fileline[1] - '0');
    int minutes1 = (fileline[3] - '0') * 10 + (fileline[4] - '0');

    // Извлечение второго времени (часы и минуты)
    int hours2 = (fileline[6] - '0') * 10 + (fileline[7] - '0');
    int minutes2 = (fileline[9] - '0') * 10 + (fileline[10] - '0');

    // Проверка валидности обоих блоков времени
    return (hours1 >= 0 && hours1 <= 23) && (minutes1 >= 0 && minutes1 <= 59) &&
        (hours2 >= 0 && hours2 <= 23) && (minutes2 >= 0 && minutes2 <= 59);
}

inline bool GameClub::isDigitsOnly(const string& input)
{
    if (input == "") return false;

    for (char c : input)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

// Для проверкии ввода событий
// ^\d{2}:\d{2} \d+ [a-z0-9_-]+ \d+$ ))
inline  bool GameClub::isEventValidFormat(const string& str)
{
    int len = int(str.size());
    int i = 0;
    // Проверка времени вначале
    if (len < 5 || !isdigit(str[i]) || !isdigit(str[i + 1]) || str[i + 2] != ':' ||
        !isdigit(str[i + 3]) || !isdigit(str[i + 4]))
    {
        return false;
    }
    i += 5;
    // Проверка пробела между временем и айди события
    if (i >= len || str[i] != ' ')
        return false;
    i++;

    // Проверка числа между временем и текстом
    if (i >= len || !isdigit(str[i]))
        return false;
    while (i < len && isdigit(str[i]))
        i++;

    // Проверка пробела между айди события и именем клиента
    if (i >= len || str[i] != ' ')
        return false;
    i++; 

    if (i >= len || !(islower(str[i]) || isdigit(str[i]) || str[i] == '-' || str[i] == '_'))
        return false;

    while (i < len && (islower(str[i]) || isdigit(str[i]) || str[i] == '-' || str[i] == '_'))
        i++;

    if (i >= len || str[i] != ' ')
        return i == len;
    i++;

    while (i < len && isdigit(str[i]))
        i++;
    return i == len;
}
