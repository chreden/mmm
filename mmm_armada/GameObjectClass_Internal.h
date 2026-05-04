#pragma once

namespace mmm
{
    namespace types
    {
        struct GameObjectClass;
    }

    class GameObjectClass
    {
    public:
        static std::shared_ptr<GameObjectClass> create(types::GameObjectClass* ptr);
        virtual ~GameObjectClass();
        std::string getLabel() const;
        std::string getUnitString() const;
        long getMaxSpecialEnergy() const;
        std::string getODF() const;
        void setUnitString(const std::string& name);
        void setMaxSpecialEnergy(long value);
        types::GameObjectClass* getClass() const;
        virtual int index(lua_State* L, const std::string& key) const;
        virtual int newindex(lua_State* L, const std::string& key);
    protected:
        explicit GameObjectClass(types::GameObjectClass* goClass);
    private:
        types::GameObjectClass* class_;
    };

    int gameobjectclass_new(lua_State* L, const std::shared_ptr<GameObjectClass>& ptr);
    void gameobjectclass_register(lua_State* state);
    std::shared_ptr<GameObjectClass> createGameObjectClassPtr(types::GameObjectClass* ptr);
}
