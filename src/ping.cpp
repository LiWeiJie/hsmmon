/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-06-13 15:58
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/

#include "include/db/ping.h"

std::string ping_dao::to_string(const ping_t &pt)
{
    std::string str;
    str += this->dbm->sql_to_string(pt.pingId) + "\t" +
        this->dbm->sql_to_string(pt.sendPackage) + "\t" +
        this->dbm->sql_to_string(pt.receivePackage) + "\t" +
        this->dbm->sql_to_string(pt.lostPackage) + "\t" +
        this->dbm->sql_to_string(pt.minTime) + "\t" +
        this->dbm->sql_to_string(pt.maxTime) + "\t" +
        this->dbm->sql_to_string(pt.averageTime) + "\t" +
        pt.errorMessage + "\t" +
        this->dbm->sql_time2string(pt.pingTime) + "\t" +
        this->dbm->sql_to_string(pt.alarmFlag);
    return str;
}


bool ping_dao::create(ping_t &pt)
{
    char sql[500];
    sprintf(sql, "INSERT INTO %s (`sendPackage`, `receivePackage`, `lostPackage`, `minTime`, `maxTime`, `averageTime`, `errorMessage`, `pingTime`) VALUES \
            ('%d', '%d', '%d', '%d', '%d', '%d', '%s', '%s');", \
            this->table_name.c_str(),  pt.sendPackage, pt.receivePackage, pt.lostPackage, pt.minTime, pt.maxTime, pt.averageTime, pt.errorMessage.c_str(), this->dbm->sql_time2string(pt.pingTime).c_str());
    hlog(sql);
    this->dbm->sql_execute(sql);
    return true;
}

bool ping_dao::update(ping_t &pt)
{
    char sql[500];
    sprintf(sql, "UPDATE %s SET `sendPackage`='%d', `receivePackage`='%d', `lostPackage`='%d', `minTime`='%d', `maxTime`='%d', `averageTime`='%d', `errorMessage`='%s', `pingTime`='%s'WHERE `pingId`='%d';",\
            this->table_name.c_str(),  pt.sendPackage, pt.receivePackage, pt.lostPackage, pt.minTime, pt.maxTime, pt.averageTime, pt.errorMessage.c_str(), this->dbm->sql_time2string(pt.pingTime).c_str(), pt.pingId);
    hlog(sql);
    this->dbm->sql_execute(sql);
    return true;
}


bool ping_dao::erase(unsigned int id)
{
    char sql[500];
    sprintf(sql, "DELETE FROM %s WHERE `pingId`='%d';", this->table_name.c_str(), id);
    hlog(sql);
    this->dbm->sql_execute(sql);
    return true;
}

std::vector<ping_t> ping_dao::find_all()
{
    char sql[500];
    sprintf(sql, "SELECT * FROM %s;", this->table_name.c_str());
    hlog(sql);
    this->dbm->sql_execute(sql);
    m_sql_list sql_list = this->dbm->get_sql_res();
    std::vector<ping_t> pfl;
    if (sql_list.size()==0) {
        helog("Object not found!");
    } else {
        m_sql_list::iterator iter = sql_list.begin();
        for (; iter != sql_list.end(); iter++) {
            pfl.push_back(this->to_ping_t(*iter));
        }
    }
    return pfl;
}


bool ping_dao::find_by_id(unsigned int id, ping_t &pt)
{
    char sql[500];
    sprintf(sql, "SELECT * FROM %s WHERE `pingId`='%d';", this->table_name.c_str(), id);
    hlog(sql);
    this->dbm->sql_execute(sql);
    m_sql_list sql_list = this->dbm->get_sql_res();    
    if (sql_list.size()==0) {
        helog("Object not found!");
        return false;
    } else {
        m_sql_list::iterator iter = sql_list.begin();
        pt = this->to_ping_t(*iter);
        return true;
    }
    
}

ping_t ping_dao::to_ping_t(m_sql_object sql_object) {
    m_sql_object::iterator iter = sql_object.begin();
    ping_t pt;
    assert(sql_object.size() == 10);
    pt.pingId = this->dbm->sql_sti(*iter);
    iter++;
    pt.sendPackage = this->dbm->sql_sti(*iter);
    iter++;
    pt.receivePackage = this->dbm->sql_sti(*iter);
    iter++;
    pt.lostPackage =  this->dbm->sql_sti(*iter);
    iter++;
    pt.minTime = this->dbm->sql_sti(*iter);
    iter++;
    pt.maxTime = this->dbm->sql_sti(*iter);
    iter++;
    pt.averageTime = this->dbm->sql_sti(*iter);
    iter++;
    pt.errorMessage = *iter;
    iter++;
    pt.pingTime = this->dbm->sql_string2time(*iter);
    iter++;
    if(iter->empty())
        pt.alarmFlag = false;
    else 
        pt.alarmFlag = this->dbm->sql_sti(*iter)>0?true:false;
    return pt;
}

