#pragma once

namespace mmm
{
	void include(const std::string& fn);
	void globals_register( lua_State* state ) noexcept;
}
