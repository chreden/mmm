#pragma once

namespace mmm
{
	bool application_isCineractive() noexcept;
	void application_setup();
	void application_update();
	void application_resume();
	void application_cineractiveBegin();
	void application_cineractiveFinish( bool forced );
	void application_register( lua_State* state );
}
