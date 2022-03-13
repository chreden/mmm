#include "Camera_Internal.h"
#include "Path_Internal.h"
#include "Entity_Internal.h"

#include "Type_ST3D_GraphicsEngine.h"
#include "Type_ST3D_GraphicsEngine_Configuration.h"
#include "Type_ST3D_DisplayMode.h"
#include "Type_ST3D_Camera.h"

namespace mmm
{
	namespace
	{
		const std::size_t Address_ProjectPoint  = 0x00618890;
	}

	void			 
	Camera::center( const Vector3& position )
	{
		getScriptInterface()->CenterCamera( position );
	}

	void
	Camera::center( EntityPtr entity )
	{
		getScriptInterface()->CenterCamera( entity->getID() );
	}

	void
	Camera::center( const Path& path, int index )
	{
		getScriptInterface()->CenterCamera(path.getName().c_str(), index );
	}

	void			 
	Camera::zoom( float value )
	{
		getScriptInterface()->SetCameraZoom( value );
	}

	Vector3 
	Camera::project( const Vector3& position )
	{
		struct Vector2
		{
			float x, y;
		};

		types::ST3D_GraphicsEngine* engine = types::getGraphicsEngine();
			
		float screenWidth = engine->m_gfx_config->m_display_mode[0]->m_width;
		float screenHeight = engine->m_gfx_config->m_display_mode[0]->m_height;

		const float UiWidth = 1600;
		const float UiHeight = 1200;

		types::ST3D_Camera* camera = types::getCurrentCamera();
		if( camera )
		{
			Vector2 pos = (camera->*memory_function<Vector2 (types::ST3D_Camera::*)(const Vector3&)>( Address_ProjectPoint ))
				(position);
			return Vector3( pos.x * (UiWidth / screenWidth), 
							pos.y * (UiHeight / screenHeight),
							0 ); 
		}
		return Vector3();
	}
}