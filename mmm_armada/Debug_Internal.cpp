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

#include "LuaBinding.h"

#include <regex>

namespace mmm
{
    namespace
    {
        const std::size_t Address_DebugDraw = 0x0070dcdc;

        Debug debug;

        int debug_circle(lua_State* L)
        {
            debug.circle(get_userdata<Vector3>(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4), get_userdata<ST3D_Colour>(L, 5), nullptr);
            return 0;
        }

        int debug_connect(lua_State* L)
        {
            debug.connect(lua_tostring(L, 2));
            return 0;
        }

        int debug_createconsole(lua_State* L)
        {
            debug.createConsole();
            return 0;
        }

        int debug_disconnect(lua_State* L)
        {
            debug.disconnect();
            return 0;
        }

        int debug_getkeystate(lua_State* L)
        {
            lua_pushboolean(L, debug.getKeyState(lua_tostring(L, 2)));
            return 1;
        }

        int debug_index(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);
            if (key == "circle")
            {
                lua_pushcfunction(L, debug_circle);
                return 1;
            }
            else if (key == "commandLine")
            {
                lua_pushstring(L, debug.getCommandLine().c_str());
                return 1;
            }
            else if (key == "connect")
            {
                lua_pushcfunction(L, debug_connect);
                return 1;
            }
            else if (key == "createConsole")
            {
                lua_pushcfunction(L, debug_createconsole);
                return 1;
            }
            else if (key == "debugDraw")
            {
                lua_pushboolean(L, debug.getDebugDraw());
                return 1;
            }
            else if (key == "disconnect")
            {
                lua_pushcfunction(L, debug_disconnect);
                return 1;
            }
            else if (key == "getKeyState")
            {
                lua_pushcfunction(L, debug_getkeystate);
                return 1;
            }
            return 0;
        }

        int debug_newindex(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);
            if (key == "debugDraw")
            {
                debug.setDebugDraw(lua_toboolean(L, 3));
                return 0;
            }
            return 0;
        }
    }

    std::string Debug::getCommandLine() const
    {
        std::string commandLine(GetCommandLineA());

        std::cmatch results;
        std::regex rx("\/mod \".+\"");
        std::regex_search(commandLine.c_str(), results, rx);

        if (results.empty())
        {
            return "";
        }

        std::string thing = results[0];
        
        std::size_t firstPos = thing.find_first_of("\"");
        std::size_t endPos = thing.find_last_of("\"");
        std::string mod = thing.substr(firstPos + 1, endPos - firstPos - 1);

        return "mods/" + mod + "/";
    }

    bool Debug::getDebugDraw()
    {
        return GetMemVariable<int>(Address_DebugDraw) != 0;
    }

    void Debug::setDebugDraw(bool value)
    {
        SetMemVariable<int>(value, Address_DebugDraw);
    }

    void Debug::createConsole()
    {
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
    }

    bool Debug::getKeyState(const std::string& key)
    {
        return 0 != GetAsyncKeyState(VkKeyScan(key[0]));
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

    void Debug::circle(const Vector3& centre, float radius, int thickness, ST3D_Colour& colour, void* material)
    {
        types::ST3D_GraphicsEngine* engine = types::getGraphicsEngine();

        types::ST3D_Database* globaldb = engine->m_global_db;

        void* t = (globaldb->*memory_function<void* (types::ST3D_Database::*)(const char*, int)>(0x00620750))
            ("default", 2);

        types::ST3D_Camera* camera = types::getCurrentCamera();
        if (camera)
        {
            (camera->*memory_function<void (types::ST3D_Camera::*)(const Vector3&, float, int, ST3D_Colour&, void*)>(0x00619e40))
                (centre, radius, thickness, colour, t);
        }
    }

    void Debug::connect(const std::string& ip)
    {
        DebuggerConnection::getInstance().connect(ip);
    }

    void Debug::disconnect()
    {
        DebuggerConnection::getInstance().disconnect();
    }

    Vector3 Debug::testCursor()
    {
        using namespace types;
        ST3D_Device* device = getGraphicsEngine()->m_device[0];
        if( device )
        {
            if (device->m_cursor_sprite)
            {
                ST3D_AnimationChannel* channel = device->m_cursor_sprite->m_animation_channel_list.head_->next_->value_;
                if (channel)
                {
                    AnimationChannel<Vector2>* vChannel = static_cast<AnimationChannel<Vector2>*>(channel);
                    Vector2& v = vChannel->m_keyframe_data[channel->m_current_keyframe];
                    return Vector3( v.x, v.y, 0 );
                }
            }
        }
        return Vector3();
    }

    void debug_register(lua_State* L)
    {
        lua_newtable(L);
        create_metatable(L,
            {
                { "__index", debug_index },
                { "__newindex", debug_newindex },
            });
        lua_setglobal(L, "Debug");
    }
}