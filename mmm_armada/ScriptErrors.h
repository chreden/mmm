#pragma once

namespace mmm
{
	void scriptError( const std::string& error, bool stop = true );
		
	template < typename T >
	void makeRangeError( lua_State* state, const std::string& functionName,
		int index, const T& value, const std::string& range );
		
	template < typename T >
	void makeTypeError( lua_State* state, const std::string& functionName, int index );

	void reportError( const std::string& functionName, const std::string& error );
}

#include "ScriptErrors.inl"
