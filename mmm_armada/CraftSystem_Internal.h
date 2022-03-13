#pragma once

namespace mmm
{
	namespace types { struct CraftSystem; }

	class CraftSystem
	{
	public:
		explicit CraftSystem( CraftPtr craft, types::CraftSystem* system );

		bool getActive() const;
		bool getPermanentDisable() const;
		float getHitpoints() const;
		float getHealth() const;
		long getMaxHitpoints() const;

		void setActive( bool value );
		void setPermanentDisable( bool value );
		void setHitpoints( float value );
		void setHealth( float value );
		void setMaxHitpoints( long value );
	private:
		CraftPtr			craft_;
		types::CraftSystem* system_;
	};

	void craftsystem_register( lua_State* state );
}
