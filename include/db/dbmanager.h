/**************************************************************
 * Copyright (C) 2006-2015 All rights reserved.
 * @Version: 1.0
 * @Created: 2015-05-29 16:34
 * @Author: liweijie – licatweijie@gmail.com
 * @Description: 
 *
 * @History: 
 **************************************************************/
#ifndef DBASE_H
#define DBASE_H

#include <string> 
#include <cstring>
#include <vector>
#include <iostream> 
#include <assert.h> 

//#include <mysql_driver.h> 
//#include <mysql_connection.h>
//#include <cppconn/resultset.h>
//#include <cppconn/statement.h>
//#include <cppconn/driver.h>
//#include <cppconn/connection.h> 
//#include <cppconn/exception.h> 

#include <mysql/mysql.h>

#include "../hsmmon_log.h"


typedef std::vector<std::string> m_sql_object;
typedef std::vector<m_sql_object>  m_sql_list;

void mes(const char *mess); 

class DBManager 
{ 
    public: 
        DBManager();
        DBManager(std::string hosts, std::string userName, std::string password, std::string dbName, unsigned int port); 
        virtual ~DBManager();

        void init_connect();
        void destory_connect();
        bool get_connect_status();

        int sql_execute(std::string sql);
        m_sql_list get_sql_res();

        static std::string sql_to_string(int t);
        static std::string sql_to_string(long int t);
        static std::string sql_time2string(time_t t);
        static time_t sql_string2time(std::string t);
        static int sql_sti(std::string);
        static long int sql_stli(std::string);

    protected:
        
        bool check_exist(unsigned int id, std::string tn);

        void set_hosts(std::string hosts);
        void set_username(std::string username);
        void set_password(std::string password);
        void set_dbname(std::string dbName);
        void set_port(unsigned int port);

    private:
        char *HOSTS;
        char *USERNAME;
        char *PASSWORD;
        char *DBNAME;
        unsigned int PORT;
        MYSQL mysql_con;
        //MYSQL_RES *mysql_res;
        bool is_connected;
        m_sql_list result_list;
}; 

#endif
