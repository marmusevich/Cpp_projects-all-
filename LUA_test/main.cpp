#include <iostream>
#include <lua.hpp>

using namespace std;


int main()
{
    lua_State *L = NULL;

    L = luaL_newstate();

    luaL_openlibs(L);//подключить стандартные библиотеки

    int status = luaL_loadfile(L, "script.lua");//загрузить файл
    /* Состояние стtка:
        [-1]main <--top of the stack
     */
    if (status)
    {
        (void)fprintf(stderr, "file not found\n");
        return 1;
    }
	int result = lua_pcall(L, 0, LUA_MULTRET, 0);

    lua_close(L);
	return 0;
}
