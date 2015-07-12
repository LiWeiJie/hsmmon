/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-07-12 10:57 PM
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/
#include "include/db/deviceresource.h"

const std::string deviceresource_dao::table_name = "deviceresource";

bool deviceresource_dao::find_by_deviceId(unsigned int deviceId, deviceresource_t& ot){
    char sql[500];
    sprintf(sql, "SELECT * FROM %s WHERE `deviceId`='%d';", this->table_name.c_str(), deviceId);
    hlog(sql);
    this->dbm->sql_execute(sql);
    m_sql_list sql_list = this->dbm->get_sql_res();
    if (sql_list.size()==0) {
        helog("Object not found!");
        return false;
    } else {
        m_sql_list::iterator iter = sql_list.begin();
        ot = this->to_deviceresource_t(*iter);
        return true;
    }
}

bool deviceresource_dao::find_by_resourceId(unsigned int resourceId, deviceresource_t &ot) {
    char sql[500];
    sprintf(sql, "SELECT * FROM %s WHERE `resourceId`='%d';", this->table_name.c_str(), resourceId);
    hlog(sql);
    this->dbm->sql_execute(sql);
    m_sql_list sql_list = this->dbm->get_sql_res();
    if (sql_list.size()==0) {
        helog("Object not found!");
        return false;
    } else {
        m_sql_list::iterator iter = sql_list.begin();
        ot = this->to_deviceresource_t(*iter);
        return true;
    }
}

std::vector<deviceresource_t> deviceresource_dao::find_all() {
    char sql[500];
    sprintf(sql, "SELECT * FROM %s;", this->table_name.c_str());
    hlog(sql);
    this->dbm->sql_execute(sql);
    m_sql_list sql_list = this->dbm->get_sql_res();
    std::vector<deviceresource_t> ol;
    if (sql_list.size()==0) {
        helog("Object not found!");
    } else {
        m_sql_list::iterator iter = sql_list.begin();
        for (; iter != sql_list.end(); iter++) {
            ol.push_back(this->to_deviceresource_t(*iter));
        }
    }
    return ol;
}

std::string deviceresource_dao::to_string(const deviceresource_t &ot) {
    std::string str = "";
    str += m_sql_to_string(ot.deviceId) + "\t";
    str += m_sql_to_string(ot.resourceId);
    return str;
}

deviceresource_t deviceresource_dao::to_deviceresource_t(m_sql_object sql_object) {
    m_sql_object::iterator iter = sql_object.begin();
    deviceresource_t ot;
    assert(sql_object.size() == 2);
    ot.deviceId = m_sql_sti(*iter);
    iter++;
    ot.resourceId = m_sql_sti(*iter);
    return ot;
}
