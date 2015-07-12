/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-05-28 16:26
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/
#include "include/db/dbmanager.h"

void mes(const char *mess) { std::cout << mess << std::endl;return;}

DBManager::DBManager()
{
    this->is_connected = false;    
    this->set_hosts("127.0.0.1");
    this->set_username("root");
    this->set_password("root");
    this->set_dbname("hsmmon");
    this->set_port(3306);
}

DBManager::DBManager(std::string hosts, std::string userName, std::string password, std::string dbName, unsigned int port)
{
    this->is_connected = false;
    this->set_hosts(hosts);
    this->set_username(userName);
    this->set_password(password);
    this->set_dbname(dbName);
    this->set_port(port);
}


void DBManager::init_connect()
{
    if ( is_connected ) {//    已经连接到服务器    
        std::cout << "Is connected to server!" <<std::endl;    
        return;    
    }   

    //mes(HP.c_str());
    //mes(this->USERNAME);
    //mes(this->PASSWORD);
    mysql_init(&this->mysql_con);
    if (mysql_real_connect(&this->mysql_con, this->HOSTS, this->USERNAME, \
        this->PASSWORD, this->DBNAME, this->PORT, NULL, 0)) {
        mes("Connected");
        is_connected = true;
    } else {
        std::cout << "Error connection to database"  << std::endl;    
    }
    return ;
}


void DBManager::destory_connect()
{
    if (is_connected)
        mysql_close(&mysql_con);
    is_connected = false;
    return;
}


bool DBManager::get_connect_status()
{
    return this->is_connected;
}


void DBManager::set_dbname(std::string dbName)
{
    if ( dbName.empty() ) {//        用户没有指定数据库名    
        std::cout << "DBName is null! Used default value: mysql" << std::endl;    
        this ->DBNAME = new char[6];    
        strcpy(this ->DBNAME, "mysql");    
    } else {    
        this ->DBNAME = new char[dbName.length()+1];    
        strcpy(this ->DBNAME, dbName.c_str());    
    }     
    return /* something */;
}


void DBManager::set_hosts(std::string hosts)
{
    if (hosts.empty()) {
        std::cout << "HOSTS is null! Used default value: localhost" << std::endl;
        this -> HOSTS = new char[10];
        strcpy(this->HOSTS, "localhost");
    } else {
        this -> HOSTS = new char[hosts.length()+1];
        strcpy(this -> HOSTS, hosts.c_str());
    }
    return ;
}


void DBManager::set_password(std::string password)
{
    if ( password.empty() ) {    
        std::cout << "Password is null! Used default value: " << std::endl;    
        this ->PASSWORD = new char[1];    
        strcpy(this ->PASSWORD, "");    
    } else {    
        this ->PASSWORD = new char[password.length()+1];    
        strcpy(this ->PASSWORD, password.c_str());    
    }    
    return ;
}


void DBManager::set_port(unsigned int port)
{
    this->PORT = port;    
    return ;
}


void DBManager::set_username(std::string userName)
{
    if ( userName.empty()) {    
        std::cout << "UserName is null! Used default value: root" << std::endl;    
        this ->USERNAME = new char[4];    
        strcpy(this ->USERNAME, "root");    
    } else {    
        this ->USERNAME = new char[userName.length()];    
        strcpy(this ->USERNAME, userName.c_str());    
    }    
    return ;
}

int DBManager::sql_execute(std::string sql)
{
    hlog("sql execulting:");
    hlog(sql.c_str());
    if ( !is_connected ) {//    没有连接到服务器    
        std::cout << "Not connect to database!" << std::endl;    
        return false;    
    }    
    if ( sql.empty()) {//    SQL语句为空    
        std::cout << "SQL is null!" << std::endl;    
        return false;    
    }    
   
    
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int j;

    if( !mysql_query(&mysql_con, sql.c_str())) {
        mes("sql success");
        res = mysql_store_result(&mysql_con);    
        this -> result_list.clear();
        if (res == NULL) return 0;
        m_sql_object objectValue; 
        unsigned int fields_num = mysql_num_fields(res);   
        while( (row = mysql_fetch_row(res)) ) {//    遍历结果集    
            objectValue.clear();    
            for ( j = 0 ; j < fields_num ; j++ ) {    
                if (row[j]!=NULL) {
                    //printf("%s\n", row[j]);
                    objectValue.push_back(row[j]);   
                } else {
                    //printf("NULL\n");
                    objectValue.push_back("");
                } 
            }    
            this -> result_list.push_back(objectValue);    
        }            
        mes("result stored");
        mysql_free_result(res);         //free result after you get the result    
    } else 
        mes("sql failed");
    return 0;    
}

m_sql_list DBManager::get_sql_res()
{
    return this -> result_list;
}


DBManager::~DBManager()
{
    if (HOSTS != NULL) 
        delete(HOSTS);
    if (USERNAME != NULL)
        delete(USERNAME);
    if (PASSWORD != NULL)
        delete(PASSWORD);
    if (DBNAME != NULL)
        delete(DBNAME);
    is_connected = false;
    this->destory_connect();
}



std::string DBManager::sql_to_string(int t)
{
    return std::to_string(t);
}

std::string DBManager::sql_to_string(long int t)
{
    return std::to_string(t);
}

std::string DBManager::sql_time2string(time_t t)
{
    char buffer[256];
    struct tm *time_info;
    time_info = localtime(&t);
    strftime(buffer, 256, "%Y-%m-%d %H:%M:%S", time_info);
    return buffer;
}

time_t DBManager::sql_string2time(std::string t)
{
    struct tm time_info;
    memset(&time_info, 0, sizeof(struct tm));
    strptime(t.c_str(), "%Y-%m-%d %H:%M:%S", &time_info); 
    return mktime(&time_info);
}

int DBManager::sql_sti(std::string str)
{
    return std::stoi(str);
}

long int DBManager::sql_stli(std::string str)
{
    return std::stoi(str);
}

