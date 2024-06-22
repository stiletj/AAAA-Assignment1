#include "InputHandler.h"

using KeyBindingData = std::tuple<std::function<void()>, std::function<void()>, std::function<void()>, bool>;
using MouseBindingData = std::tuple<std::function<void()>, std::function<void()>,  bool>;

void InputHandler::bindKey(GUKey key, std::function<void()> func1, std::function<void()> func2, std::function<void()> func3)
{
	KeyBindingData data = std::make_tuple(func1, func2, func3, false);
	KeyBindings[key] = data;
}
void InputHandler::bindMouse(GUMouseButton key, std::function<void()> func1, std::function<void()> func2)
{
	MouseBindingData data = std::make_tuple(func1, func2, false);
	MouseBindings[key] = data;
}

void InputHandler::bindMousePos(std::function<void(double, double)> func)
{
	InputHandler::func = func;
}

void InputHandler::handleInputKey(GraphicsUtility::Window window, int key, int scancode, int action, int mods)
{
	if (KeyBindings.find(key) != KeyBindings.end())
	{
		KeyBindingData& data = KeyBindings[key];
		if (glfwGetKey(window, key) == GLFW_PRESS)
		{
			std::get<0>(data)();
			std::get<3>(data) = true;
		}
		if (glfwGetKey(window, key) == GLFW_RELEASE && std::get<3>(data) == true)
		{
			std::get<1>(data)();
			std::get<3>(data) = false;
		}
		if (glfwGetKey(window, key) == GLFW_REPEAT)
		{
			std::get<2>(data)();
		}
	}
}

void InputHandler::handleInputMouse(GraphicsUtility::Window window, int button, int action, int mods)
{
	if (MouseBindings.find(button) != MouseBindings.end())
	{
		MouseBindingData& data = MouseBindings[button];
		if (glfwGetMouseButton(window, button) == GLFW_PRESS)
		{
			std::get<0>(data)();
			std::get<2>(data) = true;
		}
		if (glfwGetMouseButton(window, button) == GLFW_RELEASE && std::get<2>(data) == true)
		{
			std::get<1>(data)();
			std::get<2>(data) = false;
		}
	}
}

InputHandler::InputHandler(GraphicsUtility::Window window)
{
	glfwSetKeyCallback(window, handleInputKey);
	glfwSetMouseButtonCallback(window, handleInputMouse);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, InputHandler::getMousePosition);
}

InputHandler::~InputHandler()
{
	
}

void InputHandler::ClearBindings(GraphicsUtility::Window window)
{
	glfwSetKeyCallback(window, nullptr);
	glfwSetMouseButtonCallback(window, nullptr);
	KeyBindings.clear();
	MouseBindings.clear();
}

void InputHandler::getMousePosition(GraphicsUtility::Window window, double xpos, double ypos)
{
	if (func)
	{
		double x, y;
		x = xpos;
		y = ypos;

		double xOffset = x - lastX;
		double yOffset = lastY - y; // Reversed since y-coordinates go from bottom to top

		lastX = x;
		lastY = y;

		func(xOffset, yOffset);
	}
}
