/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-07-10 23:33
* @Author: liweijie – licatweijie@gmail.com
* @Description:
*
* @History:
**************************************************************/

#include "include/db/device.h"

const std::string device_dao::table_name = "device";

bool device_dao::create(device_t &ot) {
    char sql[500];
    std::string otstr = to_string(ot);
    if (otstr.empty()) throw "object broken";
    sprintf(sql, "INSERT INTO %s (`deviceName`, `deviceType`, `groupId`, `deviceIP`, `monitorFlag`, `lastUpdateTime`, `ipMask`) VALUES \
    ('%s', '%s', '%d', '%s', '%d', '%s', '%s');", \
            this->table_name.c_str(), ot.deviceName.c_str(), ot.deviceType.c_str(), ot.groupId, ot.deviceIP.c_str(), ot.monitorFlag,\
            m_sql_time2string(ot.lastUpdateTime).c_str(), ot.ipMask.c_str());
    this->dbm->sql_execute(sql);
    return true;
}

bool device_dao::update(device_t &ot) {
    char sql[500];
    sprintf(sql, "UPDATE `%s` SET `deviceName`='%s', `deviceType`='%s', `groupId`='%d', `deviceIP`='%s', `monitorFlag`='%d', `lastUpdateTime`='%s', `ipMask`='%s' WHERE `deviceId`='%d';", \
            this->table_name.c_str(), ot.deviceName.c_str(), ot.deviceType.c_str(), ot.groupId, ot.deviceIP.c_str(), ot.monitorFlag,\
            m_sql_time2string(ot.lastUpdateTime).c_str(), ot.ipMask.c_str(), ot.deviceId);
    hlog(sql);
    this->dbm->sql_execute(sql);
    return true;
}

bool device_dao::erase(unsigned int id) {
    char sql[500];
    sprintf(sql, "DELETE FROM %s WHERE `deviceId`='%d';", this->table_name.c_str(), id);
    hlog(sql);
    this->dbm->sql_execute(sql);
    return true;
}


bool device_dao::find_by_id(unsigned int id, device_t &ot) {
    char sql[500];
    sprintf(sql, "SELECT * FROM %s WHERE `deviceId`='%d';", this->table_name.c_str(), id);
    hlog(sql);
    this->dbm->sql_execute(sql);
    m_sql_list sql_list = this->dbm->get_sql_res();
    if (sql_list.size()==0) {
        helog("Object not found!");
        return false;
    } else {
        m_sql_list::iterator iter = sql_list.begin();
        ot = this->to_device_t(*iter);
        return true;
    }
}

std::vector<device_t> device_dao::find_all() {
    char sql[500];
    sprintf(sql, "SELECT * FROM %s;", this->table_name.c_str());
    hlog(sql);
    this->dbm->sql_execute(sql);
    m_sql_list sql_list = this->dbm->get_sql_res();
    std::vector<device_t> ol;
    if (sql_list.size()==0) {
        helog("Object not found!");
    } else {
        m_sql_list::iterator iter = sql_list.begin();
        for (; iter != sql_list.end(); iter++) {
            ol.push_back(this->to_device_t(*iter));
        }
    }
    return ol;
}

std::string device_dao::to_string(const device_t &ot) {
    std::string str = "";
    str += m_sql_to_string(ot.deviceId) + "\t";
    str += ot.deviceName + "\t";
    str += ot.deviceType + "\t";
    str += m_sql_to_string(ot.groupId) + "\t";
    str += ot.deviceIP + "\t";
    str += m_sql_to_string(ot.monitorFlag) + "\t";
    str += m_sql_time2string(ot.lastUpdateTime) + "\t";
    str += ot.ipMask;
    return str;
}

device_t device_dao::to_device_t(m_sql_object sql_object) {
    m_sql_object::iterator iter = sql_object.begin();
    device_t ot;
    assert(sql_object.size() == 8);
    ot.deviceId = m_sql_sti(*iter);
    iter++;
    ot.deviceName = *iter;
    iter++;
    ot.deviceType = *iter;
    iter++;
    ot.groupId = m_sql_sti(*iter);
    iter++;
    ot.deviceIP = *iter;
    iter++;
    ot.monitorFlag = m_sql_sti(*iter);
    iter++;
    ot.lastUpdateTime = m_sql_string2time(*iter);
    iter++;
    ot.ipMask = *iter;
    return ot;
}
