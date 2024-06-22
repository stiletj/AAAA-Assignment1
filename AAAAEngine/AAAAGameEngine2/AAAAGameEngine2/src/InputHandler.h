#pragma once

#include "GraphicsUtility.h"
#include "map"
#include <functional>

/**
 * @class InputHandler
 * @brief Class responsible for handling user input.
 */
class InputHandler
{
public:
    //BIND FUNCTIONS TO KEYS

    /**
     * @brief Binds a function to a keyboard key.
     * @param key The keyboard key to bind the function to.
     * @param func The function to be called when the key is pressed.
     */
    static void bindKey(GUKey key, std::function<void()> func1, std::function<void()> func2, std::function<void()> func3);

    /**
     * @brief Binds a function to a mouse button.
     * @param key The mouse button to bind the function to.
     * @param func The function to be called when the mouse button is pressed.
     */
    static void bindMouse(GUMouseButton key, std::function<void()> func1, std::function<void()> func2);
	static void bindMousePos(std::function<void(double, double)> func);
    void ClearBindings(GraphicsUtility::Window window);
    
    /**
     * @brief Constructs an InputHandler object and sets up key callbacks.
     * @param window The window associated with the input.
     */
    InputHandler() { }
    //sets keycallbacks
    InputHandler(GraphicsUtility::Window window);
    ~InputHandler();

    static double GetXPos() { return m_xPos; }
    static double GetYPos() { return m_yPos; }

private:
    /**
     * @brief Callback function for handling keyboard input.
     * @param window The window associated with the input.
     * @param key The keyboard key pressed.
     * @param scancode The scancode of the key.
     * @param action The action (press, release, repeat) of the key.
     * @param mods Modifier keys pressed.
     */
    static void handleInputKey(GraphicsUtility::Window window, int key, int scancode, int action, int mods);

    /**
     * @brief Callback function for handling mouse input.
     * @param window The window associated with the input.
     * @param button The mouse button pressed.
     * @param action The action (press, release) of the mouse button.
     * @param mods Modifier keys pressed.
     */
    static void handleInputMouse(GraphicsUtility::Window window, int button, int action, int mods);
    static void getMousePosition(GraphicsUtility::Window window, double xpos, double ypos);

    using KeyBindingData = std::tuple<std::function<void()>, std::function<void()>, std::function<void()>, bool>;
    static std::unordered_map<int, KeyBindingData> KeyBindings;
    
    using MouseBindingData = std::tuple<std::function<void()>, std::function<void()>, bool>;
    static std::unordered_map<int, MouseBindingData> MouseBindings;
    

    static double m_xPos;
    static double m_yPos;
    static std::function<void(double, double)> func;
    static double lastX;
    static double lastY;

};
inline double InputHandler::lastX;
inline double InputHandler::lastY;
inline double InputHandler::m_xPos;
inline double InputHandler::m_yPos;
inline std::function<void(double, double)> InputHandler::func;

inline std::unordered_map<int, InputHandler::MouseBindingData> InputHandler::MouseBindings;
inline std::unordered_map<int, InputHandler::KeyBindingData> InputHandler::KeyBindings;
