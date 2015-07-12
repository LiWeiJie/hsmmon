/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-07-12 10:57 PM
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/
#include <bits/stl_bvector.h>
#include <bits/stringfwd.h>

#ifndef HSMMON_DEVICERESOURCE_H
#define HSMMON_DEVICERESOURCE_H

struct deviceresource_t {
    int deviceId;
    int resourceId;
};

class deviceresource_dao
{
public:
    deviceresource_dao(){
        dbm = new DBManager();
        dbm->init_connect();
    }
    ~deviceresource_dao() {
        delete dbm;
    }
//    bool create(deviceresource_t &ot);
//    bool update(deviceresource_t &ot);
//    bool erase(unsigned int id);

    bool find_by_deviceId(unsigned int deviceId, deviceresource_t &ot);
    bool find_by_resourceId(unsigned int resourceId, deviceresource_t &ot);
    std::vector<deviceresource_t> find_all();

    std::string to_string(const deviceresource_t &ot);

private:
    static const std::string table_name;
    DBManager *dbm;
    deviceresource_t to_deviceresource_t(m_sql_object sql_object);

};

#endif //HSMMON_DEVICERESOURCE_H

