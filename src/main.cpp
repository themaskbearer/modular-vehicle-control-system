

#include <iostream>
#include <unistd.h>

#include "AIEngine.h"
#include "SystemGPIOs.h"
#include "utils/ErrorHandler.h"
#include "utils/DataLogger.h"


int main()
{
        ERROR_HANDLER->initialize("errors.log");
        ERROR_HANDLER->startThread();

        DATA_LOGGER->initialize();
        DATA_LOGGER->startThread();

        // Since the GPIO are not in the correct state on power on, this allows for final configuration
        // of the vehicle before deployment where the motors aren't turning
        usleep(300000000); // 5 mins

        AIEngine Controller;
        Controller.startThread();

        while(1)
            usleep(1000000);    // 1 sec

        DATA_LOGGER->close();
        ERROR_HANDLER->close();

        return 0;
}
