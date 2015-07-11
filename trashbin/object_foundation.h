/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-06-04 23:58
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/
#ifndef OBJECTFOUNDATION_H
#define OBJECTFOUNDATION_H

#include <string> 
#include <cstring> 
#include <cstdlib> 
#include <ctime> 
#include "db/dbmanager.h" 

class DBManager;

class ObjectFoundation 
{ 
    public: 
        ObjectFoundation(std::string tableName); 
        virtual ~ObjectFoundation(); 
        virtual std::string to_sql() = 0;
        virtual std::string get_field(unsigned int pos) = 0;
        virtual bool set_field(std::string str, unsigned int pos) = 0;   
        std::string get_table_name();
        bool is_vaild();

        virtual bool create(DBManager &dbm) = 0;
        virtual bool update(DBManager &dbm) = 0;
        virtual bool erase(DBManager &dbm) = 0;
        
        virtual ObjectFoundation* find_by_id(unsigned int id, DBManager &dbm) = 0;
        virtual std::vector<ObjectFoundation*> find_all(DBManager &dbm) = 0;

        static std::string sql_to_string(int t);
        static std::string sql_to_string(long int t);
        static std::string sql_time2string(time_t t);
        static time_t sql_string2time(std::string t);

        virtual std::string to_string() = 0;

    protected:
        void set_vaild();
        void set_invaild();

    private: 
        char *table_name;
        bool vaild;
};  

#endif
