#include <vector>
#include <string>
#include <luabind\luabind.hpp>

#ifdef _DEBUG
#pragma comment(lib, "lua-debug.lib")
#pragma comment(lib, "luabind-debug.lib")
#else
#pragma comment(lib, "lua.lib")
#pragma comment(lib, "luabind.lib")
#endif

extern lua_State *myLuaState;
extern std::vector<std::string> vecEnemyTypes;
bool InitScripts();