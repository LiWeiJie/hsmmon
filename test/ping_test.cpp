/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-07-15 7:07 PM
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/

#include <limits.h>
#include "gtest/gtest.h"
#include <iostream>
#include <time.h>

#include "include/db/ping.h"
#include "include/db/dbmanager.h"

ping_t construct_ping_t(int sendPackage, int receivePackage, int lostPackage, int minTime, int maxTime,\
int averageTime, std::string errorMessage, bool alarmFlag) {
    ping_t ot;
    ot.sendPackage = sendPackage;
    ot.receivePackage = receivePackage;
    ot.lostPackage = lostPackage;
    ot.minTime = minTime;
    ot.maxTime = maxTime;
    ot.averageTime = averageTime;
    ot.errorMessage = errorMessage;
    ot.pingTime = time(0);
    ot.alarmFlag = alarmFlag;
    return ot;
}

TEST(ping, find_by_id) {
    ping_dao pingDao;
    ping_t dt;

    pingDao.find_by_id(1, dt);
    EXPECT_EQ(1, dt.pingId);
    EXPECT_EQ(10, dt.sendPackage);
    EXPECT_EQ(10, dt.receivePackage);
    EXPECT_EQ(0, dt.lostPackage);
    EXPECT_EQ(0, dt.minTime);
    EXPECT_EQ(0, dt.maxTime);
    EXPECT_EQ(0, dt.averageTime);
    EXPECT_STREQ("noError", dt.errorMessage.c_str());
    EXPECT_STREQ("2015-05-22 21:23:56", m_sql_time2string(dt.pingTime).c_str());
    EXPECT_EQ(0, dt.alarmFlag);
}
