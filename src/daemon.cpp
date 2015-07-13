/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-07-10 22:55
* @Author: liweijie – licatweijie@gmail.com
* @Description:
*
* @History:
**************************************************************/

#include "include/daemon.h"


void let_it_fly() {
    if (daemon(1, 1) == -1)
        ERR_EXIT("daemon error");
    update_job();

}

void update_job() {
    device_dao deviceDao;
    std::vector<device_t> dtv = deviceDao.find_all();
    resource_dao resourceDao;
    std::vector<resource_t> rtv = resourceDao.find_all();
    probes.clear();
    for (auto dt:dtv) {
        probes[dt.deviceId] = dt;
    }
    resources.clear();
    for (auto rt:rtv) {
        resources[rt.resourceId] = rt;
    }
    deviceresource_dao deviceresourceDao;
    dr_map = deviceresourceDao.find_all();
    for (auto dr:dr_map) {
        device_resource[dr.deviceId].insert(dr.resourceId);
        resource_device[dr.resourceId] = dr.deviceId;
    }

}


