/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-07-11 4:32 PM
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/
#ifndef HSMMON_RESOURCE_H
#define HSMMON_RESOURCE_H

#include <string>
#include <time.h>

#include "include/db/dbmanager.h"

struct resource_t {
    int resourceId;
    std::string resourceName;
    int resourceType;
    int interval;
    int frequency;
    time_t lastUpdateTime;
    std::string remark;
    std::string thresholdValue;
};

class resource_dao {
public:
    resource_dao() {
        dbm = new DBManager();
        dbm->init_connect();
    }

    ~resource_dao() {
        delete dbm;
    }

    bool create(resource_t &ot);

    bool update(resource_t &ot);

    bool erase(unsigned int id);

    bool find_by_id(unsigned int id, resource_t &ot);

    std::vector<resource_t> find_all();

    std::string to_string(const resource_t &ot);

private:
    const std::string table_name = "resource";
    DBManager *dbm;

    resource_t to_resource_t(m_sql_object sql_object);
};

#endif //HSMMON_RESOURCE_H
