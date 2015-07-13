/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-07-10 22:49
* @Author: liweijie – licatweijie@gmail.com
* @Description:
*
* @History:
**************************************************************/

#ifndef HSMMON_DAEMON_H
#define HSMMON_DAEMON_H

#include <unistd.h>

#include "include/hsmmon_log.h"

#include "include/db/deviceresource.h"
#include "include/db/device.h"
#include "include/db/resource.h"

#include <vector>
#include <map>
#include <set>

std::map<int, device_t> probes;
std::map<int, resource_t> resources;
std::vector<deviceresource_t> dr_map;

std::map<int, int> device_pid;
std::map<int, std::set<int> > device_resource;
std::map<int, int> resource_device;


// main process
void let_it_fly();

void update_job();

#endif //HSMMON_DAEMON_H

