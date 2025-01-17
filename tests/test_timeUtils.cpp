#include <cassert>
#include <iostream>
#include "timeUtils.h"

void test_timeParserHHMMtoM()
{
    assert(timeParserHHMMtoM("00:00") == 0);
    assert(timeParserHHMMtoM("01:30") == 90);
    assert(timeParserHHMMtoM("12:45") == 765);
    assert(timeParserHHMMtoM("23:59") == 1439);
    std::cout << "timeParserHHMMtoM passed all tests.\n";
}

void test_timeParserMtoHHMM()
{
    assert(timeParserMtoHHMM(0) == "00:00");
    assert(timeParserMtoHHMM(90) == "01:30");
    assert(timeParserMtoHHMM(765) == "12:45");
    assert(timeParserMtoHHMM(1439) == "23:59");
    std::cout << "timeParserMtoHHMM passed all tests.\n";
}

void test_roundToNearestHour()
{
    assert(roundToNearestHour(0) == 0);
    assert(roundToNearestHour(1) == 60);
    assert(roundToNearestHour(59) == 60);
    assert(roundToNearestHour(60) == 60);
    assert(roundToNearestHour(61) == 120);
    assert(roundToNearestHour(1439) == 1440);
    std::cout << "roundToNearestHour passed all tests.\n";
}

int main()
{
    std::cout << "Run tests.\n";
    test_timeParserHHMMtoM();
    test_timeParserMtoHHMM();
    test_roundToNearestHour();
    std::cout << "All tests passed successfully.\n";
    return 0;
}
