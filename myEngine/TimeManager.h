#pragma once
#include <Windows.h>
#include <stdint.h>

namespace Engine
{
	class TimeManager
	{
	public:
		TimeManager();
		float ElapsedGameTime;
		float TotalGameTime;

		bool Init();
		void Update();
		inline float GetSecondsElapsed(LARGE_INTEGER start, LARGE_INTEGER end);
	private:
		void _SetTargetSecondsPerFrame();
		float _TargetSecondsPerFrame;
		LARGE_INTEGER _LastCounter;
		int64_t _GlobalPerfCounterfrequency;
		const UINT _DesiredSchedulerMS = 1;
		bool _SleepIsGranular;
	};
}