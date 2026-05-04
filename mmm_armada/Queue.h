#pragma once

namespace mmm
{
    namespace types { struct Queue; }

    class Entity;
    class Queue
    {
    public:
        int             getSize() const;
        int             getEntries(lua_State* L) const;
        Vector3         getOffset() const;
        void            remove(const std::shared_ptr<Entity>& entity);

        virtual int index(lua_State* L, const std::string& key) const;
        virtual int newindex(lua_State* L, const std::string& key);
    protected:
        explicit        Queue(types::Queue* queue);
        types::Queue*   getQueue() const;
    private:
        types::Queue* queue_;
    };

    int queue_new(lua_State* L, const std::shared_ptr<Queue>& queue);
    void queue_register(lua_State* state);
}
