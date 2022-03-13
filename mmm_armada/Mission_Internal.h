#pragma once

namespace mmm
{
	class Mission
	{
	public:
		void end( bool success, float delay );
	};

	void mission_register( lua_State* state );
}
