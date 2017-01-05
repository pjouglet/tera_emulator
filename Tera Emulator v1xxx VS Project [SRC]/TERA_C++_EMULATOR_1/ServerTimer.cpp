#include "ServerTimer.h"
#include <chrono>


uint64_t ServerTimer::GetCurrentUTC()
{
	long long t;
	time(&t);
	return (uint64_t)t;
}

ServerTimer::ServerTime::ServerTime(float f1, float f2)
{
	elapsedTime = f1;
	totalTime = f2;
}
