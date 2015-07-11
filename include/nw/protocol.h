/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-06-13 09:33
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/
#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstring> 
#include <string> 

struct req_ping
{
    int id;
    int t;
    char ip[100];
    char port[100];
};

struct res_ping
{
    int id;
    int rece, loss;
    double mint, avgt, maxt;
    char err_msg[100];
    time_t exect;
};


#endif
