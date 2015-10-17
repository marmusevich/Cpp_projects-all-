#include "stdafx.h"
#include "AIBase.h"
#include "Utils.h"

using namespace std;
using namespace luabind;

lua_State *myLuaState = 0;
//! ����� ����� ������, ����������� �� ���
std::vector<string> vecEnemyTypes;

bool InitScripts()
{
	myLuaState = lua_open();
	luabind::open(myLuaState);
	 
	// Define a lua function that we can call
	luaL_dostring(myLuaState, GetFileAsString("ai.lua").c_str());

	// ���������� ��� ���������� ���������� (� ������� ��� �� �����)
	const luabind::object& objects = luabind::globals(myLuaState);
	for (luabind::iterator itr(objects); itr!=luabind::iterator(); itr++)
	{
		const luabind::object& obj = (*itr);
		if ( type( obj ) == LUA_TTABLE ) // ��� �����������
		{
			// ���������� ������ � ���� �������
			for (luabind::iterator itr2(obj); itr2!=luabind::iterator(); itr2++)
			{
				// ��� ����������, �������� ��� ����� �� ��������?
				if (luabind::object_cast<std::string>(itr2.key()).compare("sprite")==0)
				{
					luabind::object key = itr.key(); // ���� ����
					std::string name = luabind::object_cast<std::string>(key);
					vecEnemyTypes.push_back(name);
				}
			}
		}
	}
	return true;
}