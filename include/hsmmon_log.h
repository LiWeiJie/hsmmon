/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-07-10 10:19
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/
#ifndef HSMMON_LOG_H
#define HSMMON_LOG_H

#include <fstream> 
#include <string> 

static const char LOG_PATH[] = "hsmmon_log";

template<typename X>
void hlog(X para) {
    std::ofstream ofs;
    ofs.open(LOG_PATH, std::ios::out | std::ios::app);
    ofs << "<Normal>:\t" << para << std::endl;
}

template<typename X>
void helog(X para) {
    std::ofstream ofs;
    ofs.open(LOG_PATH, std::ios::out | std::ios::app);
    ofs << "<Error>:\t" << para << std::endl;
}

template<typename X>
void hfelog(X para) {
    std::ofstream ofs;
    ofs.open(LOG_PATH, std::ios::out | std::ios::app);
    ofs << "<Fatal Error>:\t" << para << std::endl;
}

#define ERR_EXIT(m) \
do\
{\
    hfelog(m);\
    exit(EXIT_FAILURE);\
}\
while (0);\

#endif
