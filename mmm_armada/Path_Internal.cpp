#include "Path_Internal.h"
#include "WormholeType.h"
#include "PathType.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        using namespace types;

        // Address of the static AiPath::find function.
        const std::size_t Address_Find			= 0x0044fb10;

        const std::size_t Address_SetPointCount	= 0x0044f990;

        const std::size_t Address_SetPoints		= 0x0044f990;
        // Address of the AiPath set label function.
        const std::size_t Address_SetLabel		= 0x0044f920;
        // Address of the AiPath class' default constructor
        const std::size_t Address_PathDefaultConstructor = 0x0044ef40;

        // Static AiPath find function.
        auto path_find = memory_function<AiPath* (*)(const char*)>(Address_Find);
        // The AiPath set label function.
        auto path_set_label = memory_function<void (AiPath::*)(const char*)>(Address_SetLabel);
        // Default constructor for the AiPath class.
        auto path_default_constructor = memory_function<void (AiPath::*)()>(Address_PathDefaultConstructor);

        int path_metatable{ LUA_NOREF };

        int path_append(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Path>>(L, 1);
            self->appendPoint(get_userdata<Vector3>(L, 2));
            return 0;
        }

        int path_prepend(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Path>>(L, 1);
            self->prependPoint(get_userdata<Vector3>(L, 2));
            return 0;
        }

        int path_set(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Path>>(L, 1);
            self->setPoint(lua_tonumber(L, 3), get_userdata<Vector3>(L, 4));
            return 0;
        }

        int path_remove(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Path>>(L, 1);
            self->remove(lua_tonumber(L, 3));
            return 0;
        }

        int path_constructor(lua_State* L)
        {
            if (lua_gettop(L) == 1)
            {
                return path_new(L, std::make_shared<Path>());
            }
            return path_new(L, std::make_shared<Path>(lua_tostring(L, 2)));
        }

        int path_gc(lua_State* L)
        {
            cleanup_userdata<std::shared_ptr<Path>>(L);
            return 0;
        }

        int path_index(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Path>>(L, 1);
            const std::string key = lua_tostring(L, 2);

            if (key == "append")
            {
                lua_pushcfunction(L, path_append);
                return 1;
            }
            else if (key == "count")
            {
                lua_pushnumber(L, self->count());
                return 1;
            }
            else if (key == "name")
            {
                lua_pushstring(L, self->getName().c_str());
                return 1;
            }
            else if (key == "points")
            {
                return self->getPoints(L);
            }
            else if (key == "prepend")
            {
                lua_pushcfunction(L, path_prepend);
                return 1;
            }
            else if (key == "remove")
            {
                lua_pushcfunction(L, path_remove);
                return 1;
            }
            else if (key == "set")
            {
                lua_pushcfunction(L, path_set);
                return 1;
            }
            return 0;
        }
    }

    types::AiPath* Path::get(const std::string& name)
    {
        return path_find(name.c_str());
    }

    Path::Path()
        : path_(armada_new<types::AiPath>())
    {
        (path_->*path_default_constructor)();
    }

    Path::Path(const std::string& name)
        : path_(nullptr)
    {
        path_ = get(name);
        if(nullptr == path_)
        {
            auto path = mmm::armada_new<types::AiPath>();

            (path->*path_default_constructor)();

            (path->*memory_function< void (types::AiPath::*)(int) >(Address_SetPoints))
                (0);

            (path->*path_set_label)(name.c_str());

            path_ = path;
        }
    }

    Path::Path(types::AiPath* path)
        : path_(path)
    {

    }

    int Path::count() const
    {
        return path_->pointCount;
    }

    std::string Path::getName() const
    {
        if(path_->m_pLabel)
        {
            return path_->m_pLabel;
        }
        return ""; 
    }

    Vector3 Path::getPoint(int index) const
    {
        if(index > count())
        {
            return Vector3();
        }
        return path_->points[ index - 1 ];
    }

    bool Path::setPoint(int index, const Vector3& point)
    {
        if(index <= 0 || index > count())
        {
            return false;
        }
        path_->points[ index - 1 ] = point;
        return true;
    }

    void Path::appendPoint(const Vector3& point)
    {
        setSize(count() + 1);
        path_->points[ path_->pointCount - 1 ] = point;
    }

    void Path::prependPoint(const Vector3& point)
    {
        setSize(count() + 1);
        for(int i = count() - 1; i >= 1; --i)
        {
            path_->points[ i ] = path_->points[ i - 1 ];
        }
        path_->points[ 0 ] = point;
    }

    void Path::setSize(int size)
    {
        (path_->*memory_function< void (types::AiPath::*)(int) >(Address_SetPointCount))
            (size);
    }

    int Path::getPoints(lua_State* L) const
    {
        lua_newtable(L);
        const int Count = count();
        for(int i = 1; i <= Count; ++i)
        {
            vector_new(L, path_->points[i - 1]);
            lua_rawseti(L, -2, i);
        }
        return 1;
    }

    void Path::remove(int index)
    {
        if(index <= 0 || index > count())
        {
            return;
        }

        std::vector<Vector3> existingPoints(count());
        memcpy(&existingPoints[0],
                path_->points,
                path_->pointCount);

        (path_->*memory_function< void (types::AiPath::*)(int) >(Address_SetPoints))
            (path_->pointCount - 1);

        if(path_->pointCount)
        {
            existingPoints.erase(existingPoints.begin() + index - 1);
            memcpy(path_->points,
                    &existingPoints[0],
                    path_->pointCount);
        }
    }

    types::AiPath* Path::getPath() const
    {
        return path_;
    }

    bool is_path(lua_State* L, int index)
    {
        return equal_metatable(L, index, path_metatable);
    }

    int path_new(lua_State* L, const std::shared_ptr<Path>& path)
    {
        create_userdata(L, path);
        assign_metatable(L, path_metatable);
        return 1;
    }

    void path_register(lua_State* L)
    {
        lua_newtable(L);
        create_metatable(L,
            {
                { "__call", path_constructor }
            });
        lua_setglobal(L, "Path");

        path_metatable = store_metatable(L,
            {
                { "__index", path_index },
                { "__gc", path_gc }
            });
    }
}