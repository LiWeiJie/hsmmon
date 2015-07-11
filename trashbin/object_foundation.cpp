/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-06-05 00:21
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/

#include "../include/object_foundation.h"  

ObjectFoundation::~ObjectFoundation()
{
    if (this->table_name != NULL)
        delete this->table_name;
    this->set_invaild();
}

ObjectFoundation::ObjectFoundation(std::string tableName)
{
    this->table_name = new char[tableName.length()+1];
    std::strcpy(this->table_name, tableName.c_str());
    this->set_vaild();
}


std::string ObjectFoundation::get_table_name()
{
    return this->table_name;
}

std::string ObjectFoundation::sql_to_string(int t)
{
    return std::to_string(t);
}

std::string ObjectFoundation::sql_to_string(long int t)
{
    return std::to_string(t);
}

std::string ObjectFoundation::sql_time2string(time_t t)
{
    char buffer[256];
    struct tm *time_info;
    time_info = localtime(&t);
    std::strftime(buffer, 256, "%Y-%m-%d %H:%M:%S", time_info);
    return buffer;
}

time_t ObjectFoundation::sql_string2time(std::string t)
{
    struct tm time_info;
    memset(&time_info, 0, sizeof(struct tm));
    strptime(t.c_str(), "%Y-%m-%d %H:%M:%S", &time_info); 
    return mktime(&time_info);
}


bool ObjectFoundation::is_vaild()
{
    return this->vaild;
}


void ObjectFoundation::set_invaild()
{
    this->vaild = false;
    return ;
}


void ObjectFoundation::set_vaild()
{
    this->vaild = true;
    return ;
}


