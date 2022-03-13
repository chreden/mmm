#include "Debug_Internal.h"
#include <windows.h>
#include "MapAdapter.h"

#include "Type_ST3D_GraphicsEngine.h"
#include "Type_ST3D_GraphicsEngine_Configuration.h"
#include "Type_ST3D_DisplayMode.h"
#include "Type_ST3D_Camera.h"
#include "PrintMessages.h"
#include "DebuggerConnection.h"

#include "Type_ST3D_Device.h"
#include "Type_ST3D_Sprite.h"
#include "Type_ST3D_AnimationChannel.h"

#include <regex>

namespace mmm
{
	namespace
	{
		const std::size_t Address_DebugDraw = 0x0070dcdc;			
	}

	std::string 
	Debug::getCommandLine() const
	{
		std::string commandLine( GetCommandLineA() );

		std::cmatch results;
		std::regex rx( "\/mod \".+\"" );
		std::regex_search( commandLine.c_str(), results, rx );

		if( results.empty( ) )
		{
			return "";
		}

		std::string thing = results[0];
		
		std::size_t firstPos = thing.find_first_of( "\"" );
		std::size_t endPos = thing.find_last_of( "\"" );
		std::string mod = thing.substr( firstPos + 1, endPos - firstPos - 1 );
		 
		return "mods/" + mod + "/";
	}

	bool 
	Debug::getDebugDraw( )
	{
		return GetMemVariable< int >( Address_DebugDraw ) != 0;
	}

	void 
	Debug::setDebugDraw( bool value )
	{
		SetMemVariable< int >( value, Address_DebugDraw );
	}

	void 
	Debug::createConsole( )
	{
		AllocConsole( );
		freopen( "CONOUT$", "w", stdout );
	}

	bool
	Debug::getKeyState( const std::string& key )
	{
		return 0 != GetAsyncKeyState( VkKeyScan( key[0] ) );
	}

	//Global database.
	struct ST3D_Database
	{

	};

	/*
		ST3D_Class_Sprite
		ST3D_Class_LightingMaterial
		ST3D_Class_TextureMaterial
		ST3D_Class_AnimationChannel
		ST3D_Class_Node
		ST3D_Class_Texture
		ST3D_Class_SpriteNodeData
		ST3D_Class_TextSequence
		ST3D_Class__Size
	*/
		
	void
	Debug::circle( const Vector3& centre, float radius, int thickness,
			ST3D_Colour& colour, void* material )
	{
		types::ST3D_GraphicsEngine* engine = types::getGraphicsEngine();

		types::ST3D_Database* globaldb = engine->m_global_db;

		void* t = (globaldb->*memory_function<void* (types::ST3D_Database::*)( const char*, int )>( 0x00620750 ))
			("default", 2 );

		types::ST3D_Camera* camera = types::getCurrentCamera();
		if( camera )
		{
			(camera->*memory_function< void (types::ST3D_Camera::*)( const Vector3&, float, int, ST3D_Colour&, void*)>( 0x00619e40 ))
				( centre, radius, thickness, colour, t );
		}
	}

	void
	Debug::connect( const std::string& ip )
	{
		DebuggerConnection::getInstance().connect(ip);
	}

	void
	Debug::disconnect( )
	{
		DebuggerConnection::getInstance().disconnect();
	}

	Vector3
	Debug::testCursor()
	{
		using namespace types;
		ST3D_Device* device = getGraphicsEngine()->m_device[0];
		if( device )
		{
			if( device->m_cursor_sprite )
			{
				ST3D_AnimationChannel* channel = device->m_cursor_sprite->m_animation_channel_list.head_->next_->value_;
				if( channel )
				{
					AnimationChannel<Vector2>* vChannel = static_cast<AnimationChannel<Vector2>*>( channel );
					Vector2& v = vChannel->m_keyframe_data[ channel->m_current_keyframe ];
					return Vector3( v.x, v.y, 0 );
				}
			}
		}
		return Vector3();
	}
}