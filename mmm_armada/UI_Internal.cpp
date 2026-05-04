#include "UI_Internal.h"
#include "Game_Internal.h"
#include "Team_Internal.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        const std::size_t Address_OverlayText    = 0x00764488;
        const std::size_t Address_MapRadar       = 0x00763810;
        const std::size_t Address_AddMessage     = 0x005061e0;
        const std::size_t Address_RemoveMessage  = 0x00506460;
        const std::size_t Address_FadeMessage    = 0x00506400;
        const std::size_t Address_AddMinimapMark = 0x004eb6e0;
        std::vector<UIMessage> uiMessages;

        UI ui;

        int ui_add_message(lua_State* L)
        {
            lua_pushnumber(L, ui.addMessage(lua_tostring(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4), static_cast<eJustify>(lua_tonumber(L, 5)), get_userdata<ST3D_Colour>(L, 6), lua_toboolean(L, 7), lua_tonumber(L, 8)));
            return 1;
        }

        int ui_add_minimap_mark(lua_State* L)
        {
            ui.addMinimapMark(get_userdata<Vector3>(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4), get_userdata<ST3D_Colour>(L, 5));
            return 0;
        }

        int ui_show_trades_to(lua_State* L)
        {
            ui.showTradesTo(get_userdata<std::shared_ptr<Team>>(L, 2));
            return 0;
        }

        int ui_add_title(lua_State* L)
        {
            lua_pushnumber(L, ui.addTitle(lua_tostring(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4), lua_tonumber(L, 5), lua_toboolean(L, 6)));
            return 1;
        }

        int ui_add_subtitle(lua_State* L)
        {
            lua_pushnumber(L, ui.addSubtitle(lua_tostring(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4), lua_tonumber(L, 5), lua_toboolean(L, 6)));
            return 1;
        }

        int ui_index(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);
            if (key == "addMessage")
            {
                lua_pushcfunction(L, ui_add_message);
                return 1;
            }
            else if (key == "addMinimapMark")
            {
                lua_pushcfunction(L, ui_add_minimap_mark);
                return 1;
            }
            else if (key == "showTradesTo")
            {
                lua_pushcfunction(L, ui_show_trades_to);
                return 1;
            }
            else if (key == "addTitle")
            {
                lua_pushcfunction(L, ui_add_title);
                return 1;
            }
            else if (key == "addSubtitle")
            {
                lua_pushcfunction(L, ui_add_subtitle);
                return 1;
            }
            else if (key == "teamText")
            {
                lua_pushstring(L, ui.getTeamText().c_str());
                return 1;
            }
            return 0;
        }

        int ui_newindex(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);
            if (key == "teamText")
            {
                ui.setTeamText(lua_tostring(L, 3));
                return 0;
            }
            return 0;
        }
    }

    int UI::addMessage(const std::string& text, int x, int y, mmm::eJustify justify, const mmm::ST3D_Colour &colour, bool fade, float displayTime)
    {
        OverlayText& overlay = GetMemVariable<OverlayText>(Address_OverlayText);
        int id = (overlay.*memory_function< int (OverlayText::*)(int, int, eJustify, const char*, const ST3D_Colour&, bool, MetaFont*) >(Address_AddMessage))
                (x, y, justify, text.c_str( ), colour, fade, 0);

        UIMessage message;
        message.type = MessageType_UI;
        message.id = id;
        message.fade = fade;
        message.startTime = Game().getTime();
        message.displayTime = displayTime;

        uiMessages.push_back(message);
        return id;
    }

    int UI::addTitle(const std::string& str, int x, int y, float time, bool fade)
    {
        int id = getScriptInterface()->ShowTitle(x, y, str.c_str(), fade);
        UIMessage message;
        message.type = MessageType_Title;
        message.startTime = Game().getTime();
        message.id = id;
        message.displayTime = time;
        message.fade = fade;
        uiMessages.push_back(message);
        return id;
    }

    int UI::addSubtitle(const std::string& str, int x, int y, float time, bool fade)
    {
        int id = getScriptInterface()->ShowSubtitle(x, y, str.c_str(), fade);
        UIMessage message;
        message.type = MessageType_Subtitle;
        message.startTime = Game().getTime();
        message.id = id;
        message.displayTime = time;
        message.fade = fade;
        uiMessages.push_back(message);
        return id;
    }

    void UI::removeMessage(const UIMessage& message)
    {
        switch(message.type)
        {
        case MessageType_UI:
            {
                OverlayText& text = GetMemVariable< OverlayText >(Address_OverlayText);
                (text.*memory_function<void (OverlayText::*)(int)>(Address_RemoveMessage))
                    (message.id);
            }
        case MessageType_Title:
            {
                getScriptInterface()->RemoveTitle(message.id, false);
                break;
            }
        case MessageType_Subtitle:
            {
                getScriptInterface()->RemoveSubtitle(message.id, false);
                break;
            }
        }
    }

    void UI::removeMessage(int id)
    {
        //only for ui messages
        OverlayText& text = GetMemVariable<OverlayText>(Address_OverlayText);
        (text.*memory_function<void (OverlayText::*)(int)>(Address_RemoveMessage))
            (id);
    }

    void UI::fadeMessage(const UIMessage& message)
    {
        switch(message.type)
        {
        case MessageType_UI:
            {
                OverlayText& text = GetMemVariable<OverlayText>(Address_OverlayText);
                (text.*memory_function<void (OverlayText::*)(int)>(Address_FadeMessage))
                    (message.id);
                break;
            }
        case MessageType_Title:
            {
                getScriptInterface()->RemoveTitle(message.id, true);
                break;
            }
        case MessageType_Subtitle:
            {
                getScriptInterface()->RemoveSubtitle(message.id, true);
                break;
            }
        }
    }

    void UI::addMinimapMark(const Vector3& pos, int radius, float shrinkRate, const ST3D_Colour& color)
    {
        MapRadar* radar = memory_function<MapRadar*>(Address_MapRadar);

        typedef void (MapRadar::*Function)(const MessageMark&);
        Function f = memory_function<Function>(Address_AddMinimapMark);

        MessageMark mark;
        memset(&mark, 0, sizeof(mark));
        mark.m_location = pos;

        mark.m_color = color;

        mark.m_radius = mark.m_maxRadius = radius;
        mark.m_shrinkRate = shrinkRate;

        (radar->*f)(mark);
    }

    void UI::update()
    {
        float currentTime = Game().getTime();
        //Check for removal of things.
        std::size_t i = 0;
        while(i < uiMessages.size())
        {
            if (currentTime - uiMessages[i].startTime >= uiMessages[i].displayTime)
            {
                if (uiMessages[i].fade)
                {
                    UI::fadeMessage(uiMessages[i]);
                }
                else
                {
                    UI::removeMessage(uiMessages[i]);
                }

                uiMessages.erase(uiMessages.begin() + i);
            }
            else
            {
                ++i;
            }
        }
    }

    void UI::showTradesTo(const std::shared_ptr<Team>& player)
    {
        getScriptInterface()->ShowTradesTo(player->getNumber());
    }

    const std::string UI::getTeamText() const
    {
        char* teamText = reinterpret_cast<char*>(0x00738df8);
        if(teamText)
        {
            return std::string(teamText);
        }
        return std::string();
    }

    void UI::setTeamText(const std::string& text)
    {
        getScriptInterface()->SetTeamText(const_cast<char*>(text.c_str())); 
    }

    void ui_register(lua_State* L)
    {
        lua_newtable(L);
        create_enum(L, "Justify",
            {
                { "TopLeft", JUSTIFY_TOP_LEFT },
                { "TopRight", JUSTIFY_TOP_RIGHT },
                { "TopCenter", JUSTIFY_TOP_CENTER },
                { "BottomLeft", JUSTIFY_BOTTOM_LEFT },
                { "BottomRight", JUSTIFY_BOTTOM_RIGHT },
                { "BottomCenter", JUSTIFY_BOTTOM_CENTER },
                { "CenterLeft", JUSTIFY_CENTER_LEFT },
                { "CenterRight", JUSTIFY_CENTER_RIGHT },
                { "Center", JUSTIFY_CENTER },
                { "TopLeftByLine", JUSTIFY_TOP_LEFT_BY_LINE },
                { "TopRightByLine", JUSTIFY_TOP_RIGHT_BY_LINE },
                { "TopCenterByLine", JUSTIFY_TOP_CENTER_BY_LINE },
                { "BottomLeftByLine", JUSTIFY_BOTTOM_LEFT_BY_LINE },
                { "BottomRightByLine", JUSTIFY_BOTTOM_RIGHT_BY_LINE },
                { "BottomCenterByLine", JUSTIFY_BOTTOM_CENTER_BY_LINE },
                { "CenterLeftByLine", JUSTIFY_CENTER_LEFT_BY_LINE },
                { "CenterRightByLine", JUSTIFY_CENTER_RIGHT_BY_LINE },
                { "CenterByLine", JUSTIFY_CENTER_BY_LINE }
            });
        create_metatable(L,
            {
                { "__index", ui_index },
                { "__newindex", ui_newindex }
            });
        lua_setglobal(L, "UI");
    }
}

