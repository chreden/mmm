#include "UI_Internal.h"
#include "Game_Internal.h"
#include "Team_Internal.h"

namespace mmm
{
    namespace
    {
        constexpr std::size_t Address_OverlayText    = 0x00764488;
        constexpr std::size_t Address_MapRadar       = 0x00763810;
        constexpr std::size_t Address_AddMessage     = 0x005061e0;
        constexpr std::size_t Address_RemoveMessage  = 0x00506460;
        constexpr std::size_t Address_FadeMessage    = 0x00506400;
        constexpr std::size_t Address_AddMinimapMark = 0x004eb6e0;
        constexpr std::size_t Address_TeamText       = 0x00738df8;

        std::vector<UIMessage> uiMessages;
    }

    int UI::addMessage(const std::string& text, int x, int y, mmm::eJustify justify, const mmm::ST3D_Colour &colour, bool fade, float displayTime)
    {
        OverlayText& overlay = GetMemVariable<OverlayText>(Address_OverlayText);
        int id = (overlay.*memory_function<int (OverlayText::*)( int, int, eJustify, const char*,
            const ST3D_Colour&, bool, MetaFont*)>(Address_AddMessage))
                (x, y, justify, text.c_str( ), colour, fade, 0);

        UIMessage message;
        message.type = MessageType_UI;
        message.id = id;
        message.fade = fade;
        message.startTime = Game().getTime( );
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
        uiMessages.push_back( message );
        return id;
    }

    void UI::removeMessage(const UIMessage& message)
    {
        switch(message.type)
        {
        case MessageType_UI:
            {
                OverlayText& text = GetMemVariable<OverlayText>(Address_OverlayText);

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
        const float currentTime = Game().getTime();
        //Check for removal of things.
        std::size_t i = 0;
        while(i < uiMessages.size())
        {
            if(currentTime - uiMessages[i].startTime >= uiMessages[i].displayTime)
            {
                if(uiMessages[i].fade)
                {
                    UI::fadeMessage(uiMessages[i]);
                }
                else
                {
                    UI::removeMessage(uiMessages[i]);
                }

                uiMessages.erase(uiMessages.begin( ) + i);
            }
            else
            {
                ++i;
            }
        }
    }

    void UI::showTradesTo(TeamPtr player)
    {
        getScriptInterface()->ShowTradesTo(player->getNumber());
    }

    std::string UI::getTeamText() const
    {
        const char* teamText = reinterpret_cast<const char*>(Address_TeamText);
        if( teamText )
        {
            return std::string(teamText);
        }
        return std::string();
    }

    void UI::setTeamText(const std::string& text)
    {
        getScriptInterface()->SetTeamText(const_cast<char*>(text.c_str())); 
    }
}

