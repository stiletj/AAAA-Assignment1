#include <sol/sol.hpp>
#include <lua.hpp>

#pragma once

/**
 * @struct TestObj
 * @brief Structure representing a test object.
 */
struct TestObj
{
    int x; /**< Integer member variable. */
    std::string y; /**< String member variable. */
    bool z; /**< Boolean member variable. */

    /**
     * @brief Default constructor for TestObj.
     */
    TestObj();

    /**
     * @brief Gets the value of x.
     * @return The value of x.
     */
    int GetX();

    /**
     * @brief Gets the value of y.
     * @return The value of y.
     */
    std::string GetY();

    /**
     * @brief Gets the value of z.
     * @return The value of z.
     */
    bool GetZ();

    /**
     * @brief Checks if x is equal to a specified value.
     * @param _x The value to compare x with.
     * @return True if x is equal to _x, false otherwise.
     */
    bool IsEqual(int _x);
};

/**
 * @class Scripting
 * @brief Class responsible for managing Lua scripting.
 */
class Scripting
{
public:
    /**
     * @brief Default constructor for Scripting.
     */
    Scripting();

    /**
     * @brief Destructor for Scripting.
     */
    ~Scripting();

    /**
     * @brief Loads a Lua script file.
     * @param fileName The name of the Lua script file to load.
     * @return An integer representing the success status of the operation.
     */
    int LoadScript(std::string fileName);

    /**
     * @brief Gets a Lua variable from the Lua environment.
     * @tparam T The type of the variable to retrieve.
     * @param result Reference to store the retrieved variable.
     * @param varName The name of the variable in the Lua environment.
     */
    template<typename T>
    void GetLUAVariable(T& result, std::string varName);

    /**
     * @brief Sets a C++ function to be used in Lua.
     * @tparam func The type of the C++ function to set.
     * @param functionName The name of the function in Lua.
     * @param function The C++ function to set.
     */
    template<typename func>
    void SetCPPFunction(std::string functionName, func function);

    /**
     * @brief Sets a Lua function to be used in C++.
     * @tparam Return The return type of the Lua function.
     * @tparam Args The argument types of the Lua function.
     * @param name The name of the Lua function.
     * @param func The Lua function to set.
     */
    template<typename Return, typename... Args>
    void SetLUAFunction(std::string name, std::function<Return(Args...)>& func);

    /**
     * @brief Calls a Lua function with no output.
     * @tparam Args The argument types of the Lua function.
     * @param functionName The name of the Lua function to call.
     * @param args The arguments to pass to the Lua function.
     */
    template <typename... Args>
    void CallLUAFunction(const std::string& functionName, Args&&... args);

    /**
     * @brief Registers a C++ object with member functions to Lua.
     * @tparam Class The class type of the C++ object.
     * @tparam Args The argument types of the member functions.
     * @param className The name of the class in Lua.
     * @param args The member functions to register.
     */
    template<typename Class, typename... Args>
    void RegisterCppObject(std::string className, Args&&... args);

    /**
     * @brief Registers a C++ enum class to Lua.
     * @tparam Args The argument types of the enum class.
     * @param enumName The name of the enum class in Lua.
     * @param args The values of the enum class to register.
     */
    template<typename... Args>
    void RegisterCppEnum(std::string enumName, Args&&... args);

	void CloseState();

private:
    sol::state m_lua; /**< The Lua state. */
};

template<typename T>
void Scripting::GetLUAVariable(T& result, std::string varName)
{
	result = m_lua[varName];
}

template<typename func>
void Scripting::SetCPPFunction(std::string functionName, func function)
{
	m_lua.set_function(functionName, function);
}

template<typename Return, typename... Args>
void Scripting::SetLUAFunction(std::string name, std::function<Return(Args...)>& func)
{
	func = m_lua[name];
}

template<typename ...Args>
inline void Scripting::CallLUAFunction(const std::string& functionName, Args && ...args)
{
	m_lua[functionName](std::forward<Args>(args)...);
}








/*
template<typename Return, typename... Args>
bool Scripting::callLuaFunction(const std::string& functionName, Return& result, Args&&... args)
{
	// Get the Lua function by name
	sol::function luaFunction = m_lua[functionName];

	// Check if the Lua function exists
	if (luaFunction.valid())
	{
		sol::protected_function_result luaResult = luaFunction(std::forward<Args>(args)...);

		if (!luaResult.valid())
		{
			sol::error err = luaResult;
			std::cerr << "Error calling Lua function: " << err.what() << std::endl;
			return false;
		}

		// Check if the result can be converted to the specified type
		if constexpr (!std::is_void_v<Return>)
		{
			if (luaResult.can_be<Return>())
			{
				// Assign the result to the reference
				result = luaResult.as<Return>();
			}
			else
			{
				std::cerr << "Lua function returned value of incompatible type" << std::endl;
				return false;
			}
		}
		return false;
	}
	else
	{
		std::cerr << "Lua function '" << functionName << "' not found or invalid." << std::endl;
		return false;
	}
}

// Specialization for Lua functions with void return type and no arguments
template<typename... Args>
bool Scripting::callLuaFunctionVoid(const std::string& functionName, Args&&... args)
{
	// Retrieve the Lua function
	sol::function luaFunction = m_lua[functionName];
	if (luaFunction.valid())
	{
		// Call the Lua function with no arguments
		sol::protected_function_result luaResult = luaFunction(std::forward<Args>(args)...);
		if (!luaResult.valid())
		{
			sol::error err = luaResult;
			std::cerr << "Error calling Lua function: " << err.what() << std::endl;
			return false;
		}
		return true;
	}
	else
	{
		std::cerr << "Lua function '" << functionName << "' not found" << std::endl;
		return false;
	}
}
*/






template<typename Class, typename... Args>
void Scripting::RegisterCppObject(std::string className, Args&&... args)
{
	m_lua.new_usertype<Class>(className.c_str(), sol::constructors<void()>(),
		std::forward<Args>(args)...);
}

template<typename... Args>
void Scripting::RegisterCppEnum(std::string enumName, Args&&... args)
{
	m_lua.new_enum(enumName, std::forward<Args>(args)...);
}