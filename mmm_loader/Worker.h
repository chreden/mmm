#ifndef WORKER_H
#define WORKER_H

#include "RuleHelper.h"

namespace mmm
{
	//The worker is used for releasing resources that
	//have been allocated when the dll is unloaded. There 
	//is only one instance of the class. When it dies, we
	//know that we must shut down everything.
	class Worker
	{
	public:
		Worker( );
		~Worker( );

		//Calls initial lua function. If this is a savegame, then
		//it will call resume, else it will call init.
		void Startup( );

		void Resume( );
	public:	
		bool	inputControlsSet_;

		//Controls for cineractives.
		Rule	workerRule_;

		//Lua Functions
		static Worker* instance; //I hate singletons, but this is going 
								 //to be the easiest way to do this.

	};
}

#endif