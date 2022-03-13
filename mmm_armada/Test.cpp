#include "Test.h"
#include "PrintMessages.h"
#include "DebuggerConnection.h"

namespace mmm
{
	void
	Test::isTrue( bool condition, const std::string& message ) const
	{
		if( !condition )
		{
			throw AssertionFailureException(message);
		}
	}

	void
	Test::isFalse( bool condition, const std::string& message ) const
	{
		isTrue( !condition, message );
	}

	void
	Test::add( const std::string& name, luabind::object table, luabind::object function )
	{
		tests_.push_back( TestEntry( name, table, function ) );
	}

	void
	Test::runAll( )
	{
		std::for_each( tests_.begin(), tests_.end(), std::mem_fun_ref(&TestEntry::run) );
	}

	Test::TestEntry::TestEntry( const std::string& name, luabind::object table, luabind::object function )
		: name_( name ), table_( table ), function_( function )
	{
		
	}

	void
	Test::TestEntry::run() const
	{
		using namespace luabind;
		try
		{
			if( table_.is_valid( ) &&
				type( table_ ) != LUA_TNIL )
			{
				call_function<void>( table_, function_ );
			}
			
			call_function<void>( function_ );

			PrintMessages::add( "Pass:" + name_, DebuggerConnection::Type_Test );
		}
		catch( const luabind::error& e )
		{
			std::string actualError = lua_tostring( common::Storage::instance().mainLuaVM, -1 );
			std::size_t startIndex = actualError.find_first_of('\'');
			std::size_t endIndex = actualError.find_last_of('\'');

			if( !(startIndex == actualError.npos ||
				  endIndex == actualError.npos ))
			{
				actualError = actualError.substr(startIndex + 1, endIndex - startIndex - 1);
			}

			PrintMessages::add( "Fail:" + name_ + ":" + actualError, DebuggerConnection::Type_Test );
		}
	}
}
