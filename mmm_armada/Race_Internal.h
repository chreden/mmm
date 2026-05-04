#pragma once

#include "Type_Race.h"

namespace mmm
{
    class Race
    {
    public:
        explicit Race(types::Race* race);

        static int getAll(lua_State* L);
        static std::shared_ptr<Race> find(int id);
        static std::shared_ptr<Race> find(const std::string& name);
        static std::shared_ptr<Race> create(types::Race* race);

        std::string getName() const;
        std::string getDisplayName() const;
        float getBoardingStrength() const;
        float getRepairStrength() const;
        std::string getSinglePlayerMusic() const;
        int getNumber() const;
        bool isValid() const;
        void setSinglePlayerMusic(const std::string& music);
        void setDisplayName(const std::string& name);
        types::Race* getRace() const;
    private:
        types::Race* race_;
    };

    int race_new(lua_State* L, const std::shared_ptr<Race>& race);
    void race_register(lua_State* L);
}
