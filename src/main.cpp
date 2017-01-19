

#include <iostream>
#include <unistd.h>

#include "StateTracker.h"
#include "ErrorHandler.h"
#include "DataLogger.h"

using std::cout;
using std::endl;

int main()
{
	cout << "starting error handler...\n";
	ErrorHandler handler;
	handler.StartThread();

	cout << "starting data logger...\n";
	DataLogger logger;
	logger.StartThread();

	cout << "starting state tracker...\n";
	StateTracker tracker;
	tracker.StartThread();

	while(true)
	{
		State data = tracker.getCurrentState();

		cout << "Current Distance: " << data.Displacement.x << endl;

		usleep(500000);
	}

	return 0;
}
