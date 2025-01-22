#include <gtest/gtest.h>
#include "GameClub.h"

TEST(GameClubTests_Positive, isValidTimeString) {
    EXPECT_TRUE(GameClub::isValidTimeString("12:34 16:21"));
    EXPECT_TRUE(GameClub::isValidTimeString("00:00 23:59"));
    EXPECT_TRUE(GameClub::isValidTimeString("01:01 01:01")); 
}

TEST(GameClubTests_Negative, isValidTimeString) {
    EXPECT_FALSE(GameClub::isValidTimeString("1234 56:78"));
    EXPECT_FALSE(GameClub::isValidTimeString("aa:bb cc:dd"));
    EXPECT_FALSE(GameClub::isValidTimeString("12:34 56:7"));
    EXPECT_FALSE(GameClub::isValidTimeString("")); 
    EXPECT_FALSE(GameClub::isValidTimeString("12:34 24:00")); 
    EXPECT_FALSE(GameClub::isValidTimeString("12:34 12:60")); 
}

TEST(GameClubTests_Positive, isDigitsOnly) {
    EXPECT_TRUE(GameClub::isDigitsOnly("1234567890"));
}

TEST(GameClubTests_Negative, isDigitsOnly) {
    EXPECT_FALSE(GameClub::isDigitsOnly("123abc"));
    EXPECT_FALSE(GameClub::isDigitsOnly(""));
    EXPECT_FALSE(GameClub::isDigitsOnly("123 456"));
    EXPECT_FALSE(GameClub::isDigitsOnly("   ")); 
}

TEST(GameClubTests_Positive, isEventValidFormat) {
    EXPECT_TRUE(GameClub::isEventValidFormat("12:34 56 client_name 789"));
    EXPECT_TRUE(GameClub::isEventValidFormat("00:00 1 user-123 9999"));
}

TEST(GameClubTests_Negative, isEventValidFormat) {
    EXPECT_FALSE(GameClub::isEventValidFormat("12:34 client_name 789"));
    EXPECT_FALSE(GameClub::isEventValidFormat("12:34 56 client@name 789"));
    EXPECT_FALSE(GameClub::isEventValidFormat(""));
    EXPECT_FALSE(GameClub::isEventValidFormat("12:34 56 client_name789")); 
}

