/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-06-05 15:40
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/

#include "../include/ping_flow.h" 

PingFlow::PingFlow(): ObjectFoundation("pingflow")
{
    this->error_message = NULL;
}

PingFlow::PingFlow(int pingId, int sendPackage, int receivePackage, \
        int lostPackage, int minTime, int maxTime, int averageTime, \
        std::string errorMessage, time_t pingTime): ObjectFoundation("pingflow")
{
    this->set_ping_id(pingId);
    this->set_send_package(sendPackage);
    this->set_receive_package(receivePackage);
    this->set_lost_package(lostPackage);
    this->set_min_time(minTime);
    this->set_max_time(maxTime);
    this->set_average_time(averageTime);
    this->set_error_message(errorMessage);
    this->set_ping_time(pingTime);
    this->set_vaild();
}

PingFlow::~PingFlow()
{
    if ((this-> error_message) != NULL)
        delete this->error_message;
}

int PingFlow::get_average_time()
{
    return this->average_time;
}


std::string PingFlow::get_error_message()
{
    return this->error_message;
}


int PingFlow::get_lost_package()
{
    return this->lost_package;
}


int PingFlow::get_max_time()
{
    return this->max_time;
}


int PingFlow::get_min_time()
{
    return this->min_time;
}


int PingFlow::get_ping_id()
{
    return this->ping_id;
}


int PingFlow::get_receive_package()
{
    return this->receive_package;
}


int PingFlow::get_send_package()
{
    return this->send_package;
}


time_t PingFlow::get_ping_time()
{
    return this->ping_time;
}

bool PingFlow::get_alarm_flag()
{
    return this->alarm_flag;
}



int PingFlow::set_average_time(int averageTime)
{
    this->average_time = averageTime;
    return 0;
}


int PingFlow::set_error_message(std::string errorMessage)
{
    this->error_message = new char[errorMessage.length()+1];
    std::strcpy(this->error_message, errorMessage.c_str());    
    return 0;
}


int PingFlow::set_lost_package(int lostPackage)
{
    this->lost_package = lostPackage;
    return 0;
}


int PingFlow::set_max_time(int maxTime)
{
    this->max_time = maxTime;
    return 0;
}


int PingFlow::set_min_time(int minTime)
{
    this->min_time = minTime;
    return 0;
}


int PingFlow::set_ping_id(int pingId)
{
    this->ping_id = pingId;
    return 0;
}

int PingFlow::set_send_package(int sendPackage)
{
    this->send_package = sendPackage;
    return 0;
}


int PingFlow::set_ping_time(time_t pingTime)
{
    if (pingTime==0)
        time(&pingTime);
    this->ping_time = pingTime;
    return 0;
}


int PingFlow::set_receive_package(int receivePackage)
{
    this->receive_package = receivePackage;
    return 0;
}

int PingFlow::set_alarm_flag(bool alarmFlag)
{
    this->alarm_flag = alarmFlag;
    return 0;
}

std::string PingFlow::to_sql()
{
    char str[500];
    sprintf(str, "(`sendPackage`, `receivePackage`, `lostPackage`, `minTime`, `maxTime`, `averageTime`, `errorMessage`, 'pingTime') VALUES ('%d', '%d', '%d', '%d', '%d', '%d', '%s', 'FROM_UNIXTIME(%ld)')", \
            this->send_package, this->receive_package, this->lost_package, this->min_time, this->max_time, this->average_time, this->error_message, this->ping_time);
    return str;
}

std::string PingFlow::get_field(unsigned int pos)
{
    std::string str;
    switch (pos) { 
        case 0: {
            str = this->sql_to_string(this->ping_id); 
            break;
        } 
        case 1: {
             str = this->sql_to_string(this->send_package);
             break;
        } 
        case 2: {
            str = this->sql_to_string(this->receive_package);
            break;
        }
        case 3: {
            str = this->sql_to_string(this->lost_package);
            break;
        }
        case 4: {
            str = this->sql_to_string(this->min_time);
            break;
        }
        case 5: {
            str = this->sql_to_string(this->max_time);
            break;
        }
        case 6: {
            str = this->sql_to_string(this->average_time);
            break;
        }
        case 7: {
            str = std::string(this->error_message);
            break;
        }
        case 8: {
            str = this->sql_time2string(this->ping_time);
            break;
        }
        case 9: {
            str = this->sql_to_string(this->get_alarm_flag());
            break;
        }
        default: { 
            break; 
        }
    } 
    return str;
}

bool PingFlow::set_field(std::string str, unsigned int pos)
{
    switch (pos ) { 
         case 0: {
            int pingId = std::stoi(str, nullptr);
            this->set_ping_id(pingId);
            break;
        } 
        case 1: {
            this->set_send_package(std::stoi(str, nullptr));
            break;
        } 
        case 2: {
            this->set_receive_package(std::stoi(str, nullptr));
            break;
        }
        case 3: {
            this->set_lost_package(std::stoi(str, nullptr));
            break;
        }
        case 4: {
            this->set_min_time(std::stoi(str, nullptr));
            break;
        }
        case 5: {
            this->set_max_time(std::stoi(str, nullptr));
            break;
        }
        case 6: {
            this->set_average_time(std::stoi(str, nullptr));
            break;
        }
        case 7: {
            this->set_error_message(str);
            break;
        }
        case 8: {
            this->set_ping_time(this->sql_string2time(str));
            break;
        }
        case 9: {
            if (!str.empty())
                this->set_alarm_flag(stoi(str));
            break;
        }
        default: { 
            break;
        } 
    }
    return true;
}


bool PingFlow::create(DBManager &dbm)
{
    char sql[500];
    sprintf(sql, "INSERT INTO %s (`sendPackage`, `receivePackage`, `lostPackage`, `minTime`, `maxTime`, `averageTime`, `errorMessage`, 'pingTime') VALUES \
                                    ('%d', '%d', '%d', '%d', '%d', '%d', '%s', 'FROM_UNIXTIME(%ld)')", \
            this->get_table_name().c_str(),  this->send_package, this->receive_package, this->lost_package, this->min_time, this->max_time, this->average_time, this->error_message, this->ping_time);
    dbm.sql_execute(sql);
    return true;
}

bool PingFlow::update(DBManager &dbm)
{
    char sql[500];
    sprintf(sql, "UPDATE %s SET `sendPackage`='%d', `receivePackage`='%d', `lostPackage`='%d', `minTime`='%d', `maxTime`='%d', `averageTime`='%d', `errorMessage`='%s', `pingTime`='FROM_UNIXTIME(%ld)'WHERE `pingId`='%d';",\
            this->get_table_name().c_str(),  this->send_package, this->receive_package, this->lost_package, this->min_time, this->max_time, this->average_time, this->error_message, this->ping_time, this->ping_id);
    dbm.sql_execute(sql);
    return true;
}

bool PingFlow::erase(DBManager &dbm)
{
    char sql[500];
    sprintf(sql, "DELETE FROM %s WHERE `pingId`='%d';", this->get_table_name().c_str(), this->get_ping_id());
    dbm.sql_execute(sql);
    return true;
}


std::vector<ObjectFoundation*> PingFlow::find_all(DBManager &dbm)
{
    char sql[500];
    sprintf(sql, "SELECT * FROM %s;", this->get_table_name().c_str());
    std::cout << sql << std::endl;
    dbm.sql_execute(sql);
    m_sql_list sql_list = dbm.get_sql_res();
    m_sql_object sql_object;
    std::vector<ObjectFoundation*> pfl;
    if (sql_list.size()==0) {
        std::cout << "Object not found!" << std::endl;
    } else {
        m_sql_list::iterator iter = sql_list.begin();
        for (; iter != sql_list.end(); iter++) {
            pfl.push_back(this->to_object(*iter));
        }
    }
    return pfl;
}

ObjectFoundation* PingFlow::find_by_id(unsigned int id, DBManager &dbm)
{
    char sql[500];
    sprintf(sql, "SELECT * FROM %s WHERE `pingId`='%d';", this->get_table_name().c_str(), id);
    dbm.sql_execute(sql);
    m_sql_list sql_list = dbm.get_sql_res();
    m_sql_object sql_object;
    if (sql_list.size()==0) {
        std::cout << "Object not found!" << std::endl;
        return NULL;
    } else {
        m_sql_list::iterator iter = sql_list.begin();
        return to_object(*iter);
    }
}

ObjectFoundation* PingFlow::to_object(m_sql_object &sql_object)
{
    m_sql_object::iterator iter = sql_object.begin();
    PingFlow *pf = new PingFlow();
    unsigned int pos = 0;
    for ( ; iter != sql_object.end(); iter++) {
        pf->set_field(*iter, pos);
        pos++;
    }
    return pf;
}

std::string PingFlow::to_string()
{
    std::string str;
    for (unsigned int i=0; i<10; i++) {
        str += this->get_field(i)+"\t";
    }
    return str;
}



