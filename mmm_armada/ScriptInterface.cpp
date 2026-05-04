#include "ScriptInterface.h"

namespace mmm
{
    namespace
    {
        ScriptInterface* currentScriptInterface_;
    }

    ScriptInterface* getScriptInterface()
    {
        return currentScriptInterface_;
    }

    void setScriptInterface(ScriptInterface* sInterface)
    {
        currentScriptInterface_ = sInterface;
    }
}