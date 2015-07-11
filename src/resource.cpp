/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-07-11 4:47 PM
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/
#include "include/db/resource.h"

bool resource_dao::create(resource_t &ot) {
    char sql[500];
    sprintf(sql, "INSERT INTO `%s` (`resourceName`, `resourceType`, `interval`, `frequency`, `lastUpdateTime`, `remark`, `thresholdValue`) VALUES \
            ('%s', '%d', '%d', '%d', '%s', '%s', '%s');", \
            this->table_name.c_str(), ot.resourceName.c_str(), ot.resourceType, ot.interval, ot.frequency, \
            this->dbm->sql_time2string(ot.lastUpdateTime).c_str(), ot.remark.c_str(), ot.thresholdValue.c_str());
    hlog(sql);
    this->dbm->sql_execute(sql);
    return true;
}

bool resource_dao::update(resource_t &ot) {
    char sql[500];
    sprintf(sql, "UPDATE `%s` SET `resourceName`='%s', `resourceType`='%d', `interval`='%d', \
            `frequency`='%d', `lastUpdateTime`='%s', `remark`='%s', `thresholdValue`='%s' WHERE `resourceId`='%d';", \
            this->table_name.c_str(), ot.resourceName.c_str(), ot.resourceType, ot.interval, ot.frequency, \
            this->dbm->sql_time2string(ot.lastUpdateTime).c_str(), ot.remark.c_str(), ot.thresholdValue.c_str(), \
            ot.resourceId);
    hlog(sql);
    this->dbm->sql_execute(sql);
    return true;
}

bool resource_dao::erase(unsigned int id) {
    char sql[500];
    sprintf(sql, "DELETE FROM %s WHERE `resourceId`='%d';", this->table_name.c_str(), id);
    hlog(sql);
    this->dbm->sql_execute(sql);
    return true;
}

bool resource_dao::find_by_id(unsigned int id, resource_t &ot) {
    char sql[500];
    sprintf(sql, "SELECT * FROM %s WHERE `resourceId`='%d';", this->table_name.c_str(), id);
    hlog(sql);
    this->dbm->sql_execute(sql);
    m_sql_list sql_list = this->dbm->get_sql_res();
    if (sql_list.size() == 0) {
        helog("Object not found!");
        return false;
    } else {
        m_sql_list::iterator iter = sql_list.begin();
        ot = this->to_resource_t(*iter);
        return true;
    }
}

std::vector<resource_t> resource_dao::find_all() {
    char sql[500];
    sprintf(sql, "SELECT * FROM %s;", this->table_name.c_str());
    hlog(sql);
    this->dbm->sql_execute(sql);
    m_sql_list sql_list = this->dbm->get_sql_res();
    std::vector<resource_t> ol;
    if (sql_list.size() == 0) {
        helog("Object not found!");
    } else {
        m_sql_list::iterator iter = sql_list.begin();
        for (; iter != sql_list.end(); iter++) {
            ol.push_back(this->to_resource_t(*iter));
        }
    }
    return ol;
}

std::string resource_dao::to_string(const resource_t &ot) {
    std::string str;
    str += this->dbm->sql_to_string(ot.resourceId) + "\t" +
           ot.resourceName + "\t" +
           this->dbm->sql_to_string(ot.resourceType) + "\t" +
           this->dbm->sql_to_string(ot.interval) + "\t" +
           this->dbm->sql_to_string(ot.frequency) + "\t" +
           this->dbm->sql_to_string(ot.lastUpdateTime) + "\t" +
           ot.remark + "\t" +
           ot.thresholdValue;
    return str;
}

resource_t resource_dao::to_resource_t(m_sql_object sql_object) {
    m_sql_object::iterator iter = sql_object.begin();
    resource_t ot;
    assert(sql_object.size() == 8);
    ot.resourceId = this->dbm->sql_sti(*iter);
    iter++;
    ot.resourceName = *iter;
    iter++;
    ot.resourceType = this->dbm->sql_sti(*iter);
    iter++;
    ot.interval = this->dbm->sql_sti(*iter);
    iter++;
    ot.frequency = this->dbm->sql_sti(*iter);
    iter++;
    ot.lastUpdateTime = this->dbm->sql_string2time(*iter);
    iter++;
    ot.remark = *iter;
    iter++;
    ot.thresholdValue = *iter;
    return ot;
}
