#include "Race_Internal.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        const std::size_t Address_NumberOfRaces = 0x00737cb8;
        const std::size_t Address_Races = 0x00737cbc;
        const std::size_t Function_FindRaceByID = 0x0048b0c0;
        const std::size_t Function_FindRaceByName = 0x0048b100;

        int race_find(lua_State* L)
        {
            if (lua_type(L, 2) == LUA_TSTRING)
            {
                return race_new(L, Race::find(lua_tostring(L, 2)));
            }
            return race_new(L, Race::find(lua_tonumber(L, 2)));
        }

        int race_get_all(lua_State* L)
        {
            return Race::getAll(L);
        }

        int race_class_index(lua_State* L)
        {
            std::string key = lua_tostring(L, 2);
            if (key == "find")
            {
                lua_pushcfunction(L, race_find);
                return 1;
            }
            else if (key == "getAll")
            {
                lua_pushcfunction(L, race_get_all);
                return 1;
            }
            return 0;
        }

        int race_index(lua_State* L)
        {
            auto race = get_userdata<std::shared_ptr<Race>>(L, 1);
            std::string key = lua_tostring(L, 2);

            if (key == "boardingStrength")
            {
                lua_pushnumber(L, race->getBoardingStrength());
                return 1;
            }
            else if (key == "displayName")
            {
                lua_pushstring(L, race->getDisplayName().c_str());
                return 1;
            }
            else if (key == "name")
            {
                lua_pushstring(L, race->getName().c_str());
                return 1;
            }
            else if (key == "repairStrength")
            {
                lua_pushnumber(L, race->getRepairStrength());
                return 1;
            }
            else if (key == "number")
            {
                lua_pushnumber(L, race->getNumber());
                return 1;
            }

            return 0;
        }
    }

    Race::Race(types::Race* race)
        : race_(race)
    {
    }

    std::shared_ptr<Race> Race::create(types::Race* race)
    {
        return std::make_shared<Race>(race);
    }

    std::string Race::getName() const
    {
        return race_->m_name;
    }

    std::string Race::getDisplayName() const
    {
        return race_->m_displayKey;
    }

    float Race::getBoardingStrength() const
    {
        return race_->boardingStrength;
    }

    float Race::getRepairStrength() const
    {
        return race_->repairStrength;
    }

    std::string Race::getSinglePlayerMusic() const
    {
        return race_->m_singlePlayerMusic;
    }

    bool Race::isValid() const
    {
        return race_ != 0;
    }

    int Race::getNumber() const
    {
        return race_->m_raceNumber;
    }

    int Race::getAll(lua_State* L)
    {
        lua_newtable(L);
        types::Race** races = *reinterpret_cast<types::Race***>(Address_Races);
        const int NumberOfRaces = *reinterpret_cast<int*>(Address_NumberOfRaces);
        for (int i = 0; i < NumberOfRaces; ++i)
        {
            race_new(L, std::make_shared<Race>(races[i]));
            lua_rawseti(L, -2, i + 1);
        }
        return 1;
    }

    std::shared_ptr<Race> Race::find(int id)
    {
        types::Race* race = (*memory_function<types::Race* (*)(int)>(Function_FindRaceByID))(id);
        if (race)
        {
            return std::make_shared<Race>(race);
        }
        return {};
    }

    std::shared_ptr<Race> Race::find(const std::string& name)
    {
        types::Race* race = (*memory_function<types::Race* (*)(const char*)>(Function_FindRaceByName))(name.c_str());
        if (race)
        {
            return std::make_shared<Race>(race);
        }
        return {};
    }

    void Race::setSinglePlayerMusic(const std::string& music)
    {
        strcpy_s(race_->m_singlePlayerMusic, music.c_str());
    }

    void Race::setDisplayName(const std::string& name)
    {
        strcpy_s(race_->m_displayKey, name.c_str());
    }

    types::Race* Race::getRace() const
    {
        return race_;
    }

    int race_new(lua_State* L, const std::shared_ptr<Race>& race)
    {
        create_userdata(L, race);
        create_metatable(L,
            {
                { "__index", race_index }
            });
        return 1;
    }

    void race_register(lua_State* L)
    {
        lua_newtable(L);
        create_metatable(L,
            {
                { "__index", race_class_index }
            });
        lua_setglobal(L, "Race");
    }
}