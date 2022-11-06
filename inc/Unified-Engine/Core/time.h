#pragma once

namespace UnifiedEngine
{
    class TimeController{
    public:
        TimeController();
        ~TimeController();

    private:
		//Timer
		bool TimerOngoing = 0;
		float TimerStartTime = 0;

		float lastTime = 0;

    public:
        float DeltaTime = 0;
    
    public:
        //Tick
		void Update();

		//Return Main Time
		float Time();

		//Start Single Timer
		void StartTimer();

		//End Timer
		float EndTimer();

		//Read Current Timer Value
		float ReadTimerValue();
    };

    extern TimeController Time;
} // namespace UnifiedEngine
