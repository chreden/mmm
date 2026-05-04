#include "Wormhole.h"
#include "WormholeType.h"
#include "Team_Internal.h"
#include "Shipyard_Internal.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        const std::size_t Offset_State = 0x00000190;
        const std::size_t Offset_Name = 0x000001BE;
        const std::size_t Address_SetPartner = 0x004a6a60;
        const std::size_t Address_SetShipyard = 0x004a77f0;
        const std::size_t Address_SetName = 0x004a7860;
    }

    std::shared_ptr<Wormhole> Wormhole::create( types::Entity* entity )
    {
        return std::shared_ptr<Wormhole>(new Wormhole(static_cast<types::Wormhole*>(entity )));
    }

    Wormhole::Wormhole(types::Wormhole* wormhole)
        : AreaEffectObject(wormhole)
    {
    }

    std::shared_ptr<Wormhole> Wormhole::getPartner() const
    {
        return std::shared_ptr<Wormhole>(new Wormhole(getWormhole()->m_pWormholePartner));
    }

    GateStatus Wormhole::getStatus() const
    {
        return getWormhole()->m_wormholeState;
    }

    std::string Wormhole::getName() const
    {
        return getWormhole()->m_pDisplayName;
    }

    std::shared_ptr<Team> Wormhole::getOwner() const
    {
        return std::make_shared<Team>(getWormhole()->m_ownerTeam);
    }

    bool Wormhole::setPartner(const std::shared_ptr<Entity>& wormhole)
    {
        if (wormhole->isType(Entity_Wormhole))
        {
            typedef void (types::Wormhole::*MemFunction) (types::Wormhole*);
            MemFunction function = memory_function<MemFunction>(Address_SetPartner);
            (getWormhole()->*function)(static_cast<types::Wormhole*>(wormhole->getEntity()));
            return true;
        }
        return false;
    }

    bool Wormhole::getExpireOnClose() const
    {
        return getWormhole()->m_expireOnClose;
    }

    bool Wormhole::getDeleteOnTransport() const
    {
        return getWormhole()->m_deleteOnTransport;
    }

    void Wormhole::setExpireOnClose(bool value)
    {
        getScriptInterface()->SetWormholeExpireOnClose(getWormhole()->m_entity_id, value);
    }

    void Wormhole::setDeleteOnTransport(bool value)
    {
        getScriptInterface()->SetWormholeDeleteOnTransport(getWormhole()->m_entity_id, value);
    }

    void Wormhole::setName(const std::string& name)
    {
        typedef void (types::Wormhole::*MemFunction) (const char*);
        MemFunction function = memory_function<MemFunction>(Address_SetName);
        (getWormhole()->*function)(name.c_str());
    }

    void Wormhole::setOwner(const std::shared_ptr<Team>& team)
    {
        getWormhole()->m_ownerTeam = team->getNumber();
    }

    void Wormhole::setShipyard(const std::shared_ptr<Shipyard>& shipyard)
    {
        (getWormhole()->*memory_function<void (types::Wormhole::*)(types::Shipyard*)>(Address_SetShipyard))(shipyard->getShipyard());
    }

    types::Wormhole* Wormhole::getWormhole() const
    {
        return static_cast<types::Wormhole*>(getEntity());
    }

    int Wormhole::index(lua_State* L, const std::string& key) const
    {
        if (key == "link")
        {
            return entity_new(L, getPartner());
        }
        else if (key == "name")
        {
            lua_pushstring(L, getName().c_str());
            return 1;
        }
        else if (key == "owner")
        {
            return team_new(L, getOwner());
        }
        else if (key == "expireOnClose")
        {
            lua_pushboolean(L, getExpireOnClose());
            return 1;
        }
        else if (key == "deleteOnTransport")
        {
            lua_pushboolean(L, getDeleteOnTransport());
            return 1;
        }
        else if (key == "status")
        {
            lua_pushnumber(L, getStatus());
            return 1;
        }
        return AreaEffectObject::index(L, key);
    }

    int Wormhole::newindex(lua_State* L, const std::string& key)
    {
        if (key == "link")
        {
            setPartner(get_entity<Entity>(L, 3));
            return 0;
        }
        else if (key == "name")
        {
            setName(lua_tostring(L, 3));
            return 0;
        }
        else if (key == "owner")
        {
            setOwner(get_userdata<std::shared_ptr<Team>>(L, 3));
            return 0;
        }
        else if (key == "expireOnClose")
        {
            setExpireOnClose(lua_toboolean(L, 3));
            return 1;
        }
        else if (key == "deleteOnTransport")
        {
            setDeleteOnTransport(lua_toboolean(L, 3));
            return 1;
        }
        return AreaEffectObject::newindex(L, key);
    }

    void wormhole_register(lua_State* L)
    {
        lua_newtable(L);
        create_enum(L, "State",
            {
                { "Closed", Gate_Closed },
                { "Closing", Gate_Close },
                { "Open", Gate_Open },
                { "Opening", Gate_Opening }
            });
        lua_setglobal(L, "Wormhole");
    }
}
