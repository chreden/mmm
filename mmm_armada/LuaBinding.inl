#pragma once

namespace mmm
{
    template <typename T>
    void create_userdata(lua_State* L, const T& value)
    {
        T* ptr = reinterpret_cast<T*>(lua_newuserdata(L, sizeof(T)));
        new(ptr) T(value);
    }

    template <typename T>
    void cleanup_userdata(lua_State* L, int index)
    {
        T* ptr = static_cast<T*>(lua_touserdata(L, index));
        ptr->~T();
    }

    template <typename T>
    T& get_userdata(lua_State* L, int index)
    {
        return *static_cast<T*>(lua_touserdata(L, index));
    }
}