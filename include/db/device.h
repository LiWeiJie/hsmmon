/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-06-25 21:01
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/
#ifndef DEVICE_H
#define DEVICE_H

#include <time.h>
#include <vector>

#include "dbmanager.h"

struct device_t
{
    int deviceId;
    std::string deviceName;
    std::string deviceType;
    int groupId;
    std::string deviceIP;
    bool monitorFlag;
    time_t lastUpdateTime;
    std::string ipMask;
};

class device_dao
{
    public:
        device_dao(){
            dbm = new DBManager();
            dbm->init_connect();
        }
        ~device_dao() {
            delete dbm;
        }
        bool create(device_t &ot);
        bool update(device_t &ot);
        bool erase(unsigned int id);

        bool find_by_id(unsigned int id, device_t &ot);
        std::vector<device_t> find_all();

        std::string to_string(const device_t &ot);

    private:
        const std::string table_name =  "device";
        DBManager *dbm;
        device_t to_device_t(m_sql_object sql_object);

};
#endif
