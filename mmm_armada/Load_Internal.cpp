#include "Load_Internal.h"
#include "Type_Craft.h"

#include "GameObject_Internal.h"
#include "Craft_Internal.h"
#include "Entities_Internal.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        Load load;

        int load_load(lua_State* L)
        {
            load.doLoad();
            return 0;
        }

        int load_readstring(lua_State* L)
        {
            lua_pushstring(L, load.read<std::string>().c_str());
            return 1;
        }

        int load_readnumber(lua_State* L)
        {
            lua_pushnumber(L, load.read<float>());
            return 1;
        }

        int load_readboolean(lua_State* L)
        {
            lua_pushnumber(L, load.read<bool>());
            return 1;
        }

        int load_index(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);
            if (key == "load")
            {
                lua_pushcfunction(L, load_load);
                return 1;
            }
            else if (key == "readString")
            {
                lua_pushcfunction(L, load_readstring);
                return 1;
            }
            else if (key == "readNumber")
            {
                lua_pushcfunction(L, load_readnumber);
                return 1;
            }
            else if (key == "readBoolean")
            {
                lua_pushcfunction(L, load_readboolean);
                return 1;
            }
            else if (key == "position")
            {
                lua_pushnumber(L, load.getLength());
                return 1;
            }
            return 0;
        }

        int load_newindex(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);
            if (key == "position")
            {
                load.setRead(lua_tonumber(L, 3));
                return 0;
            }
            return 0;
        }
    }

    Load::Load()
        : position_(0)
    {
        memset(buffer_, 0, sizeof(buffer_));
    }

    void Load::doLoad()
    {
        memset(buffer_, 0, sizeof(buffer_));

        std::vector<std::shared_ptr<Entity>> objects;

        Entities::find(objects, isLoadOdf, 0);

        loadHolders(objects);
        loadMappers(objects);
    }

    void Load::loadHolders(const std::vector<std::shared_ptr<Entity>>& objects)
    {
        for(std::size_t i = 0; i < objects.size(); ++i)
        {
            CraftPtr craft = std::static_pointer_cast<Craft>(objects[i]);
            if(craft->getOdf() == HolderName)
            {
                const std::string name = craft->getName();
                if(name.size() > 2)
                {
                    char packetIndex = name[ 0 ] - 1;
                    char numberOfBytes = name[ 1 ];

                    int offset = packetIndex * BytesPerPacket;

                    for(int b = 0; b < numberOfBytes; ++b)
                    {
                        buffer_[ offset + b ] = name[ 2 + b ];
                    }
                }
            }
        }
    }

    void Load::loadMappers(const std::vector<std::shared_ptr<Entity>>& objects)
    {
        for(std::size_t i = 0; i < objects.size(); ++i)
        {
            CraftPtr craft = std::static_pointer_cast<Craft>(objects[i]);
            if(craft->getOdf() == MapperName)
            {
                const std::string name = craft->getName();
                if(name.size() > 2)
                {
                    char packetIndex = name[ 0 ] - 1;
                    char numberOfBytes = name[ 1 ];

                    int offset = packetIndex * BytesPerPacket;

                    for(int b = 0; b < numberOfBytes; ++b)
                    {
                        if(name[ 2 + b ] == IsZeroChar)
                        {
                            buffer_[ offset + b ] = 0;
                        }
                    }
                }
            }
        }
    }

    int Load::getLength()
    {
        return position_;
    }

    void Load::setRead(int position)
    {
        position_ = position;
    }

    bool Load::isLoadOdf(const std::shared_ptr<Entity>& ent, void* arguments)
    {
        if(types::isGameObject(ent->getEntity()))
        {
            const std::string odf = std::static_pointer_cast<GameObject>(ent)->getOdf();
            return odf == HolderName || odf == MapperName;
        }
        return false;
    }

    void load_register(lua_State* L)
    {
        lua_newtable(L);
        create_metatable(L,
            {
                { "__index", load_index },
                { "__newindex", load_newindex }
            });
        lua_setglobal(L, "Load");
    }
}

