#include <Unified-Engine/Core/time.h>
#include <Unified-Engine/includeGL.h>

using namespace UnifiedEngine;

TimeController UnifiedEngine::Time;

TimeController::TimeController(){

}
TimeController::~TimeController(){
    
}

//Tick
void TimeController::Update() {
    //Get Change in Time
    float currentTime = static_cast<float>(glfwGetTime());
    this->DeltaTime = currentTime - this->lastTime;
    this->lastTime = currentTime;
}

//Return Main Time
float TimeController::Time() {
    return static_cast<float>(glfwGetTime());
}

//Start Single Timer
void TimeController::StartTimer() {
    this->TimerOngoing = true;
    this->TimerStartTime = this->Time();
}

//End Timer
float TimeController::EndTimer() {
    this->TimerOngoing = false;
    return this->Time() - this->TimerStartTime;
}

//Read Current Timer Value
float TimeController::ReadTimerValue() {
    return this->Time() - this->TimerStartTime;
}