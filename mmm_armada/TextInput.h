#pragma once

namespace mmm
{
    class Hook;
    class TextInputHook;
    class TextInput
    {
    public:
        bool hook(const std::string& id, int table, int function, int argument);
        bool hook(const std::string& id, int table, int function, int argument, const std::string& pattern);
        bool unhook(const std::string& id);
        bool unhook(const std::shared_ptr<Hook>& hook);
        bool getActive() const;
        std::string getPrompt() const;
        std::string getText() const;
        int getHooks(lua_State* L) const;
        void setPrompt(const std::string& prompt);
        void update();
    private:
        std::unordered_map<std::string, std::shared_ptr<TextInputHook>> hooks_;
        bool previousActive_{ false };
        std::string	previousString_;
    };

    void textinput_update();
    void textinput_register(lua_State* L);
}
