/**************************************************************
* Copyright (C) 2006-2015 All rights reserved.
* @Version: 1.0
* @Created: 2015-06-01 20:47
* @Author: liweijie – licatweijie@gmail.com
* @Description: 
*
* @History: 
**************************************************************/
#ifndef HSM_H
#define HSM_H

class hsm_t
{
    public:
        hsm_t();
        virtual ~hsm_t();
        int set_ping_status(const hsm_t hsm, int pingId, int sendPackage,\
                int receivePackage, int lostPackage, int minTime, int maxTime,\
                int averageTime, char* errorMessage, long long int pingTime );

        int get_hsms(hsm_t *hsms, unsigned int &nums);

    private:
        int id;
        char *ip;
        static constexpr char table_name[] = "hsm"; 

};



#endif
