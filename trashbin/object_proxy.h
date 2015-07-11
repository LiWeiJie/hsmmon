/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-06-09 12:20
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/
#ifndef OBJECTPROXY_H
#define OBJECTPROXY_H

#include "dbmanager.h" 
#include "object_foundation.h" 

class ObjectProxy 
{ 
    public: 
        ObjectProxy(); 
        virtual ~ObjectProxy(); 

        bool creat(ObjectFoundation *tb);
        bool update(ObjectFoundation *tb);
        bool erase(ObjectFoundation *tb);
        
        ObjectFoundation* find_by_id(unsigned int id);
        ObjectFoundation* find_all(unsigned int &num);
        

    private:
        DBManager dbc;
}; 


#endif
