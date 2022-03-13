#include "mmm_armada.h"

namespace mmm
{
	ScriptInterface* currentScriptInterface_;

	ScriptInterface* getScriptInterface( )
	{
		return currentScriptInterface_;
	}

	void setScriptInterface( ScriptInterface* sInterface )
	{
		currentScriptInterface_ = sInterface;
	}
}