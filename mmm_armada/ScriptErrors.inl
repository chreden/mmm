#pragma once

namespace mmm
{
	template < typename T >
	void makeTypeError( lua_State* state, const std::string& functionName, int index )
	{
		std::string error = std::string( "Wrong argument type to " ) + 
							functionName + ". Arg " + typeToString( index ) + 
							", got " + getTypeInfo( state, index ) + ", expected " + 
							getTypeInfo<T>( state ) ;
		lua_pushstring( state, error.c_str( ) );
		lua_error( state );
	}

	template < typename T >
	void makeRangeError( lua_State* state, const std::string& functionName,
		int index, const T& value, const std::string& range )
	{
		std::string error = std::string( "Invalid argument value to " ) +
							functionName + ". Arg " + typeToString(index) + 
							", got " + typeToString(value) + ", expected in " +
							range;
		lua_pushstring( state, error.c_str( ) );
		lua_error( state );						
	}
}
