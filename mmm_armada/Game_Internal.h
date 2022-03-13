#pragma once

namespace mmm
{
    /**
        Contains functions that have a game wide scope, or those which do not
        yet have an appropriate area to reside in.
    */
	class Game
	{
	public:
        /**
            Get the current game time. This is the number of seconds since the
            scenario was started. 
            @remark Time does not advance when the game is paused or the player is in a menu.
            @return The time since the start of the scenario.
        */
		float		getTime()		const;
        /**
            Get whether the current map allows warp travel.
            @remark This only really has any effect in stock.
            @return Whether or not warp is enabled.
        */
		bool		getAllowWarp()  const;

		bool		getAllowSave()  const;
        /**
            Get the value used to seed the random number generator used
            by the game.
            @remark This is shared across all players in a network game.
            @return The seed value.
        */
		int			getSeed()		const;
		int			getLocalSlot()  const;
		float		getUpdateTime() const;
		const char* getMapTitle()	const;
		bool		isHost()		const;
		int			getGameSpeed()  const;
		void		setAllowSave( bool value );
		void		setAllowWarp( bool value );
		void		setUpdateTime( float interval );
		void		setGameSpeed( int value );
		/**
			Get the active window for the game.
			@return The game window.
		*/
		HWND		getWindow() const;
	};
	
	void game_register( lua_State* state );
}
