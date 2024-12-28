#include "GameObject_Internal.h"
#include "GameObjectClass_Internal.h"
#include "Race_Internal.h"
#include "Team_Internal.h"
#include "Path_Internal.h"

#include "Type_GameObject.h"
#include "Type_Team.h"
#include "Type_Weapons.h"

namespace mmm
{
    namespace
    {
        const std::size_t Address_SetHealth			= 0x004d2080;
        const std::size_t Address_SetMaximumHealth	= 0x004d2020;
        const std::size_t Address_GetOdfName		= 0x004d5620;
        const std::size_t Address_Cloak				= 0x004d5160;
        const std::size_t Address_Decloak			= 0x004d51b0;
        const std::size_t Address_CanCloak			= 0x004d51f0;
        const std::size_t Address_ImmediateCloak	= 0x004d03e0;
        const std::size_t Address_IsCloaked			= 0x004d03f0;
        const std::size_t Address_SetTeam			= 0x004d0f10;
        const std::size_t Address_SwapTeam			= 0x004d0ea0;
        const std::size_t Address_IsAIControlled	= 0x004d5290;
        const std::size_t Address_IsUnderAttack		= 0x004d1530; 
        const std::size_t Address_GiveOrderPos		= 0x004d1b50;
        const std::size_t Address_GiveOrderEnt		= 0x004d1af0;
        const std::size_t Address_GiveOrderClassPos	= 0x004d1cb0;
        const std::size_t Address_GiveOrderPath		= 0x004d1b80;
    }

    GameObjectPtr 
    GameObject::create( types::Entity* entity )
    {
        return GameObjectPtr( new GameObject( static_cast<types::GameObject*>( entity ) ) ); 
    }

    GameObject::GameObject( types::GameObject* entity )
        : Entity( entity ), ResourceInterface( entity )
    {
            
    }

    types::GameObject* 
    GameObject::getGameObject() const
    {
        return static_cast<types::GameObject*>( getEntity() );
    }

    const std::string
    GameObject::getOdf( ) const
    {
        std::string odfname = (getGameObject()->*memory_function< const char* (types::GameObject::*) () >( Address_GetOdfName ))();
        std::transform( odfname.begin(), odfname.end(), odfname.begin(), tolower );
        return odfname;
    }

    const std::string
    GameObject::getHandle( ) const
    {
        return getGameObject()->label;
    }

    bool
    GameObject::getInvincible( ) const
    {
        types::GameObject* object = getGameObject();
        return object->m_invincible != 0;
    }

    const Vector3 
    GameObject::getVelocity( ) const
    {
        types::GameObject* object = getGameObject();
        return object->m_euler.m_vel;
    }

    TeamPtr
    GameObject::getTeam( ) const 
    {
        types::GameObject* object = getGameObject();
        return TeamPtr( new Team( object->teamNumber ) );
    }

    TeamPtr
    GameObject::getPerceivedTeam( ) const
    {
        types::GameObject* object = getGameObject();
        return TeamPtr( new Team( object->perceivedTeam ) );
    }

    float 
    GameObject::getHealth( ) const
    {
        return getHitpoints() / getMaximumHealth();
    }

    float 
    GameObject::getHitpoints( ) const
    {
        return getScriptInterface( )->GetCurrentHealth( getID() );
    }

    float 
    GameObject::getMaximumHealth( ) const
    {
        return getScriptInterface( )->GetMaxHealth( getID() );
    }

    float
    GameObject::getSpecialEnergy( ) const
    {
        return getGameObject()->m_curSpecialEnergy;
    }

    float
    GameObject::getSpecialEnergyValue() const
    {
        return getSpecialEnergy() * getMaxSpecialEnergy();
    }

    float
    GameObject::getMaxSpecialEnergy( ) const
    {
        return getGameObject()->m_maxSpecialEnergy;
    }

    GameObjectClassPtr
    GameObject::getClass( ) const
    {
        return createGameObjectClassPtr( getGameObject()->m_class );
    }

    RacePtr				
    GameObject::getRace() const
    {
        return RacePtr( new Race( getGameObject()->m_pRace ) );
    }

    bool
    GameObject::isDestroyed( ) const
    {
        types::GameObject* object = getGameObject();
        return object->m_is_destroyed;
    }

    bool 
    GameObject::isUnderAttack( ) const
    {
        float interval = 5.0f;
        return (getGameObject()->*memory_function< bool (types::GameObject::*)(float) const >( Address_IsUnderAttack ))( interval );
    }

    bool
    GameObject::canCloak( ) const
    {
        return (getGameObject()->*memory_function< bool (types::GameObject::*)() >( Address_CanCloak ))();
    }

    bool 
    GameObject::isCloaked( ) const
    {
        return (getGameObject()->*memory_function< bool (types::GameObject::*)() >( Address_IsCloaked ))();
    }

    bool 
    GameObject::isAiControlled( ) const
    {
        return (getGameObject()->*memory_function< bool (types::GameObject::*)() >( Address_IsAIControlled ))();
    }

    void 
    GameObject::setInvincible( bool value )
    {
        types::GameObject* object = getGameObject();
        object->m_invincible = value;
    }

    void 
    GameObject::setHealth( float value )
    {
        (getGameObject()->*memory_function< void (types::GameObject::*) ( float ) >( Address_SetHealth ))( value * getMaximumHealth() );
    }

    void 
    GameObject::setHitpoints( float value )
    {
        (getGameObject()->*memory_function< void (types::GameObject::*) ( float ) >( Address_SetHealth ))( value );
    }

    void 
    GameObject::setMaximumHealth( float value )
    {
        (getGameObject()->*memory_function< void (types::GameObject::*) ( float ) >( Address_SetMaximumHealth ))( value );
    }

    void					
    GameObject::setSpecialEnergy( float value )
    {
        getGameObject()->m_curSpecialEnergy = value * getMaxSpecialEnergy();
    }

    void					
    GameObject::setMaxSpecialEnergy( float value )
    {
        getGameObject()->m_maxSpecialEnergy = value;
    }

    void					
    GameObject::setSpecialEnergyValue( float value )
    {
        getGameObject()->m_maxSpecialEnergy = value;
    }

    void 
    GameObject::setVelocity( const Vector3& vec )
    {
        getGameObject()->m_euler.m_vel = vec;
    }

    void 
    GameObject::setTeam( TeamPtr team )
    {
        types::GameObject* object = getGameObject();
        object->teamNumber = team->getNumber();
        object->perceivedTeam = team->getNumber();
        object->m_pRace = team->getRace()->getRace();
    }

    void
    GameObject::setPerceivedTeam( TeamPtr team )
    {
        types::GameObject* object = getGameObject();
        object->perceivedTeam	= team->getNumber();
        object->m_pRace			= team->getRace()->getRace();
    }

    bool
    GameObject::getForceOntoMap( ) const
    {
        types::GameObject* object = getGameObject();
        return 	object->m_force_onto_map;
    }

    void
    GameObject::setForceOntoMap( bool value )
    {
        types::GameObject* object = getGameObject();
        object->m_force_onto_map = value;
    }

    void 
    GameObject::cloak( )
    {
        (getGameObject()->*memory_function< void (types::GameObject::*)() >( Address_Cloak ))();
    }

    void 
    GameObject::decloak( )
    {
        (getGameObject()->*memory_function< void (types::GameObject::*)() >( Address_Decloak))();
    }

    void 
    GameObject::immediateCloak( )
    {
        (getGameObject()->*memory_function< void (types::GameObject::*)() >( Address_ImmediateCloak ))();
    }

    void 
    GameObject::giveOrder( AiCommand order, const Vector3& pos )
    {
        (getGameObject()->*memory_function< void (types::GameObject::*)( AiCommand, const Vector3&, long, bool )>( Address_GiveOrderPos ))
            ( order, pos, 0, false );
    }

    void
    GameObject::giveOrder( AiCommand order, EntityPtr ent )
    {
        if( ent->isType( Entity_GameObject ) )
        {
            (getGameObject()->*memory_function< void (types::GameObject::*)( AiCommand, const types::GameObject*, long, bool )>( Address_GiveOrderEnt ))
                ( order, boost::static_pointer_cast<GameObject>( ent )->getGameObject(), 0, false );
        }
    }

    void
    GameObject::giveOrder( AiCommand order, const std::string& cls, const Vector3& pos )
    {
        std::string lowerClassName(cls);
        std::transform( lowerClassName.begin(), lowerClassName.end(), lowerClassName.begin(), ::tolower );

        void* objectClass = FindGameObjectClass( lowerClassName.c_str( ) );
        if( objectClass )
        {
            (getGameObject()->*memory_function< void (types::GameObject::*)( AiCommand, void*, const Vector3&, bool )>( Address_GiveOrderClassPos ))
                ( order, objectClass, pos, false );
        }
    }

    void
    GameObject::giveOrder( AiCommand order, const Path& path )
    {
        (getGameObject()->*memory_function< void (types::GameObject::*)(AiCommand, types::AiPath*, bool, bool)>( Address_GiveOrderPath ))
            (order, path.getPath(), true, false );
    }

    void
    GameObject::giveOrder( AiCommand order, long what )
    {
        getScriptInterface()->SetCommandWhatWhoParamVO( getGameObject()->m_entity_id,
                                                        order,
                                                        getGameObject()->m_entity_id,
                                                        what,
                                                        false );
    }

    void				
    GameObject::giveOrder( AiCommand order )
    {
        getScriptInterface()->SetCommandWhatWhoParamVO( getGameObject()->m_entity_id,
                                                        order,
                                                        getGameObject()->m_entity_id,
                                                        0,
                                                        false );
                                                        
    }

    void				
    GameObject::addWeapon( const std::string& weapon )
    {
        struct cPrjID
        {
            int m_id;
        };

        cPrjID testID = { 0 };
        (testID.*memory_function< void (cPrjID::*)(const char*) >( 0x006593c0 ))( weapon.c_str() );

        void* wpn = (memory_function< void* (*)(const cPrjID&) >( 0x00664850 ))( testID );

        types::Carrier* carrier = static_cast<types::Carrier*>( getGameObject()->carrier );
        (carrier->*memory_function< void (types::Carrier::*)(void*, unsigned char) >( 0x006682d0 ))(wpn, 0);
    }

    ResourceInterface
    GameObject::getResourceInterface( ) const
    {
        return ResourceInterface( *this );
    }

    Vector3 GameObject::getAlpha() const
    {
        return getGameObject()->m_euler.alpha;
    }

    Vector3 GameObject::getOmega() const
    {
        return getGameObject()->m_euler.omega;
    }

    Vector3 GameObject::getAccel() const
    {
        return getGameObject()->m_euler.accel;
    }

    void GameObject::setAlpha(const Vector3& alpha)
    {
        getGameObject()->m_euler.alpha = alpha;
    }

    void GameObject::setOmega(const Vector3& omega)
    {
        getGameObject()->m_euler.omega = omega;
    }

    void GameObject::setAccel(const Vector3& accel)
    {
        getGameObject()->m_euler.accel = accel;
    }

    void 
    GameObject::allocateReplacement( luabind::detail::object_rep* obj )
    {
        entity_allocate_replacement<GameObject>( obj, boost::static_pointer_cast<GameObject>( shared_from_this() ) );
    }

    void GameObject::setRace(RacePtr race)
    {
        getGameObject()->m_pRace = race->getRace();
    }
}
