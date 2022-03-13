#pragma once

namespace mmm
{
	namespace types
	{
		struct GameObjectClass;
	}

	class GameObjectClass
	{
	public:
		static GameObjectClassPtr create( types::GameObjectClass* ptr );
		virtual ~GameObjectClass();

		const std::string getLabel() const;
		const std::string getUnitString() const;
		long			  getMaxSpecialEnergy() const;
		const std::string getODF() const;

		void setUnitString( const std::string& name );
		void setMaxSpecialEnergy( long value );
		
		types::GameObjectClass* getClass() const;
	protected:
		explicit GameObjectClass( types::GameObjectClass* goClass );
	private:
		types::GameObjectClass* class_;
	};

	void gameobjectclass_register( lua_State* state );

	GameObjectClassPtr createGameObjectClassPtr( types::GameObjectClass* ptr );
}
