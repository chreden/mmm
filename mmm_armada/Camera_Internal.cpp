#include "Camera_Internal.h"
#include "Path_Internal.h"
#include "Entity_Internal.h"
#include "Type_ST3D_GraphicsEngine.h"
#include "Type_ST3D_GraphicsEngine_Configuration.h"
#include "Type_ST3D_DisplayMode.h"
#include "Type_ST3D_Camera.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        constexpr std::size_t Address_ProjectPoint  = 0x00618890;
        constexpr std::size_t Address_gCameraManager = 0x00763370;
        Camera camera;

        struct GameCamera
        {
            std::size_t* vtable;
        };

        struct CameraManager
        {
            GameCamera* m_pCamera;
        };

        Vector3 GetCameraInterest()
        {
            CameraManager* camera_manager = reinterpret_cast<CameraManager*>(Address_gCameraManager);
            return *(camera_manager->m_pCamera->*memory_function<Vector3 * (GameCamera::*)()>
                (camera_manager->m_pCamera->vtable[23]))();
        }

        int camera_center(lua_State* L)
        {
            if (is_entity(L, 2))
            {
                camera.center(get_entity<Entity>(L, 2));
            }
            else if (is_path(L, 2))
            {
                camera.center(*get_userdata<std::shared_ptr<Path>>(L, 2), lua_tonumber(L, 3));
            }
            else if (is_vector(L, 2))
            {
                camera.center(get_userdata<Vector3>(L, 2));
            }
            return 0;
        }

        int camera_project(lua_State* L)
        {
            camera.project(get_userdata<Vector3>(L, 2));
            return 0;
        }

        int camera_zoom(lua_State* L)
        {
            camera.zoom(lua_tonumber(L, 2));
            return 0;
        }

        int camera_index(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);
            if (key == "center")
            {
                lua_pushcfunction(L, camera_center);
                return 1;
            }
            else if (key == "project")
            {
                lua_pushcfunction(L, camera_project);
                return 1;
            }
            else if (key == "target")
            {
                return vector_new(L, camera.getTarget());
            }
            else if (key == "zoom")
            {
                lua_pushcfunction(L, camera_zoom);
                return 1;
            }
            return 0;
        }

        int camera_newindex(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);
            if (key == "target")
            {
                camera.center(get_userdata<Vector3>(L, 2));
                return 0;
            }
            return 0;
        }
    }

    void Camera::center(const Vector3& position)
    {
        getScriptInterface()->CenterCamera(position);
    }

    void Camera::center(const std::shared_ptr<Entity>& entity)
    {
        getScriptInterface()->CenterCamera(entity->getID());
    }

    void Camera::center(const Path& path, int index)
    {
        getScriptInterface()->CenterCamera(path.getName().c_str(), index);
    }

    void Camera::zoom(float value)
    {
        getScriptInterface()->SetCameraZoom(value);
    }

    Vector3 Camera::project(const Vector3& position)
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
        if(camera)
        {
            Vector2 pos = (camera->*memory_function<Vector2 (types::ST3D_Camera::*)(const Vector3&)>(Address_ProjectPoint))
                (position);
            return Vector3(pos.x * (UiWidth / screenWidth),
                            pos.y * (UiHeight / screenHeight),
                            0);
        }
        return Vector3();
    }

    Vector3 Camera::getTarget() const
    {
        return GetCameraInterest();
    }

    void camera_register(lua_State* L)
    {
        lua_newtable(L);
        create_metatable(L,
            {
                { "__index", camera_index },
                { "__newindex", camera_newindex }
            });
        lua_setglobal(L, "Camera");
    }
}