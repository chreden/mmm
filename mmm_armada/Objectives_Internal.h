#pragma once

#include "VectorAdapter.h"

namespace mmm
{
	namespace types
	{
		class ObjectivesText;
	}

	class Objectives
	{
	public:
		explicit Objectives( );
		int getCount() const;

		const std::string getSummaryTitle() const;
		const std::string getObjectivesTitle() const;
		const std::string getObjectivesText() const;
		const std::string getObjectivesHeader() const;

		void setSummaryTitle( const std::string& text );
		void setObjectivesTitle( const std::string& text );
		void setObjectivesText( const std::string& text );
		void setObjectivesHeader( const std::string& text );

		void addObjective( const std::string& text );
		void removeObjective( int index );

		bool getObjectiveState( int index ) const;
		const std::string getObjective( int index ) const;

		void setObjectiveState( int index, bool value );
		void setObjective( int index, const std::string& value );

		void load( const std::string& filename );

		bool getShow( ) const;
		void setShow( bool value );

		luabind::object getObjectiveValues() const;
	};

	void objectives_register( lua_State* state );
}
