#include "Cineractive_Internal.h"
#include "Type_Cineractive.h"
#include "Type_GameObject.h"
#include "Entity_Internal.h"
#include "Freighter_Internal.h"
#include "Path_Internal.h"

#include "Application.h"

namespace mmm
{
	namespace
	{
		const std::size_t Address_Cineractive = 0x007aeaf8;
		const std::size_t Address_Begin = 0x0064a0d0;
		const std::size_t Address_End = 0x0064b5d0;
		const std::size_t Address_LookAtGameObject = 0x0064bc00;
		const std::size_t Address_LookAtPosition = 0x0064bb80;
		const std::size_t Address_LookFromPosition = 0x0064ba50;
		const std::size_t Address_LookFromGameObject = 0x0064bab0;
		const std::size_t Address_LookFromPath = 0x0064afe0;
		const std::size_t Address_CameraOffset = 0x0064a160;
		const std::size_t Address_TargetOffset = 0x0064a240;

		bool skippable = true;
	}

	void 
	Cineractive::internal_begin( )
	{
		getScriptInterface()->CineractiveStart( 0, 0 );
		application_cineractiveBegin();
	}

	void 
	Cineractive::internal_end( bool forced )
	{
		memory_function< void (*)() >( Address_End )( );
		application_cineractiveFinish( forced );
	}

	Cineractive::Cineractive( )
	{

	}

	void 
	Cineractive::begin( )
	{
		skippable = true;
		internal_begin();
	}

	void 
	Cineractive::end( )
	{
		internal_end( false );
	}

	void
	Cineractive::forceEnd( )
	{
		internal_end( true );
	}

	bool 
	Cineractive::isActive( )
	{
		return application_isCineractive();
	}

	bool
	Cineractive::isSkippable( ) const
	{
		return skippable;
	}

	void
	Cineractive::setSkippable( bool value )
	{
		skippable = value;
	}

	void
	Cineractive::setActive( bool value )
	{
		if( value )
		{
			begin();
		}
		else
		{
			end();
		}
	}

	void 
	Cineractive::lookAt( EntityPtr object )
	{
		if( Cineractive().isActive() &&
			types::isGameObject( object->getEntity() ) )
		{
			types::Cineractive* cineractive = LoadMemPointer< types::Cineractive >( Address_Cineractive );
			if( cineractive )
			{
				(cineractive->*memory_function< void (types::Cineractive::*)(types::GameObject*) >
					( Address_LookAtGameObject ))( static_cast<types::GameObject*>( object->getEntity() ) );
			}
		}
	}

	void 
	Cineractive::lookAt( const Vector3& pos )
	{
		if( Cineractive().isActive() )
		{
			types::Cineractive* cineractive = LoadMemPointer< types::Cineractive >( Address_Cineractive );
			if( cineractive )
			{
				(cineractive->*memory_function< void (types::Cineractive::*)(const Vector3&) >
					( Address_LookAtPosition ))( pos );
			}
		}
	}

	void 
	Cineractive::lookFrom( const Vector3& pos )
	{
		if( Cineractive().isActive() )
		{
			types::Cineractive* cineractive = LoadMemPointer< types::Cineractive >( Address_Cineractive );
			if( cineractive )
			{
				(cineractive->*memory_function< void (types::Cineractive::*)(const Vector3&) >
					( Address_LookFromPosition ))( pos );
			}
		}
	}

	void 
	Cineractive::lookFrom( EntityPtr object )
	{
		if( Cineractive().isActive() &&
			types::isGameObject( object->getEntity() ) )
		{
			types::Cineractive* cineractive = LoadMemPointer< types::Cineractive >( Address_Cineractive );
			if( cineractive )
			{
				(cineractive->*memory_function< void (types::Cineractive::*)(types::GameObject*) >
					( Address_LookFromGameObject ))( static_cast<types::GameObject*>( object->getEntity() ) );
			}
		}
	}

	void 
	Cineractive::lookFrom( const Path& path, float speed )
	{
		if( Cineractive().isActive() )
		{
			memory_function< void (*)(const char*, float, int) >( Address_LookFromPath )
				(path.getName().c_str( ), speed, true);
		}
	}

	void 
	Cineractive::setCameraOffset( const Vector3& pos )
	{
		if( Cineractive().isActive() )
		{
			memory_function< void (*)(float,float,float,bool) >
				( Address_CameraOffset )( pos.x, pos.y, pos.z, true );
		}
	}

	void 
	Cineractive::fadeIn( float time )
	{
		if( Cineractive().isActive() )
		{
			getScriptInterface()->FadeIn( 0, time, 0, static_cast<float>(FADE_TYPE_BLACK), 1 );
		}
	}

	void
	Cineractive::fadeOut( float time )
	{
		if( Cineractive().isActive() )
		{
			getScriptInterface()->FadeOut( 0, time, 0, static_cast<float>(FADE_TYPE_BLACK), 1 );
		}
	}
}

