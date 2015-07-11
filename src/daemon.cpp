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


void let_it_fly()
{
    if (daemon(1, 1) == -1)
        ERR_EXIT("daemon error");

}


