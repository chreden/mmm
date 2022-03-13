#pragma once

#include "UIMessage.h"

namespace mmm
{
	//Used for User Interface messages and other effects
	class UI
	{
	public:
		int addMessage( const std::string& text, int x, int y, eJustify justify,
			const ST3D_Colour& colour, bool fade, float displayTime );
		int addTitle( const std::string& str, int x, int y, float time, bool fade );
		int addSubtitle( const std::string& str, int x, int y, float time, bool fade );
		void removeMessage( const UIMessage& message );
		void removeMessage( int id );
		void fadeMessage( const UIMessage& message );
		void addMinimapMark( const Vector3& pos, int radius, float shrinkRate, const ST3D_Colour& color );
		void update( );
		void showTradesTo( TeamPtr player );
		const std::string getTeamText() const;
		void setTeamText( const std::string& text );
		luabind::object getJustify() const;
	private:
		//Justify enumeration - this is required as we are using a global
		//instance and the enum is now local scoped.
		mutable luabind::object			justify_;
	};
	
	void ui_register( lua_State* state );
}