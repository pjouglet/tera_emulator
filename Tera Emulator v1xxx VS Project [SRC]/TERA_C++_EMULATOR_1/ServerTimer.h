#ifndef SERVER_TIMER_H
#define SERVER_TIMER_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <mutex>
#include <thread>

class ServerTimer
{
public:
	struct ServerTime
	{
		float elapsedTime;
		float totalTime;

		ServerTime(float f1, float f2);
	};

	static uint64_t GetCurrentUTC();


};

#endif