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

#define ERR_EXIT(m) \
do\
{\
    hfelog(m);\
    exit(EXIT_FAILURE);\
}\
while (0);\

// main process
void let_it_fly();

#endif //HSMMON_DAEMON_H

