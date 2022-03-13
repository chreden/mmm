#include "Media_Internal.h"
#include "Team_Internal.h"
#include "Race_Internal.h"

namespace mmm
{
	namespace
	{
		const std::size_t Address_MissionRace = 0x00737cc0;
		const std::size_t Address_Jukebox	  = 0x00736728;
		const std::size_t Address_JukeboxStop = 0x00463660;
		const std::size_t Address_JukeboxPlay = 0x00463640;

		std::set<int> audioMessages;
	}

	void 
	Media::playSound( const std::string& filename )
	{
		audioMessages.insert( getScriptInterface( )->AudioMessage( 0, filename.c_str( ), true ) );
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

	void 
	Media::playMusic( const std::string& filename )
	{
		Race race( *reinterpret_cast<types::Race**>( Address_MissionRace ) );
		const std::string oldMusic = race.getSinglePlayerMusic();

		race.setSinglePlayerMusic( filename );


		JukeBox* jukebox = reinterpret_cast<JukeBox*>( Address_Jukebox );

		(jukebox->*memory_function< void (JukeBox::*)() >( Address_JukeboxStop ))();
		(jukebox->*memory_function< void (JukeBox::*)() >( Address_JukeboxPlay ))();

		race.setSinglePlayerMusic( oldMusic );
	}

	void 
	Media::playMovie( const std::string& filename )
	{
		getScriptInterface( )->PlayCinematicMovie( 0, const_cast<char*>( filename.c_str( ) ), 0, 0 );
	}

	void
	Media::stopMovie( )
	{
		getScriptInterface( )->StopMovie( );
	}

	void
	Media::stopMusic( )
	{
		JukeBox* jukebox = reinterpret_cast<JukeBox*>( Address_Jukebox );
		(jukebox->*memory_function< void (JukeBox::*)() >( Address_JukeboxStop ))();
	}

	void
	Media::stopSounds( )
	{
		for( auto iter = audioMessages.begin();
			 iter != audioMessages.end();
			 ++iter )
		{
			getScriptInterface()->StopAudioMessage( *iter );
		}
		audioMessages.clear();
	}

	void 
	Media::update( )
	{
		ScriptInterface* si = getScriptInterface();

		std::set<int> audioMessagesCopy = audioMessages;
		for( auto iter = audioMessagesCopy.begin();
			 iter != audioMessagesCopy.end();
			 ++iter )
		{
			int id = *iter;
			if( si->IsAudioMessageDone( id ) )
			{
				audioMessages.erase( id );
			}
		}
	}
}
