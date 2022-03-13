#include "Mission_Internal.h"
#include "Game_Internal.h"

namespace mmm
{
	void
	Mission::end( bool success, float delay )
	{
		const float FinishingTime = Game().getTime() + delay;
		if( success )
		{
			getScriptInterface()->SucceedMission( FinishingTime, "" );
		}
		else
		{
			getScriptInterface()->FailMission( FinishingTime, "" );
		}
	}
}