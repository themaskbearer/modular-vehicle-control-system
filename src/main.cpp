

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
        ErrorHandler handler;
        handler.StartThread();

        DataLogger logger;
        logger.StartThread();

        usleep(300000000); //5 mins

        SystemGPIOs IOs;

        AIEngine Controller;
        Controller.StartThread();

        while(1)
                usleep(1000000);

        return 0;
}
