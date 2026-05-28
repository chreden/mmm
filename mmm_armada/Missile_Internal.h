#pragma once

#include "Ordnance.h"

//An aside - unitorped is derived from missile

namespace mmm
{
    namespace types { struct Missile; }

    class Missile : public Ordnance
    {
    public:
        static std::shared_ptr<Missile> create(types::Entity* entity);
        virtual ~Missile(){};
        Vector3 getOmega() const;
        float getSeekTimer() const;
        float getTurnLim2() const;
        void setOmega(const Vector3& value);
        void setTurnLim2(float value);
        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit  Missile(types::Missile* missile);
        types::Missile* getMissile() const;
    };
}
