#include "OrdnanceDamage.h"
#include "OrdnanceType.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        int ordnancedamage_metatable{ LUA_NOREF };

        int ordnancedamage_index(lua_State* L)
        {
            const auto& self = get_userdata<std::shared_ptr<OrdnanceDamage>>(L, 1);
            const std::string key = lua_tostring(L, 2);
            if (key == "flags")
            {
                lua_pushnumber(L, self->getFlags());
                return 1;
            }
            else if (key == "total")
            {
                lua_pushnumber(L, self->getTotal());
                return 1;
            }
            return 0;
        }

        int ordnancedamage_newindex(lua_State* L)
        {
            auto& self = get_userdata<std::shared_ptr<OrdnanceDamage>>(L, 1);
            const std::string key = lua_tostring(L, 2);
            if (key == "flags")
            {
                self->setFlags(static_cast<Special>(lua_tonumber(L, 3)));
                return 0;
            }
            else if (key == "total")
            {
                self->setTotal(lua_tonumber(L, 3));
                return 0;
            }
            return 0;
        }
    }

    OrdnanceDamagePtr OrdnanceDamage::create(types::Ordnance* ordnance)
    {
        return OrdnanceDamagePtr(new OrdnanceDamage(ordnance));
    }

    OrdnanceDamage::OrdnanceDamage(types::Ordnance* ordnance)
        : ordnance_(ordnance)
    {
    }

    float OrdnanceDamage::getTotal() const
    {
        return ordnance_->stDamage.total;
    }

    Special OrdnanceDamage::getFlags() const
    {
        return ordnance_->stDamage.flags;
    }

    void OrdnanceDamage::setTotal(float value)
    {
        ordnance_->stDamage.total = value;
    }

    void OrdnanceDamage::setFlags(Special value)
    {
        ordnance_->stDamage.flags = value;
    }

    int ordnancedamage_new(lua_State* L, const std::shared_ptr<OrdnanceDamage>& damage)
    {
        create_userdata(L, damage);
        assign_metatable(L, ordnancedamage_metatable);
        return 1;
    }

    void ordnancedamage_register(lua_State* L)
    {
        lua_newtable(L);
        create_enum(L, "DamageFlags",
            {
                { "Standard", Standard },
                { "StandardIgnoreShield", StandardIgnoreShield },
                { "IgnoreShield", IgnoreShield },
                { "DisableEngines", DisableEngines },
                { "DisableLifesupport", DisableLifesupport },
                { "DisableWeapons", DisableWeapons },
                { "DisableShields", DisableShields },
                { "DisableSensors", DisableSensors },
                { "DamageShieldsOnly", DamageShieldsOnly }
            });
        lua_setglobal(L, "OrdnanceDamage");

        ordnancedamage_metatable = store_metatable(L,
            {
                { "__index", ordnancedamage_index },
                { "__newindex", ordnancedamage_newindex }
            });
    }
}
