#include "Timer.h"
#include "Game_Internal.h"
#include "ScriptErrors.h"
#include "TimerHook.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace 
    {
        std::vector<std::shared_ptr<Timer>> timers;
        int timer_metatable{ LUA_NOREF };

        int timer_find(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Timer>>(L, 1);
            return timer_new(L, self->find(lua_tostring(L, 2)));
        }

        int timer_get_all(lua_State* L)
        {
            return Timer::getAll(L);
        }

        int timer_hook(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Timer>>(L, 1);
            std::string id = lua_tostring(L, 2);
            int arguments = luaL_ref(L, LUA_REGISTRYINDEX);
            int function = luaL_ref(L, LUA_REGISTRYINDEX);
            int table = luaL_ref(L, LUA_REGISTRYINDEX);
            bool result = self->hook(id, table, function, arguments);
            lua_pushboolean(L, result);
            return 1;
        }

        int timer_start(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Timer>>(L, 1);
            self->start();
            return 0;
        }

        int timer_stop(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Timer>>(L, 1);
            self->stop();
            return 0;
        }

        int timer_unhook(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Timer>>(L, 1);
            if (lua_type(L, 2) == LUA_TSTRING)
            {
                lua_pushboolean(L, self->unhook(lua_tostring(L, 2)));
                return 1;
            }
            lua_pushboolean(L, self->unhook(get_userdata<std::shared_ptr<Hook>>(L, 2)));
            return 1;
        }

        int timer_index(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Timer>>(L, 1);
            std::string key = lua_tostring(L, 2);

            if (key == "hook")
            {
                lua_pushcfunction(L, timer_hook);
                return 1;
            }
            else if (key == "hooks")
            {
                return self->getHooks(L);
            }
            else if (key == "id")
            {
                lua_pushstring(L, self->getId().c_str());
                return 1;
            }
            else if (key == "interval")
            {
                lua_pushnumber(L, self->getInterval());
                return 1;
            }
            else if (key == "repeats")
            {
                lua_pushboolean(L, self->getRepeat());
                return 1;
            }
            else if (key == "start")
            {
                lua_pushcfunction(L, timer_start);
                return 1;
            }
            else if (key == "state")
            {
                lua_pushnumber(L, self->getState());
                return 1;
            }
            else if (key == "stop")
            {
                lua_pushcfunction(L, timer_stop);
                return 1;
            }
            else if (key == "unhook")
            {
                lua_pushcfunction(L, timer_unhook);
                return 1;
            }

            return 0;
        }

        int timer_newindex(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Timer>>(L, 1);
            std::string key = lua_tostring(L, 2);

            if (key == "interval")
            {
                self->setInterval(lua_tonumber(L, 3));
                return 0;
            }
            else if (key == "repeats")
            {
                self->setRepeat(lua_toboolean(L, 3));
                return 0;
            }
            return 0;
        }

        int timer_gc(lua_State* L)
        {
            cleanup_userdata<std::shared_ptr<Timer>>(L, 1);
            return 0;
        }

        int timer_stop_all(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Timer>>(L, 1);
            self->stopAll();
            return 0;
        }

        int timer_class_index(lua_State* L)
        {
            std::string key = lua_tostring(L, 2);
            if (key == "find")
            {
                lua_pushcfunction(L, timer_find);
                return 1;
            }
            else if (key == "getAll")
            {
                lua_pushcfunction(L, timer_get_all);
                return 1;
            }
            else if (key == "stopAll")
            {
                lua_pushcfunction(L, timer_stop_all);
                return 1;
            }

            return 0;
        }

        int timer_constructor(lua_State* L)
        {
            return timer_new(L, Timer::add(lua_tostring(L, 2), lua_tonumber(L, 3), static_cast<Timer::State>(lua_tonumber(L, 4))));
        }
    }

    Timer::Timer( const std::string& id, float interval, State state )
            : id_( id ),
              interval_( interval ),
              state_( state ), 
              startTime_( Game().getTime() ),
              repeat_( false )
    {

    }

    std::string Timer::getId() const
    {
        return id_;
    }

    float Timer::getInterval() const
    {
        return interval_;
    }

    bool Timer::getRepeat() const
    {
        return repeat_;
    }

    float Timer::getStartTime() const
    {
        return startTime_;
    }

    bool Timer::getStarted() const
    {
        return state_ == State_Started;
    }

    Timer::State Timer::getState() const
    {
        return state_;
    }

    void Timer::setInterval(float value)
    {
        interval_ = value;
    }

    void Timer::setRepeat(bool value)
    {
        repeat_ = value;
    }

    void Timer::tick(lua_State* L)
    {
        if (!hooks_.empty()) 
        {
            auto self = shared_from_this();
            auto hooksCopy = hooks_;
            for( auto iter = hooksCopy.begin(); iter != hooksCopy.end(); ++iter )
            {
                std::shared_ptr<Hook> hook = iter->second;
                lua_rawgeti(L, LUA_REGISTRYINDEX, hook->table());
                if (lua_type(L, -1) == LUA_TTABLE)
                {
                    lua_rawgeti(L, LUA_REGISTRYINDEX, hook->function());
                    lua_pushvalue(L, -2);
                    hook_new(L, hook);
                    lua_rawgeti(L, LUA_REGISTRYINDEX, hook->argument());
                    if (LUA_OK != lua_pcall(L, 3, 0, 0))
                    {
                        scriptError(std::string("Error in Timer.tick : ") + lua_tostring(L, -1));
                    }
                }
                else
                {
                    lua_rawgeti(L, LUA_REGISTRYINDEX, hook->function());
                    lua_rawgeti(L, LUA_REGISTRYINDEX, hook->argument());
                    int args = 0;
                    if (LUA_TNIL == lua_type(L, -1))
                    {
                        lua_pop(L, 1);
                    }
                    else
                    {
                        ++args;
                    }
                    if (LUA_OK != lua_pcall(L, args, 0, 0))
                    {
                        scriptError(std::string("Error in Timer.tick : ") + lua_tostring(L, -1));
                    }
                }
            }
        }

        if (getRepeat())
        {
            start();
        }
        else
        {
            stop();
        }
    }

    void Timer::start()
    {
        state_ = State_Started;
        startTime_ = Game().getTime();

        //Check to see if the timer is in the active list - if it isn't we have to add it so that
        //it gets updated. This means that people can hang on to timers if they want.
        std::shared_ptr<Timer> timer = shared_from_this();
        if(std::find(timers.begin(), timers.end(), timer) == timers.end())
        {
            timers.push_back(timer);
        }
    }

    void Timer::stop()
    {
        //Stop the timer
        state_ = State_Stopped;
        //Remove it from the active list, if it is there
        std::remove(timers.begin(), timers.end(), shared_from_this());
    }

    bool Timer::hook(const std::string& id, int table, int function, int arguments)
    {
        if (hooks_.find(id) != hooks_.end())
        {
            return false;
        }
        hooks_[id] = std::make_shared<TimerHook>(id, table, function, arguments);
        return true;
    }

    bool Timer::unhook(const std::string& id)
    {
        auto iter = hooks_.find(id);
        if (iter != hooks_.end())
        {
            hooks_.erase(iter);
            return true;
        }
        return false;
    }

    bool Timer::unhook(const std::shared_ptr<Hook>& hook)
    {
        if (!hook)
        {
            return false;
        }

        auto iter = hooks_.find(hook->id());
        if (iter == hooks_.end())
        {
            return false;
        }

        hooks_.erase(iter);
        return true;
    }

    int Timer::getHooks(lua_State* L) const
    {
        lua_newtable(L);
        for( auto iter = hooks_.begin(); iter != hooks_.end(); ++iter )
        {

            lua_setfield(L, -2, iter->first.c_str());
        }
        return 1;
    }

    void timer_update(lua_State* L)
    {
        std::vector<std::shared_ptr<Timer>> timersCopy(timers);
        float currentTime = Game().getTime();
        for (std::size_t i = 0; i < timersCopy.size(); ++i)
        {
            if (timersCopy[i] && timersCopy[i]->getStarted())
            {
                if (currentTime - timersCopy[i]->getStartTime() >= timersCopy[i]->getInterval())
                {
                    timersCopy[i]->tick(L);
                }
            }
        }
    }

    std::shared_ptr<Timer> Timer::add(const std::string& id, float interval, State started)
    {
        std::shared_ptr<Timer> newTimer = std::make_shared<Timer>(id, interval, started);
        timers.push_back( newTimer );
        return newTimer;
    }

    int Timer::getAll(lua_State* L)
    {
        lua_newtable(L);
        const std::size_t Count = timers.size();
        for( std::size_t i = 0; i < Count; ++i ) 
        {
            timer_new(L, timers[i]);
            lua_rawseti(L, -2, i + 1);
        }
        return 1;
    }

    std::shared_ptr<Timer> Timer::find(const std::string& id)
    {
        const std::size_t Count = timers.size();
        for( std::size_t i = 0; i < Count; ++i )
        {
            if( timers[i]->getId() == id )
            {
                return timers[i];
            }
        }
        return {};
    }

    void Timer::stopAll() 
    {
        //Using the stop function would be slower, so stopping the timers manually here
        //and then removing everything.
        std::for_each(timers.begin(), timers.end(),
            [] (std::shared_ptr<Timer> timer) 
        {
            timer->state_ = Timer::State_Stopped;
        });
        timers.clear();
    }

    int timer_new(lua_State* L, const std::shared_ptr<Timer>& timer)
    {
        create_userdata(L, timer);
        assign_metatable(L, timer_metatable);
        return 1;
    }

    void timer_register(lua_State* L)
    {
        lua_newtable(L);
        create_enum(L, "State",
            {
                { "Started", Timer::State_Started },
                { "Stopped", Timer::State_Stopped }
            });
        create_metatable(L,
            {
                { "__index", timer_class_index },
                { "__call", timer_constructor }
            });
        lua_setglobal(L, "Timer");

        timer_metatable = store_metatable(L,
            {
                { "__index", timer_index },
                { "__newindex", timer_newindex },
                { "__gc", timer_gc }
            });
    }
}