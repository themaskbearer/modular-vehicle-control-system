

#include <iostream>
#include <unistd.h>

#include "AUV.h"


int main()
{
        // Since the GPIO are not in the correct state on power on, this allows for final configuration
        // of the vehicle before deployment where the motors aren't turning
        //usleep(300000000); // 5 mins

        AUV auv;

        auv.initialize();
        auv.run();
        auv.shutdown();

        return 0;
}
