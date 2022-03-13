#include "StringAdapter.h"

namespace mmm
{
	StringAdapter::operator std::string() const
	{
		return ptr_;
	}

	StringAdapter& 
	StringAdapter::operator=( const std::string& value )
	{
		(this->*(memory_function< StringAdapter& (StringAdapter::*)( const char*, unsigned int)>( Address_Assign )))( value.c_str(), value.size() );
		return *this;
	}
}
