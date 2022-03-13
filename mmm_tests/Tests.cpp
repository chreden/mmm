#include <iostream>
#include <string>
#include <Windows.h>
#include <process.h>

#include "..\mmm_luapack\LuaPack.h"
#include "..\luabind\luabind\luabind.hpp"

#ifdef _DEBUG
	#pragma comment( lib, "..\\bin\\mmm_luapack_d.lib" )
	#pragma comment( lib, "..\\lua\\lib\\lua5.1.lib" )
	#pragma comment( lib, "..\\luabind\\debug\\luabind.lib" )
#else
	#pragma comment( lib, "..\\bin\\mmm_luapack.lib" )
	#pragma comment( lib, "..\\lua\\lib\\lua5.1.lib" )
	#pragma comment( lib, "..\\luabind\\release\\luabind.lib" )
#endif

lua_State* state  = 0;

void
print( const std::string& str )
{
	std::cout << str << '\n';
}

HANDLE signal = INVALID_HANDLE_VALUE;

std::string
testThis()
{
	WaitForSingleObject( signal, INFINITE );
	return "Happy Days";
}

void
doStuff( void* )
{
	using namespace luabind;
	state = lua_open();
	open( state );

	module( state )
	[
		def("print", &print),
		def("test", testThis)
	];

	try
	{
		luaL_dofile( state, "script.lua" );
	}
	catch( luabind::error& )
	{
		std::cout << lua_tostring( state, -1 ) << '\n';
	}

	lua_close( state );
}

int main( )
{
	signal = CreateEvent( 0, TRUE, FALSE, 0 );

	_beginthread( doStuff, 0, 0 );
	
	bool inCineractive = true;
	while( inCineractive )
	{
		if( GetAsyncKeyState( VK_SPACE ) )
		{
			inCineractive = false;
		}
	}
	SetEvent( signal );

	std::cin.get();

	CloseHandle( signal );

	return 0;
}
