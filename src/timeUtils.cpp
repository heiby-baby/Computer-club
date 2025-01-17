#include "timeUtils.h"

// Format HH:MM to Minutes
int timeParserHHMMtoM(const string& line) {
    int hours = (((int(line[0]) - int('0')) * 10) + (int(line[1]) - int('0')));
    int minuts = (((int(line[3]) - int('0')) * 10) + (int(line[4]) - int('0')));
    return hours * 60 + minuts;
}
// Minutes to HH:MM format
string timeParserMtoHHMM(int minutes) {
    int hours = minutes / 60;
    int minut = minutes % 60;
    return (hours < 10 ? "0" : "") + to_string(hours) + ":" + (minut < 10 ? "0" : "") + to_string(minut);
}

// Rounds up the given time in minutes to the nearest hour
int roundToNearestHour(int minutes) {
    if (minutes % 60 == 0) {
        return minutes;
    }
    return ((minutes / 60) + 1) * 60;
}