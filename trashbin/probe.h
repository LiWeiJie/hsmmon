/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-06-01 21:42
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/
#ifndef PROBE_H
#define PROBE_H

class probe_t 
{ 
    public: 
        probe_t(); 
        virtual ~probe_t(); 

        int get_probes(probe_t *probes, unsigned int &nums);

    private: 
        int id;
        char *ip;
        static constexpr char table_name[] = "probe";

}; 


#endif
