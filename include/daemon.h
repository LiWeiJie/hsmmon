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
#include "include/db/ping.h"

#include "include/nw/protocol.h"
#include <include/nw/m_socket.h>

#include <vector>
#include <map>
#include <set>

extern std::map<int, device_t> probes;
extern std::map<int, resource_t> resources;
extern std::vector<deviceresource_t> dr_map;

//extern std::map<int, int> device_pid;
extern std::map<int, int> resource_pid;
extern std::map<int, std::set<int> > device_resource;
extern std::map<int, int> resource_device;


// main process
void let_it_fly();

void update_job();

void monitor_handle();

#endif //HSMMON_DAEMON_H

