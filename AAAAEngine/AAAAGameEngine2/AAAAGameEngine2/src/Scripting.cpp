#include "Scripting.h"

TestObj::TestObj()
{
	x = 20;
	y = "Hello World";
	z = true;
}

bool TestObj::IsEqual(int _x)
{
	if (_x == x)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Scripting::Scripting() : m_lua()
{
	m_lua.open_libraries(sol::lib::base, sol::lib::math);
}

Scripting::~Scripting()
{
	
}

int Scripting::LoadScript(std::string fileName)
{
	try
	{
		m_lua.script_file(fileName);
	}
	catch (sol::error &e)
	{
		std::cerr << "Error: Failed to load the script: " << fileName << std::endl;

		return -1;
	}

	return 0;
}

void Scripting::CloseState()
{
	lua_close(m_lua);
}
