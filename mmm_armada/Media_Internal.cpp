#include "Media_Internal.h"
#include "Team_Internal.h"
#include "Race_Internal.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        const std::size_t Address_MissionRace = 0x00737cc0;
        const std::size_t Address_Jukebox	  = 0x00736728;
        const std::size_t Address_JukeboxStop = 0x00463660;
        const std::size_t Address_JukeboxPlay = 0x00463640;

        // FO 4 beta music player
        constexpr std::size_t Seg_Code = 0x5A801000;
        constexpr std::size_t Seg_Bss = 0x5AA14000;
        constexpr std::size_t Address_FO_Jukebox = Seg_Bss + 0x00032A24;
        constexpr std::size_t Address_FO_Jukebox_Stop = Seg_Code + 0x001D4008;
        constexpr std::size_t Address_FO_Jukebox_Play = Seg_Code + 0x001D4004;

        std::set<int> audioMessages;

        Media media;

        int media_play_sound(lua_State* L)
        {
            media.playSound(lua_tostring(L, 2));
            return 0;
        }

        int media_play_music(lua_State* L)
        {
            media.playMusic(lua_tostring(L, 2));
            return 0;
        }

        int media_play_movie(lua_State* L)
        {
            media.playMovie(lua_tostring(L, 2));
            return 0;
        }

        int media_stop_movie(lua_State* L)
        {
            media.stopMovie();
            return 0;
        }

        int media_stop_music(lua_State* L)
        {
            media.stopMusic();
            return 0;
        }

        int media_stop_sounds(lua_State* L)
        {
            media.stopSounds();
            return 0;
        }

        int media_index(lua_State* L)
        {
            std::string key = lua_tostring(L, 2);

            if (key == "playSound")
            {
                lua_pushcfunction(L, media_play_sound);
                return 1;
            }
            else if (key == "playMusic")
            {
                lua_pushcfunction(L, media_play_music);
                return 1;
            }
            else if (key == "playMovie")
            {
                lua_pushcfunction(L, media_play_movie);
                return 1;
            }
            else if (key == "stopMovie")
            {
                lua_pushcfunction(L, media_stop_movie);
                return 1;
            }
            else if (key == "stopMusic")
            {
                lua_pushcfunction(L, media_stop_music);
                return 1;
            }
            else if (key == "stopSounds")
            {
                lua_pushcfunction(L, media_stop_sounds);
                return 1;
            }

            return 0;
        }
    }

    void Media::playSound(const std::string& filename)
    {
        audioMessages.insert(getScriptInterface()->AudioMessage(0, filename.c_str(), true));
    }

    /*
        enum AudioSound::__unnamed_20_ {
            NO_FLAGS = 0x0,
            LOOPING = 0x1,
            STRATEGIC_IGNORE_HEIGHT = 0x2,
            IGNORE_MUTING = 0x4,
            IGNORE_PAUSE = 0x8,
            KILL_ON_PAUSE = 0x10,
            DONT_CACHE = 0x20,
        };
    */

    struct AudioSound 
    {
        char _padding_[0x8];
        long m_flags;
        //There is more but not important
    };

    struct JukeBox // : public gamefeature
    { 
        char		_padding_[0x2c];
        AudioSound* m_currentTrack;
    };

    struct FO_Jukebox
    {
    };

    void Media::playMusic(const std::string& filename)
    {
        if (common::fleetops_version().major >= 4)
        {
            Race race(*reinterpret_cast<types::Race**>(Address_MissionRace));
            race.setSinglePlayerMusic(filename);

            JukeBox* jukebox = reinterpret_cast<JukeBox*>(Address_Jukebox);
            (jukebox->*memory_function< void (JukeBox::*)() >(Address_JukeboxStop))();
        }
        else
        {
            Race race(*reinterpret_cast<types::Race**>(Address_MissionRace));
            const std::string oldMusic = race.getSinglePlayerMusic();

            race.setSinglePlayerMusic(filename);

            JukeBox* jukebox = reinterpret_cast<JukeBox*>(Address_Jukebox);

            (jukebox->*memory_function< void (JukeBox::*)() >(Address_JukeboxStop))();
            (jukebox->*memory_function< void (JukeBox::*)() >(Address_JukeboxPlay))();

            race.setSinglePlayerMusic(oldMusic);
        }
    }

    void Media::playMovie(const std::string& filename)
    {
        getScriptInterface()->PlayCinematicMovie(0, const_cast<char*>(filename.c_str()), 0, 0);
    }

    void Media::stopMovie()
    {
        getScriptInterface()->StopMovie();
    }

    void Media::stopMusic()
    {
        if (common::fleetops_version().major >= 4)
        {
            Race race(*reinterpret_cast<types::Race**>(Address_MissionRace));
            race.setSinglePlayerMusic("");

            JukeBox* jukebox = reinterpret_cast<JukeBox*>(Address_Jukebox);
            (jukebox->*memory_function< void (JukeBox::*)() >(Address_JukeboxStop))();
        }
        else
        {
            JukeBox* jukebox = reinterpret_cast<JukeBox*>(Address_Jukebox);
            (jukebox->*memory_function< void (JukeBox::*)() >(Address_JukeboxStop))();
        }
    }

    void Media::stopSounds()
    {
        for(auto iter = audioMessages.begin(); iter != audioMessages.end(); ++iter )
        {
            getScriptInterface()->StopAudioMessage(*iter);
        }
        audioMessages.clear();
    }

    void Media::update()
    {
        ScriptInterface* si = getScriptInterface();

        std::set<int> audioMessagesCopy = audioMessages;
        for( auto iter = audioMessagesCopy.begin(); iter != audioMessagesCopy.end(); ++iter )
        {
            int id = *iter;
            if(si->IsAudioMessageDone(id))
            {
                audioMessages.erase(id);
            }
        }
    }

    void media_register(lua_State* L)
    {
        lua_newtable(L);
        create_metatable(L,
            {
                { "__index", media_index }
            });
        lua_setglobal(L, "Media");
    }
}
