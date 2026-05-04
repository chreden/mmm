#pragma once

#include <string>

namespace mmm
{
    class Hook
    {
    public:
        virtual ~Hook();

        std::string id() const;
        int argument() const;
        int table() const;
        int function() const;
        void set_argument(int argument);
        template <typename ReturnType>
        void call();

        virtual int index(lua_State* L, const std::string& key) const;
        virtual int newindex(lua_State* L, const std::string& key);
    protected:
        explicit Hook(const std::string& id, int table, int function, int argument);
    private:
        std::string _id;
        int _table;
        int _function;
        int _argument;
    };

    int hook_new(lua_State* L, const std::shared_ptr<Hook>& hook);
    void hook_register(lua_State* L);
}
