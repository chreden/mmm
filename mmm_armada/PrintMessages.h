#pragma once

#include "DebuggerConnection.h"

namespace mmm
{
	class PrintMessages
	{
	public:
		static void add( const std::string& message, DebuggerConnection::Type type = DebuggerConnection::Type_Message );
	private:
		static std::size_t getIndex( );
		static std::vector< std::pair<int,float> > messages_;
		static int					currentIndex_;
	};
}
