#pragma once

#include <chrono>

/**
 * @brief A class for managing time-related functionalities in a game engine.
 */
class Timer {
public:
    /**
     * @brief Returns the singleton instance of the Timer class.
     * @return Reference to the Time instance.
     */
    static Timer& Instance() {
        static Timer instance;
        return instance;
    }

    /**
     * @brief Calculates and updates the delta time.
     *
     * This function should be called once per frame to update the delta time.
     */
    void Update();

    /**
     * @brief Gets the delta time since the last frame.
     *
     * @return The delta time in seconds.
     */
    float GetDeltaTime() const;

private:
    /**
     * @brief Constructs a new Timer object and initializes the last frame time.
     */
    Timer() : m_lastFrameTime(std::chrono::high_resolution_clock::now()), m_deltaTime(0.f) {}

    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastFrameTime; /**< The time point of the last frame. */
    float m_deltaTime; /**< The delta time since the last frame. */
};


