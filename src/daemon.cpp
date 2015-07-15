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

std::map<int, device_t> probes;
std::map<int, resource_t> resources;
std::vector<deviceresource_t> dr_map;

//std::map<int, int> device_pid;
std::map<int, int> resource_pid;
std::map<int, std::set<int> > device_resource;
std::map<int, int> resource_device;

ping_t res_t_ping(res_ping rp);

void monitor_handle(int resourceId);

void alarm_handle(ping_t &pt);


void let_it_fly() {
    if (daemon(1, 1) == -1)
        ERR_EXIT("daemon error");
    update_job();

    int fork_status;
    for (auto resource:resources) {
        fork_status = fork();
        if (fork_status == -1) {
            ERR_EXIT("fork error");
        } else if (fork_status > 0) {
            resource_pid[resource.first] = fork_status;
        } else {
            monitor_handle(resource.first);
        }
    }

    //TODO main process

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


void monitor_handle(int resourceId) {
    resource_t resource = resources[resourceId];
    device_t device = probes[resource_device[resourceId]];

    while (1) {
        // maybe 1 is the ping
        if (resource.resourceType == 1) {
            req_ping send_ping;
            send_ping.id = resourceId;
            send_ping.t = 1;
            std::strcpy(send_ping.ip, device.deviceIP.c_str());

            //TODO whereis the port?!
            std::strcpy(send_ping.port, "1111");

            //socket_send ss("192.168.1.123","1083");
            //TODO send to where?
            socket_send ss("127.0.0.1", "5555");
            ss.m_connect();
            ss.m_send((char *) &send_ping, sizeof(send_ping));

            char buffer[1000];
            ss.m_receive(buffer, 1000);

            res_ping receive_ping;
            memset(&receive_ping, 0, sizeof(receive_ping));//清空结构体
            memcpy(&receive_ping, buffer, sizeof(receive_ping));

            ping_dao pindDao;
            ping_t pt = res_t_ping(receive_ping);

            //TODO handle alarm
            alarm_handle(pt);
        }
        if (resource.frequency > 0) {
            //frequenct count
            // by seconds
            sleep((unsigned int) (resource.frequency * 60));
        } else {
            break;
        }
    }
    return;
}


ping_t res_t_ping(res_ping rp) {
    ping_t pt;
    pt.sendPackage = rp.send;
    pt.receivePackage = rp.rece;
    pt.lostPackage = rp.loss;
    pt.minTime = rp.mint;
    pt.maxTime = rp.maxt;
    pt.averageTime = rp.avgt;
    pt.errorMessage = rp.err_msg;
    pt.pingTime = rp.exect;
    return pt;
}

void alarm_handle(ping_t &pt) {
    //TODO
}
