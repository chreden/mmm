#include "UI_Internal.h"

namespace mmm
{
	namespace 
	{
		UI ui;
	}

	void
	ui_register( lua_State* state )
	{
		using namespace luabind;

		module( state )
		[
			class_<UI>( "_UI" )
				.def( "addMessage", &UI::addMessage )
				.def( "addMinimapMark", &UI::addMinimapMark )
				.def( "showTradesTo", &UI::showTradesTo )
				.def( "addTitle", &UI::addTitle )
				.def( "addSubtitle", &UI::addSubtitle )
				.property( "teamText", &UI::getTeamText, &UI::setTeamText )
				.property( "Justify", &UI::getJustify )
				.scope
				[
					class_<eJustify>("Justify")
						.enum_("constants")
						[
							value("TopLeft", JUSTIFY_TOP_LEFT),
							value("TopRight", JUSTIFY_TOP_RIGHT),
							value("TopCenter", JUSTIFY_TOP_CENTER),
							value("BottomLeft", JUSTIFY_BOTTOM_LEFT),
							value("BottomRight", JUSTIFY_BOTTOM_RIGHT),
							value("BottomCenter", JUSTIFY_BOTTOM_CENTER),
							value("CenterLeft", JUSTIFY_CENTER_LEFT),
							value("CenterRight", JUSTIFY_CENTER_RIGHT),
							value("Center", JUSTIFY_CENTER),
							value("TopLeftByLine", JUSTIFY_TOP_LEFT_BY_LINE),
							value("TopRightByLine", JUSTIFY_TOP_RIGHT_BY_LINE),
							value("TopCenterByLine", JUSTIFY_TOP_CENTER_BY_LINE),
							value("BottomLeftByLine", JUSTIFY_BOTTOM_LEFT_BY_LINE),
							value("BottomRightByLine", JUSTIFY_BOTTOM_RIGHT_BY_LINE),
							value("BottomCenterByLine", JUSTIFY_BOTTOM_CENTER_BY_LINE),
							value("CenterLeftByLine", JUSTIFY_CENTER_LEFT_BY_LINE),
							value("CenterRightByLine", JUSTIFY_CENTER_RIGHT_BY_LINE),
							value("CenterByLine", JUSTIFY_CENTER_BY_LINE)
						]
				]
		];

		globals( state )[ "UI" ] = &ui;
	}
}