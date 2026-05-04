#ifndef WORKER_H
#define WORKER_H

#include "RuleHelper.h"

namespace mmm
{
    // The worker is used for releasing resources that
    // have been allocated when the dll is unloaded. There 
    // is only one instance of the class. When it dies, we
    // know that we must shut down everything.
    class Worker
    {
    public:
        Worker();
        ~Worker();

        //Calls initial lua function. If this is a savegame, then
        //it will call resume, else it will call init.
        void Startup();
        void Resume();
    public:
        bool inputControlsSet_;
        Rule workerRule_;
        static Worker* instance;
    };
}

#endif