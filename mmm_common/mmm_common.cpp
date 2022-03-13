#include "mmm_common.h"
#include <Windows.h>

namespace mmm
{
	namespace common
	{
		Storage::Storage( )
			: error( false ), 
			  updateTime( 0 ),
			  mainLuaVM( 0 ),
			  fleetops( INVALID_HANDLE_VALUE != GetModuleHandle( L"FleetOpsHook.dll" ) )
		{

		}

		Storage& Storage::instance( )
		{
			static Storage inst;
			return inst;
		}
	}
}
