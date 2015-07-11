/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-06-14 17:04
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/

#include "include/nw/m_socket.h"

void socket_send::m_close()
{
    if (this->connected) 
        close(this->sock);
    this->connected = false;
    return ;
}


void socket_send::m_connect() {
    /* Establish connection */
    if (connect(sock, (struct sockaddr *) &this->server, sizeof(this->server)) < 0) {
        //Die("Failed to connect with server");
    }
    this->connected = true;
    return;
}


bool socket_send::is_connected() {
    return this->connected;
}


long socket_send::m_receive(char *buffer, unsigned int _size)
{
    long rece_len;
    rece_len = recv(this->sock, buffer, _size, 0);
    return rece_len;
}


bool socket_send::m_send(char *bytes, unsigned int _size)
{
    if (send(sock, bytes, _size, 0) != _size) {
        //Die("Mismatch in number of sent bytes");
    }
    return true;
}

socket_send::socket_send(std::string server_ip, std::string port)
{
    this->sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); 
    /*  if (this->sock){*/
    ////std::cerr<< "Fail to create socket" << std::endl;
    ////Die("Fail to create socket");
    //std::cout << "Fail" << std::endl;
    /*}*/
    /* Construct the server sockaddr_in structure */
    std::memset(&this->server, 0, sizeof(this->server));
    server.sin_family = AF_INET;                  /* Internet/IP */
    server.sin_addr.s_addr = inet_addr(server_ip.c_str());  /* IP address */
    server.sin_port = htons((uint16_t)atoi(port.c_str()));       /* server port */
    this->connected = false;
}

socket_send::~socket_send()
{
}

