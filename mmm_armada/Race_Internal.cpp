#include "Race_Internal.h"

namespace mmm
{
    namespace
    {
        const std::size_t Address_NumberOfRaces = 0x00737cb8;
        const std::size_t Address_Races			= 0x00737cbc;

        const std::size_t Function_FindRaceByID	  = 0x0048b0c0;
        const std::size_t Function_FindRaceByName = 0x0048b100;
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

    std::vector<std::shared_ptr<Race>> Race::getAll()
    {
        std::vector<std::shared_ptr<Race>> results;
        types::Race** races = *reinterpret_cast<types::Race***>(Address_Races);
        const int NumberOfRaces = *reinterpret_cast<int*>(Address_NumberOfRaces);
        for (int i = 0; i < NumberOfRaces; ++i)
        {
            results.push_back(std::make_shared<Race>(races[i]));
        }
        return results;
    }

    std::shared_ptr<Race> Race::find(int id)
    {
        types::Race* race = (*memory_function<types::Race* (*)(int)>(Function_FindRaceByID))(id);
        if(race)
        {
            return std::make_shared<Race>(race);
        }
        return nullptr;
    }

    std::shared_ptr<Race> Race::find(const std::string& name)
    {
        types::Race* race = (*memory_function<types::Race* (*)(const char*)>(Function_FindRaceByName))(name.c_str());
        if(race)
        {
            return std::make_shared<Race>(race);
        }
        return nullptr;
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
}