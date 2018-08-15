

#include <iostream>
#include <unistd.h>

#include "utils/ErrorHandler.h"
#include "utils/DataLogger.h"
#include "AUV.h"
#include "utils/Configuration.h"

void printCliUsage();
bool processCommandArgs(int numOfArgs, char** args);

int main(int argc, char** argv)
{
    if(argc > 1)
    {
        //TODO This is a terrible interface for this function
        // Need better mechanism for determining restarts
        if(processCommandArgs(argc, argv))
            return 1;
    }

    ERROR_HANDLER.initialize("errors.log");
    ERROR_HANDLER.startThread();

    DATA_LOGGER.initialize();
    DATA_LOGGER.startThread();

    AUV auv;

    auv.run();
    auv.shutdown();

    DATA_LOGGER.close();
    ERROR_HANDLER.close();

    return 0;
}


bool processCommandArgs(int numOfArgs, char** args)
{
    bool exitNeeded = false;

    for(int i = 1; i < numOfArgs; ++i)
    {
        std::string arg = args[i];

        if(arg == "-t")
        {
            ++i;
            std::string val = args[i];
            if(val == "test")
                CONFIG.setValue(VEHICLE_TYPE, "test_platform");
            else if(val == "sim")
                CONFIG.setValue(VEHICLE_TYPE, "simulation");
            else
            {
                printCliUsage();
                exitNeeded = true;
            }
        }
        if(arg == "-h")
        {
            printCliUsage();
            exitNeeded = true;
        }
        else
        {
            printCliUsage();
            exitNeeded = true;
        }
    }

    return exitNeeded;
}


void printCliUsage()
{
    std::cout << "Usage: command [OPTION]...\n" <<
            "\t-t\tSpecify the type of vehicle to use\n" <<
            "\t\tOptions are:\ttest\n\t\t\t\tsim\n\n" <<
            "\t-h\tPrint this message\n" << std::endl;
}
