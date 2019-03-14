#include "TimeManager.h"
#include "Director.h"

namespace Engine
{
	TimeManager::TimeManager()
	{
	}

	bool TimeManager::Init()
	{
		_SleepIsGranular = (timeBeginPeriod(_DesiredSchedulerMS) == TIMERR_NOERROR);

		_SetTargetSecondsPerFrame();

		LARGE_INTEGER i;

		if (!QueryPerformanceFrequency(&i))
			return false;

		_GlobalPerfCounterfrequency = i.QuadPart;

		QueryPerformanceCounter(&_LastCounter);
		TotalGameTime = 0;

		return true;
	}

	void TimeManager::Update()
	{
		LARGE_INTEGER i;
		QueryPerformanceCounter(&i);
		float secondsElapsedForFrame = GetSecondsElapsed(_LastCounter, i);

		if (secondsElapsedForFrame < _TargetSecondsPerFrame)
		{
			if (_SleepIsGranular)
			{
				DWORD SleepMS = (DWORD)(1000.0f * (_TargetSecondsPerFrame - secondsElapsedForFrame));
				if (SleepMS > 0)
				{
					Sleep(SleepMS);
				}
			}

			while (secondsElapsedForFrame < _TargetSecondsPerFrame)
			{
				QueryPerformanceCounter(&i);
				secondsElapsedForFrame = GetSecondsElapsed(_LastCounter, i);
			}
		}
		else
		{
			// TODO(marko): Logging
			//MessageBox(NULL, "Missed target frame rate!", NULL, NULL);
		}

		ElapsedGameTime = secondsElapsedForFrame;
		_LastCounter = i;
		TotalGameTime += ElapsedGameTime;
	}

	inline float TimeManager::GetSecondsElapsed(LARGE_INTEGER start, LARGE_INTEGER end)
	{
		return ((float)(end.QuadPart - start.QuadPart) / (float)_GlobalPerfCounterfrequency);
	}

	void TimeManager::_SetTargetSecondsPerFrame()
	{
		int monitorRefreshHz = 60;
		HDC refreshDC = GetDC(Director::getInstance()->GetWindowHandle());
		int win32RefreshRate = GetDeviceCaps(refreshDC, VREFRESH);
		ReleaseDC(Director::getInstance()->GetWindowHandle(), refreshDC);
		if (win32RefreshRate > 1)
		{
			monitorRefreshHz = win32RefreshRate;
		}
		float gameUpdateHz = (monitorRefreshHz / 2.0f);
		_TargetSecondsPerFrame = 1.0f / (float)gameUpdateHz;
	}
}
