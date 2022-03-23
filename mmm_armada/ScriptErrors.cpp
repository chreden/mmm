#include "ScriptErrors.h"
#include "UI_Internal.h"
#include "PrintMessages.h"

namespace mmm
{
	void scriptError( const std::string& error, bool stop )
	{
		print::add( error, DebuggerConnection::Type_Error );
		common::Storage::instance().error = stop;
	}

	void 
	reportError( const std::string& functionName, const std::string& error )
	{
		scriptError( "Error in " + functionName + " : " + error );
	}
}
