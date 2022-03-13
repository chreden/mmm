#pragma once

#include "Entity_Internal.h"
#include "ResourceInterface_Internal.h"

namespace mmm
{
	namespace types
	{
		struct GameObject;
	}
		
	class Path;

	class GameObject : public Entity, public ResourceInterface
	{
	public:
		static GameObjectPtr create( types::Entity* entity );
		virtual				~GameObject(){};
		const std::string	getOdf( ) const;
		const std::string	getHandle( ) const;
		bool				getInvincible( ) const;
		const Vector3		getVelocity( ) const;
		TeamPtr				getTeam( ) const;
		TeamPtr				getPerceivedTeam( ) const;
		float				getHealth( ) const;
		float				getHitpoints() const;
		float				getMaximumHealth( ) const;
		float				getSpecialEnergy( ) const;
		float				getSpecialEnergyValue( ) const;
		float				getMaxSpecialEnergy( ) const;
		bool				getForceOntoMap( ) const;
		GameObjectClassPtr  getClass() const;
		RacePtr				getRace() const;
		void				setHealth( float value );
		void				setHitpoints( float value );
		void				setMaximumHealth( float value );
		void				setSpecialEnergy( float value );
		void				setMaxSpecialEnergy( float value );
		void				setSpecialEnergyValue( float value );
		bool				isDestroyed( ) const;
		bool				isUnderAttack( ) const;
		bool				canCloak( ) const;
		bool				isCloaked( ) const;
		bool				isAiControlled( ) const;
		void				setInvincible( bool value );
		void				setVelocity( const Vector3& vec );
		void				setTeam( TeamPtr team );
		void				setPerceivedTeam( TeamPtr team );
		void				setForceOntoMap( bool value );
		void				cloak( );
		void				decloak( );
		void				immediateCloak( );
		void				giveOrder( AiCommand order, const Vector3& pos );
		void				giveOrder( AiCommand order, EntityPtr ent );
		void				giveOrder( AiCommand order, const std::string& cls, const Vector3& pos );
		void				giveOrder( AiCommand order, const Path& path );
		void				giveOrder( AiCommand order, long value );
		void				giveOrder( AiCommand order );
		void				addWeapon( const std::string& weapon );
		types::GameObject*	getGameObject() const;
		ResourceInterface	getResourceInterface() const;
	protected:
		explicit			GameObject( types::GameObject* entity );
		virtual void allocateReplacement( luabind::detail::object_rep* obj );
	};

	void gameobject_register( lua_State* state );
}