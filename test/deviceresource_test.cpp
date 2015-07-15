/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-07-12 11:30 PM
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/

#include <limits.h>
#include "gtest/gtest.h"
#include <iostream>

#include "include/db/deviceresource.h"
#include "include/hsmmon_log.h"

TEST(deviceresource, find_by_deviceId) {
    deviceresource_dao drao;
    deviceresource_t dr;
    drao.find_by_deviceId(1, dr);
    EXPECT_EQ(2, dr.resourceId);
}

TEST(deviceresource, find_by_resourceId) {
    deviceresource_dao drao;
    deviceresource_t dr;
    drao.find_by_resourceId(1, dr);
    EXPECT_EQ(2, dr.deviceId);
}
