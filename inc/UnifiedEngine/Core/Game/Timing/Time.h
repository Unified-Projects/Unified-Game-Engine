#pragma once

//Includes
#include "../../OpenGL/OpenGLInc.h"

namespace UnifiedEngine {
	class TimeClass {
	private:
		//Timer
		bool TimerOngoing;
		float TimerStartTime;

		float lastTime;
	public:
		//Main DeltaTime
		float deltaTime;

		//Tick
		void Update() {
			//Get Change in Time
			float currentTime = static_cast<float>(glfwGetTime());
			this->deltaTime = currentTime - this->lastTime;
			this->lastTime = currentTime;
		}

		//Return Main Time
		float Time() {
			return static_cast<float>(glfwGetTime());
		}

		//Start Single Timer
		void StartTimer() {
			this->TimerOngoing = true;
			this->TimerStartTime = this->Time();
		}

		//End Timer
		float EndTimer() {
			this->TimerOngoing = false;
			return this->Time() - this->TimerStartTime;
		}

		//Read Current Timer Value
		float ReadTimerValue() {
			return this->Time() - this->TimerStartTime;
		}
	};

//Only Init One
#ifndef TIME_Init
#define TIME_Init
	static TimeClass Time;
#endif
}