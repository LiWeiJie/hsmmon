/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-05-28 16:26
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/

#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h> 
#include <mysql/mysql.h>
#include <vector> 

#include "include/hsmmon_log.h"

#include "include/db/ping.h"
#include "include/db/device.h"

#include "include/nw/m_socket.h"
#include "include/nw/protocol.h"

using namespace std;

//#define MAXPENDING 500   [> Max connection requests <]
//#define BUFFSIZE 32

void  print_vvs(m_sql_list vvs) {
    vector< vector<string> >::iterator vvsiter= vvs.begin();
    for (; vvsiter != vvs.end(); vvsiter++ ) {
        vector< string>::iterator vsiter = vvsiter->begin();
        for (; vsiter != vvsiter->end(); vsiter++) {
           cout << *vsiter << endl;
        }
    }
    return ;
}

void test_sql_conn()
{
    DBManager dbase("127.0.0.1", "root", "root", "hsmmon", 3306);
    dbase.init_connect();
    dbase.sql_execute("SELECT * FROM hsmmon.pingFlow;");
    m_sql_list res = dbase.get_sql_res();
    print_vvs(res);
    return;
}

void get_all_pf()
{
    ping_dao pd;

    vector<ping_t> ptl = pd.find_all();
    for (vector<ping_t>::iterator iter = ptl.begin(); iter!=ptl.end(); iter++) {
        cout << pd.to_string(*iter) << endl;
    }    
    return;
}

void get_pf_by_id(unsigned int id)
{ 
    ping_dao pd;

    ping_t pt;
    pd.find_by_id(id, pt);
    cout << pd.to_string(pt) << endl;
    return;
}

void ping_t_test()
{
    ping_dao pd;
    ping_t pt;
    pt.sendPackage = 10;
    pt.receivePackage = 8;
    pt.lostPackage = 2;
    pt.minTime = 0;
    pt.maxTime = 99;
    pt.averageTime = 50;
    pt.errorMessage = "Good news";
    pt.pingTime = time(0);
    pt.alarmFlag = true;
    pd.create(pt);
    mes(pd.to_string(pt).c_str());
    get_all_pf();    
}

void debug() 
{
    req_ping reqp;
    reqp.id = 1;
    reqp.t = 1;
    std::strcpy(reqp.ip, "baidu.com");
    std::strcpy(reqp.port, "1080");
    mes(std::to_string(sizeof(reqp.ip)).c_str());
    mes(std::to_string(sizeof(req_ping)).c_str());

    //socket_send ss("192.168.1.123","1083");
    socket_send ss("127.0.0.1","5555");
    ss.m_connect();
    ss.m_send((char*)&reqp, sizeof(reqp));
    
    mes("send finshed");

    char buffer[1000];
    ss.m_receive(buffer, 1000);

    res_ping resp;
    memset(&resp,0,sizeof(resp));//清空结构体
    memcpy(&resp, buffer, sizeof(resp));
    
    mes(resp.err_msg);

    //get_pf_by_id(2);

    /*int serversock, clientsock;*/
    //struct sockaddr_in serverm, client;

    //[> Create TCP <]
    //serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //if (serversock < 0) {
        //Die("Failed to create socket");
    //}

    cout << "hehe" << endl;
  
}

int main(int argc, char *argv[])
{
    cout << "start: start hsmmon daemon" << endl;
    cout << "stop: stop hsmmon daemon" << endl;
    cout << "log: dynmic log" << endl;
    cout << "debug: debug pattern" << endl;
    
    string com;
    cin >> com;

    if (com.compare("start") == 0) {
        cout << "To be continuc" << endl;
    } else if (com.compare("stop") == 0) {
        cout << "To be continue" << endl;
    } else if (com.compare("log") == 0) {
        cout << "To be continue" << endl;
    } else if (com.compare("debug") == 0) {
        debug();
    } else {
        cout << "Donot match" << endl;
    }


    return 0;
}
