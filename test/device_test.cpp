#include <include/db/dbmanager.h>/**************************************************************
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
    return devicet;
}


TEST(device, crud) {
    DBManager dbm;
    device_dao ddao;
    device_t dt;
    ddao.find_by_id(1, dt);
    std::cout << ddao.to_string(dt) << std::endl;
    EXPECT_EQ(1, dt.deviceId);
    EXPECT_STREQ("gtest", dt.deviceName.c_str());
    EXPECT_STREQ("gtest", dt.deviceType.c_str());
    EXPECT_EQ(0, dt.groupId);
    EXPECT_STREQ("1.1.1.1", dt.deviceIP.c_str());
    EXPECT_EQ(0, dt.monitorFlag);
    EXPECT_STREQ("2015-05-22 21:23:56", m_sql_time2string(dt.lastUpdateTime).c_str());
    EXPECT_STREQ("255.255.255.0", dt.ipMask.c_str());

    //find_all
    std::vector<device_t> vl = ddao.find_all();
    unsigned long  device_num = vl.size();

    //create
    dt = construct_device_t("gtest", "gtest", 0, "127.0.0.1", 0, "255.255.255.0");
    ddao.create(dt);
    vl = ddao.find_all();
    EXPECT_EQ(1+device_num, vl.size());
    device_t ndt;
    //find_by_id
    ddao.find_by_id(vl[device_num].deviceId, ndt);
    dt.deviceId = ndt.deviceId;
    EXPECT_STREQ(ddao.to_string(dt).c_str(), ddao.to_string(ndt).c_str());

    //update
    ndt.deviceName = "newDeviceName";
    ddao.update(ndt);
    ddao.find_by_id(ndt.deviceId, dt);
    EXPECT_STREQ(ddao.to_string(dt).c_str(), ddao.to_string(ndt).c_str());

    //erase
    ddao.erase(ndt.deviceId);
    vl = ddao.find_all();
    EXPECT_EQ(device_num, vl.size());
}
