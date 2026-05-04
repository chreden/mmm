#pragma once

#include <unordered_map>

#include "Hook.h"

namespace mmm
{
    /**
        Repeatedly tick and call all hooked functions.
    */
    class Timer final : public std::enable_shared_from_this<Timer>
    {
    public:
        enum State
        {
            State_Stopped,
            State_Started
        };

        explicit Timer(const std::string& id, float interval, State state);
        std::string getId() const;
        float getInterval() const;
        bool getRepeat() const;
        float getStartTime() const;
        bool getStarted() const;
        void setInterval(float value);
        void setRepeat(bool value);
        bool hook(const std::string& id, int table, int function, int arguments);
        bool unhook(const std::string& id);
        bool unhook(const std::shared_ptr<Hook>& hook);
        int getHooks(lua_State* L) const;
        State getState() const;
        void start();
        void stop();
        void tick(lua_State* L);
        static std::shared_ptr<Timer> add(const std::string& id, float interval, State state);
        static std::shared_ptr<Timer> find(const std::string& id);
        static void stopAll();
        static int getAll(lua_State* L);
    private:
        std::unordered_map<std::string, std::shared_ptr<Hook>> hooks_;
        std::string id_;
        float interval_;
        float startTime_;
        bool repeat_;
        State state_;
    };

    void timer_update(lua_State* L);
    int timer_new(lua_State* L, const std::shared_ptr<Timer>& timer);
    void timer_register(lua_State* L);
}
