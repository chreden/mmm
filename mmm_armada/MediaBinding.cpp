#include "Media_Internal.h"

namespace mmm
{
	namespace
	{
		Media media;
	}

	void
	media_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Media>( "_Media" )
				.def( "playSound", &Media::playSound )
				.def( "playMusic", &Media::playMusic )
				.def( "playMovie", &Media::playMovie )
				.def( "stopMovie", &Media::stopMovie )
				.def( "stopMusic", &Media::stopMusic )
				.def( "stopSounds", &Media::stopSounds )
		];

		globals(state)["Media"] = &media;
	}
}