#include "Media_Internal.h"
#include "Team_Internal.h"
#include "Race_Internal.h"

namespace mmm
{
    namespace
    {
        const std::size_t Address_MissionRace = 0x00737cc0;
        const std::size_t Address_Jukebox     = 0x00736728;
        const std::size_t Address_JukeboxStop = 0x00463660;
        const std::size_t Address_JukeboxPlay = 0x00463640;

        // FO 4 beta music player
        constexpr std::size_t Seg_Code = 0x5A801000;
        constexpr std::size_t Seg_Bss = 0x5AA14000;
        constexpr std::size_t Address_FO_Jukebox = Seg_Bss + 0x00032A24;
        constexpr std::size_t Address_FO_Jukebox_Stop = Seg_Code + 0x001D4008;
        constexpr std::size_t Address_FO_Jukebox_Play = Seg_Code + 0x001D4004;

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

        std::set<int> audioMessages;

        void play_sound(const std::string& filename)
        {
            audioMessages.insert(getScriptInterface()->AudioMessage(0, filename.c_str(), true));
        }

        void play_music(const std::string& filename)
        {
            if (common::fleetops_version().major >= 4)
            {
                Race race(*reinterpret_cast<types::Race**>(Address_MissionRace));
                race.setSinglePlayerMusic(filename);

                FO_Jukebox* jukebox = reinterpret_cast<FO_Jukebox*>(Address_FO_Jukebox);
                (jukebox->*memory_function<void (FO_Jukebox::*)()>(Address_FO_Jukebox_Stop))();
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

        void play_movie(const std::string& filename)
        {
            getScriptInterface()->PlayCinematicMovie(0, const_cast<char*>(filename.c_str()), 0, 0);
        }

        void stop_movie()
        {
            getScriptInterface()->StopMovie();
        }

        void stop_music()
        {
            if (common::fleetops_version().major >= 4)
            {
                Race race(*reinterpret_cast<types::Race**>(Address_MissionRace));
                race.setSinglePlayerMusic("");

                FO_Jukebox* jukebox = reinterpret_cast<FO_Jukebox*>(Address_FO_Jukebox);
                (jukebox->*memory_function<void (FO_Jukebox::*)()>(Address_FO_Jukebox_Stop))();
            }
            else
            {
                JukeBox* jukebox = reinterpret_cast<JukeBox*>(Address_Jukebox);
                (jukebox->*memory_function< void (JukeBox::*)() >(Address_JukeboxStop))();
            }
        }

        void stop_sounds()
        {
            for (const auto& id : audioMessages)
            {
                getScriptInterface()->StopAudioMessage(id);
            }
            audioMessages.clear();
        }

        int play_sound(lua_State* L)
        {
            luaL_checktype(L, 1, LUA_TSTRING);
            play_sound(lua_tostring(L, 1));
            return 0;
        }

        int play_music(lua_State* L)
        {
            luaL_checktype(L, 1, LUA_TSTRING);
            play_music(lua_tostring(L, 1));
            return 0;
        }

        int play_movie(lua_State* L)
        {
            luaL_checktype(L, 1, LUA_TSTRING);
            play_movie(lua_tostring(L, 1));
            return 0;
        }

        int stop_movie(lua_State* L)
        {
            stop_movie();
            return 0;
        }

        int stop_music(lua_State* L)
        {
            stop_music();
            return 0;
        }

        const luaL_reg media_funcs[] =
        {
            { "playSound", play_sound },
            { "playMusic", play_music },
            { "playMovie", play_movie },
            { "stopMovie", stop_movie },
            { "stopMusic", stop_music },
            { nullptr, nullptr }
        };
    }

    void media_update()
    {
        ScriptInterface* si = getScriptInterface();
        std::set<int> audioMessagesCopy = audioMessages;
        for (const auto& id : audioMessagesCopy)
        {
            if (si->IsAudioMessageDone(id))
            {
                audioMessages.erase(id);
            }
        }
    }

    void media_register(lua_State* L)
    {
        luaL_register(L, "Media", media_funcs);
    }
}
