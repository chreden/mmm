#include "CraftSystem_Internal.h"
#include "Type_CraftSystem.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        int craftsystem_index(lua_State* L)
        {
            const auto self = get_userdata<std::shared_ptr<CraftSystem>>(L, 1);
            const std::string key = lua_tostring(L, 2);
            if (key == "active")
            {
                lua_pushboolean(L, self->getActive());
                return 1;
            }
            else if (key == "health")
            {
                lua_pushnumber(L, self->getHealth());
                return 1;
            }
            else if (key == "hitpoints")
            {
                lua_pushnumber(L, self->getHitpoints());
                return 1;
            }
            else if (key == "maxHitpoints")
            {
                lua_pushnumber(L, self->getMaxHitpoints());
                return 1;
            }
            else if (key == "permanentDisable")
            {
                lua_pushboolean(L, self->getPermanentDisable());
                return 1;
            }
            return 0;
        }

        int craftsystem_newindex(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<CraftSystem>>(L, 1);
            const std::string key = lua_tostring(L, 2);
            if (key == "active")
            {
                self->setActive(lua_toboolean(L, 3));
                return 0;
            }
            else if (key == "health")
            {
                self->setHealth(lua_tonumber(L, 3));
                return 0;
            }
            else if (key == "hitpoints")
            {
                self->setHitpoints(lua_tonumber(L, 3));
                return 0;
            }
            else if (key == "maxHitpoints")
            {
                self->setMaxHitpoints(lua_tonumber(L, 3));
                return 0;
            }
            else if (key == "permanentDisable")
            {
                self->setPermanentDisable(lua_toboolean(L, 3));
                return 0;
            }
            return 0;
        }
    }

    CraftSystem::CraftSystem(types::CraftSystem* system)
        : system_(system)
    {
    }

    bool CraftSystem::getActive( ) const
    {
        return system_->active;
    }

    bool CraftSystem::getPermanentDisable( ) const
    {
        return system_->permanentDisable;
    }

    float CraftSystem::getHitpoints( ) const
    {
        return system_->fHitPoints;
    }

    float CraftSystem::getHealth( ) const
    {
        return system_->fHitPoints / static_cast<float>(system_->maxHitPoints);
    }

    long CraftSystem::getMaxHitpoints() const
    {
        return system_->maxHitPoints;
    }

    void CraftSystem::setActive( bool value )
    {
        system_->active = value;
    }

    void CraftSystem::setPermanentDisable( bool value )
    {
        system_->permanentDisable = value;
    }

    void CraftSystem::setHitpoints( float value )
    {
        system_->fHitPoints = value;
    }

    void CraftSystem::setHealth( float value )
    {
        system_->fHitPoints = static_cast<float>( system_->maxHitPoints ) * value;
    }

    void CraftSystem::setMaxHitpoints( long value )
    {
        system_->maxHitPoints = value;
    }

    int craftsystem_new(lua_State* L, const std::shared_ptr<CraftSystem>& system)
    {
        create_userdata<std::shared_ptr<CraftSystem>>(L, system);
        create_metatable(L,
            {
                { "__index", craftsystem_index },
                { "__newindex", craftsystem_newindex }
            });
        return 1;
    }
}
