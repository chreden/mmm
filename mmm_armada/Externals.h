#pragma once

#include <list>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <functional>
#include <set>
#include <deque>
#include <sstream>
#include <iostream>
#include <cmath>
#include <fstream>
#include <regex>
#include <queue>
#include <unordered_map>

#include <process.h>
#include <windows.h>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>

#include "../mmm_common/mmm_common.h"

extern "C"
{
    #include <lua/src/lua.h>
	#include <lua/src/lualib.h>
	#include <lua/src/lauxlib.h>
}

#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>
#include <luabind/object.hpp>
#include <luabind/detail/class_cache.hpp>
#include <luabind/adopt_policy.hpp>
