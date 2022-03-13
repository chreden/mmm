#include "Map_Internal.h"

namespace mmm
{
	namespace
	{
		Map map;
	}

	void 
	map_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Map>( "Map_" )
				.property( "min", &Map::getMin, &Map::setMin )
				.property( "max", &Map::getMax, &Map::setMax )
                .def( "getVisibility", &Map::getVisibility )
                .property( "Visibility", &Map::getVisibilityEnum )
                .scope
                [
                    class_<Map::eVisibility>( "Visibility" )
                        .enum_("constants")
                        [
                            value("Shrouded", Map::Shrouded),
                            value("Fogged", Map::Fogged),
                            value("Visible", Map::Visible)
                        ]
                ]
		];

		globals(state)["Map"] = &map;
	}
}