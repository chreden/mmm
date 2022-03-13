#pragma once

namespace mmm
{
	template<typename T>
	T
	Load::read( )
	{
		T ret = 0;
		memcpy( &ret, &buffer_[ position_ ], sizeof(ret) );
		position_ += sizeof(ret);
		return ret;
	}

	template<>
	inline
	std::string
	Load::read( )
	{
		int length = strlen( reinterpret_cast<const char*>( &buffer_[ position_ ] ) ) + 1;
		const char* ret = reinterpret_cast<const char*>( &buffer_[ position_ ] );
		position_ += length;
		return ret;
	}
}
