#include "timeUtils.h"
// Format HH:MM to Minutes
int timeParserHHMMtoM(const string& line) {
    if (line.size() != 5 || line[2] != ':') {
        throw std::invalid_argument("Invalid time format.");
    }

    int hours = (line[0] - '0') * 10 + (line[1] - '0');
    int minutes = (line[3] - '0') * 10 + (line[4] - '0');
    
    if (hours < 0 || hours >= 24 || minutes < 0 || minutes >= 60) {
        throw std::invalid_argument("Invalid time values.");
    }

    return hours * 60 + minutes;
}

// Minutes to HH:MM format
string timeParserMtoHHMM(int minutes) {
    if (minutes < 0 || minutes >= 24 * 60) {
        throw std::invalid_argument("Invalid minutes value. Must be between 0 and 1439.");
    }

    int hours = minutes / 60;
    int mins = minutes % 60;
    return (hours < 10 ? "0" : "") + to_string(hours) + ":" + (mins < 10 ? "0" : "") + to_string(mins);
}

int roundToNearestHour(int minutes) {
    if (minutes % 60 == 0) {
        return minutes;
    }
    return ((minutes / 60) + 1) * 60;
}