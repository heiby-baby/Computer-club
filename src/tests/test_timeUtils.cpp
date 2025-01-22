#include <gtest/gtest.h>
#include "timeUtils.h"
#include "GameClub.h"

TEST(TimeUtilsTests_Positive, TimeParserHHMMtoM) {
    EXPECT_EQ(timeParserHHMMtoM("12:34"), 754);
    EXPECT_EQ(timeParserHHMMtoM("00:00"), 0);    
    EXPECT_EQ(timeParserHHMMtoM("23:59"), 1439);
}

TEST(TimeUtilsTests_Negative, TimeParserHHMMtoM) {
    EXPECT_THROW(timeParserHHMMtoM("12:3"), std::invalid_argument);
    EXPECT_THROW(timeParserHHMMtoM("24:00"), std::invalid_argument);
    EXPECT_THROW(timeParserHHMMtoM("23:60"), std::invalid_argument);
    EXPECT_THROW(timeParserHHMMtoM("12:345"), std::invalid_argument); 
}

TEST(TimeUtilsTests_Positive, TimeParserMtoHHMM) {
    EXPECT_EQ(timeParserMtoHHMM(754), "12:34");
    EXPECT_EQ(timeParserMtoHHMM(0), "00:00");    
    EXPECT_EQ(timeParserMtoHHMM(1439), "23:59"); 
}

TEST(TimeUtilsTests_Negative, TimeParserMtoHHMM) {
    EXPECT_THROW(timeParserMtoHHMM(-1), std::invalid_argument);
    EXPECT_THROW(timeParserMtoHHMM(1440), std::invalid_argument);
}

TEST(TimeUtilsTests_Positive, RoundToNearestHour) {
    EXPECT_EQ(roundToNearestHour(754), 780);  
    EXPECT_EQ(roundToNearestHour(0), 0);     
    EXPECT_EQ(roundToNearestHour(1439), 1440); 
    EXPECT_EQ(roundToNearestHour(60), 60);   
}
