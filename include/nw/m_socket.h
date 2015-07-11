/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-06-14 16:31
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/
#ifndef M_SOCKET_H
#define M_SOCKET_H

#include <iostream> 

#include <cstring> 
#include <string> 

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>


class socket_send 
{ 
    public: 
        socket_send(std::string server_ip, std::string port);
        virtual ~socket_send(); 

        void m_connect();
        void m_close();
        bool is_connected();

        bool m_send(char *bytes, unsigned int _size);
        long m_receive(char *buffer, unsigned int _size);

    private: 
        int sock;
        struct sockaddr_in server;
    bool connected;
}; 

class socket_rece 
{ 
    public: 
        socket_rece(); 
        virtual ~socket_rece(); 

    private: 
}; 

#endif
