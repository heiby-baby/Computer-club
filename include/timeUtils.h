#pragma once
#include <string>
#include <stdexcept>
using namespace std;


// Format HH:MM to Minutes
int timeParserHHMMtoM(const string&);


// Minutes to HH:MM format
string timeParserMtoHHMM(int);


// Rounds up the given time in minutes to the nearest hour
int roundToNearestHour(int);