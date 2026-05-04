#include "Container.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        int container_metatable{ LUA_NOREF };

        int container_index(lua_State* L)
        {
            const auto& self = get_userdata<Container>(L, 1);
            const std::string key = lua_tostring(L, 2);

            if (key == "crew")
            {
                lua_pushnumber(L, self.getResource<RESOURCE_CREW>());
                return 1;
            }
            else if (key == "officers")
            {
                lua_pushnumber(L, self.getResource<RESOURCE_OFFICERS>());
                return 1;
            }
            else if (key == "dilithium")
            {
                lua_pushnumber(L, self.getResource<RESOURCE_DILITHIUM>());
                return 1;
            }
            else if (key == "latinum" || key == "tritanium")
            {
                lua_pushnumber(L, self.getResource<RESOURCE_LATINUM>());
                return 1;
            }
            else if (key == "metal" || key == "collectiveConnections")
            {
                lua_pushnumber(L, self.getResource<RESOURCE_METAL>());
                return 1;
            }
            else if (key == "biomatter" || key == "supply")
            {
                lua_pushnumber(L, self.getResource<RESOURCE_BIOMATTER>());
                return 1;
            }

            return 0;
        }

        int container_newindex(lua_State* L)
        {
            auto& self = get_userdata<Container>(L, 1);
            const std::string key = lua_tostring(L, 2);

            if (key == "crew")
            {
                self.setResource<RESOURCE_CREW>(lua_tonumber(L, 3));
                return 0;
            }
            else if (key == "officers")
            {
                self.setResource<RESOURCE_OFFICERS>(lua_tonumber(L, 3));
                return 0;
            }
            else if (key == "dilithium")
            {
                self.setResource<RESOURCE_DILITHIUM>(lua_tonumber(L, 3));
                return 0;
            }
            else if (key == "latinum" || key == "tritanium")
            {
                self.setResource<RESOURCE_LATINUM>(lua_tonumber(L, 3));
                return 0;
            }
            else if (key == "metal" || key == "collectiveConnections")
            {
                self.setResource<RESOURCE_METAL>(lua_tonumber(L, 3));
                return 0;
            }
            else if (key == "biomatter" || key == "supply")
            {
                self.setResource<RESOURCE_BIOMATTER>(lua_tonumber(L, 3));
                return 0;
            }
            return 0;
        }

        int container_gc(lua_State* L)
        {
            cleanup_userdata<Container>(L);
            return 0;
        }
    }

    Container::Callback::~Callback()
    {

    }

    Container::Container(std::shared_ptr<Callback> callback)
        : callback_(callback)
    {
    }

    int container_new(lua_State* L, const Container& container)
    {
        create_userdata(L, container);
        assign_metatable(L, container_metatable);
        return 1;
    }

    void container_register(lua_State* L)
    {
        lua_newtable(L);
        create_enum(L, "Type",
            {
                { "Crew", RESOURCE_CREW },
                { "Officers", RESOURCE_OFFICERS },
                { "Dilithium", RESOURCE_DILITHIUM },
                { "Latinum", RESOURCE_LATINUM },
                { "Metal", RESOURCE_METAL },
                { "Biomatter", RESOURCE_BIOMATTER },
                { "Tritanium", RESOURCE_LATINUM },
                { "Supply", RESOURCE_BIOMATTER },
                { "CollectiveConnections", RESOURCE_METAL }
            });
        lua_setglobal(L, "Resources");

        container_metatable = store_metatable(L,
            {
                { "__index", container_index },
                { "__newindex", container_newindex },
                { "__gc", container_gc }
            });
    }
}