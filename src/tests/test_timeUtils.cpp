#include <gtest/gtest.h>
#include "timeUtils.h"

TEST(TimeUtilsTest, TimeParserHHMMtoM) {
    EXPECT_EQ(timeParserHHMMtoM("12:34"), 754);
    EXPECT_EQ(timeParserHHMMtoM("00:00"), 0);
    EXPECT_EQ(timeParserHHMMtoM("23:59"), 1439);
}

TEST(TimeUtilsTest, TimeParserMtoHHMM) {
    EXPECT_EQ(timeParserMtoHHMM(754), "12:34");
    EXPECT_EQ(timeParserMtoHHMM(0), "00:00");
    EXPECT_EQ(timeParserMtoHHMM(1439), "23:59");
}

TEST(TimeUtilsTest, RoundToNearestHour) {
    EXPECT_EQ(roundToNearestHour(754), 780);  
    EXPECT_EQ(roundToNearestHour(0), 0);      
    EXPECT_EQ(roundToNearestHour(1439), 1440); 
}


