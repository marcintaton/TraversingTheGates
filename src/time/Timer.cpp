#include "Timer.h"
#include <GLFW/glfw3.h>

float Timer::delta_time;

Timer::Timer() {}

Timer::~Timer() {}

void Timer::update_timer()
{
    Timer::delta_time = glfwGetTime() - last_frame_timestamp;
    last_frame_timestamp = glfwGetTime();
}