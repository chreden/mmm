#include "Type_DebriefingData.h"

namespace mmm
{
    namespace types
    {
        DebriefingData* get_debriefing_data()
        {
            return *reinterpret_cast<DebriefingData**>(0x007a86b4);
        }
    }
}
