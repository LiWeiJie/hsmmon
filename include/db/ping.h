/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-06-13 09:40
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/
#ifndef PING_H
#define PING_H

#include <cstring> 
#include <string> 
#include <time.h>

#include "dbmanager.h"

struct ping_t
{
    int pingId = 0;
    int sendPackage = 0;
    int receivePackage = 0;
    int lostPackage = 0;
    int minTime = 0;
    int maxTime = 0;
    int averageTime = 0;
    std::string errorMessage;
    time_t pingTime = 0;
    bool alarmFlag = 0;
};

class ping_dao
{
    public:
        ping_dao(){
            dbm = new DBManager();
            dbm->init_connect();
        }
        ~ping_dao() {
            delete dbm;
        }
        bool create(ping_t &pt);
        bool update(ping_t &pt);
        bool erase(unsigned int id);

        bool find_by_id(unsigned int id, ping_t &pt);
        std::vector<ping_t> find_all();

        std::string to_string(const ping_t &pt);

    private:
        const std::string table_name =  "pingflow";
        DBManager *dbm;
        ping_t to_ping_t(m_sql_object sql_object);

};

#endif
