#pragma once

#include "GameObject_Internal.h"

namespace mmm
{
    namespace types 
    {
        struct Craft;
    }

    class Craft : public GameObject
    {
    public:
        static std::shared_ptr<Craft> create(types::Entity* entity);
        std::string getName() const;
        float getShields() const;
        float getShieldsValue() const;
        float getMaxShields() const;
        eAlertStatus getAlertStatus() const;
        eSpecialWeaponAutonomy getSpecialWeaponAutonomy() const;
        eMovementAutonomy getMovementAutonomy() const;
        float getImpulseSpeed() const;
        float getCrew() const;
        float getMaxCrew() const;
        int getSystems(lua_State* L) const;
        std::shared_ptr<GameObjectClass> getClass() const override;
        void setName(const std::string& name);
        void setShields(float percentage);
        void setShieldsValue(float value);
        void setMaxShields(float value);
        void setCrew(float value);
        void setMaxCrew(float value);
        void setAlertStatus(eAlertStatus status);
        void setSpecialWeaponAutonomy(eSpecialWeaponAutonomy autonomy);
        void setMovementAutonomy(eMovementAutonomy autonomy);
        void setSystemStatus(eCraftSystem system, bool state);
        void setImpulseSpeed(float value);
        void explode();
        void disableSystem(eCraftSystem system, float time);
        types::Craft* getCraft() const;

        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit Craft(types::Craft* craft);
    };

    void craft_register(lua_State* state);
}
