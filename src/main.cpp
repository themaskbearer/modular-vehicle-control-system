

#include <iostream>
#include <unistd.h>

#include "AUV.h"


int main(int argc, char** argv)
{
    if(argc > 1)
    {
        std::cout << "Woo arguments!" << std::endl;
    }

    AUV auv;

    auv.initialize();
    auv.run();
    auv.shutdown();

    return 0;
}
