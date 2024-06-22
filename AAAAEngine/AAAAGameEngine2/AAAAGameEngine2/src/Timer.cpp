#include "Timer.h"

float Timer::GetDeltaTime() const
{
    return m_deltaTime;
}

void Timer::Update()
{
    auto now = std::chrono::high_resolution_clock::now();
    m_deltaTime = std::chrono::duration<float>(now - m_lastFrameTime).count();
    m_lastFrameTime = now;
}