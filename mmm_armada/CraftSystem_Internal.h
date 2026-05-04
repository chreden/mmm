#pragma once

namespace mmm
{
    namespace types { struct CraftSystem; }

    class CraftSystem
    {
    public:
        explicit CraftSystem(types::CraftSystem* system);

        bool getActive() const;
        bool getPermanentDisable() const;
        float getHitpoints() const;
        float getHealth() const;
        long getMaxHitpoints() const;

        void setActive(bool value);
        void setPermanentDisable(bool value);
        void setHitpoints(float value);
        void setHealth(float value);
        void setMaxHitpoints(long value);
    private:
        types::CraftSystem* system_;
    };

    int craftsystem_new(lua_State* L, const std::shared_ptr<CraftSystem>& system);
}
