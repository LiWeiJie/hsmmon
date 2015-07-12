/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-07-12 9:06 AM
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/

#include <limits.h>
#include "gtest/gtest.h"
#include <iostream>

#include "include/db/device.h"

device_t construct_device_t(std::string device_name, std::string device_type, int group_id, \
    std::string device_ip, bool monitor_flag, std::string ip_mask) {
    device_t devicet;
    devicet.deviceName = device_name;
    devicet.deviceType = device_type;
    devicet.groupId = group_id;
    devicet.deviceIP = device_ip;
    devicet.lastUpdateTime = time(0);
    devicet.monitorFlag = monitor_flag;
    devicet.ipMask = ip_mask;
    device_dao ddao;

    std::cout << devicet.ipMask << std::endl;
    std::cout << ddao.to_string(devicet) << std::endl;
    return devicet;
}


TEST(device_dao, create
) {
device_dao ddao;
//    cout << ddao.table_name << endl;
device_t dt = construct_device_t("gtest", "gtest", 0, "127.0.0.1", 0, "255.255.255.0");
std::cout << dt.deviceName <<
std::endl;
std::cout << dt.ipMask <<
std::endl;
std::cout << ddao.
to_string(dt)
<<
std::endl;
EXPECT_TRUE(ddao
.
create(dt)
);
}

