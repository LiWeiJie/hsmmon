/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-06-05 15:32
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/
#ifndef PINGFLOW_H
#define PINGFLOW_H

#include "object_foundation.h" 
#include <unistd.h> 
#include <ctime> 

class PingFlow : public ObjectFoundation
{ 
    public: 
        PingFlow();
        PingFlow(int pingId, int pingPackage, int receivePackage, \
                int lostPackage, int minTime, int maxTime, int averageTime, \
                std::string errorMessage, time_t pingTime); 
        virtual ~PingFlow();
        virtual std::string to_sql();
        virtual std::string get_field(unsigned int pos);
        virtual bool set_field(std::string str, unsigned int pos);

        virtual bool create(DBManager &dbm);
        virtual bool update(DBManager &dbm);
        virtual bool erase(DBManager &dbm);
        
        virtual ObjectFoundation* find_by_id(unsigned int id, DBManager &dbm);
        virtual std::vector<ObjectFoundation*> find_all(DBManager &dbm);

        std::string to_string();

    protected:
        int get_ping_id();
        int set_ping_id(int pingId);
        int get_send_package();
        int set_send_package(int sendPackage);
        int get_receive_package();
        int set_receive_package(int receivePackage);
        int get_lost_package();
        int set_lost_package(int lostPackage);
        int get_min_time();
        int set_min_time(int minTime);
        int get_max_time();
        int set_max_time(int maxTime);
        int get_average_time();
        int set_average_time(int averageTime);
        std::string get_error_message();
        int set_error_message(std::string errorMessage);
        time_t get_ping_time();
        int set_ping_time(time_t pingTime);
        bool get_alarm_flag();
        int set_alarm_flag(bool alarmFlag);

    private:
        static ObjectFoundation* to_object(m_sql_object &sql_object);
        int ping_id;
        int send_package;
        int receive_package;
        int lost_package;
        int min_time;
        int max_time;
        int average_time;
        char * error_message;
        time_t ping_time;
        bool alarm_flag;
}; 


#endif
