

#include <iostream>
#include <unistd.h>

#include "AIEngine.h"
#include "SystemGPIOs.h"
#include "ErrorHandler.h"
#include "DataLogger.h"

using std::cout;
using std::endl;

int main()
{
        ERROR_HANDLER->initialize("errors.log");
        ERROR_HANDLER->startThread();

        DATA_LOGGER->initialize();
        DATA_LOGGER->startThread();

        usleep(300000000); //5 mins

        SystemGPIOs IOs;

        AIEngine Controller;
        Controller.startThread();

        while(1)
                usleep(1000000);

        return 0;
}
