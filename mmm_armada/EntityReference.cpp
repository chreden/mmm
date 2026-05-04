#include "EntityReference.h"
#include "ScriptErrors.h"
#include "Entity_Internal.h"
#include "Type_Entity.h"

namespace mmm
{
    namespace
    {
        std::list<std::shared_ptr<EntityReference>> entityReferences;
        const std::size_t Address_GetEntity = 0x004cfff0;
    }

    std::shared_ptr<EntityReference> EntityReference::create(int id)
    {
        std::shared_ptr<EntityReference> ptr = find(id);
        if (!ptr)
        {
            ptr = std::shared_ptr<EntityReference>(new EntityReference(id));
            entityReferences.push_back(ptr);
        }
        return ptr;
    }

    std::shared_ptr<EntityReference> EntityReference::create(types::Entity* ent)
    {
        if (!ent)
        {
            return std::shared_ptr<EntityReference>();
        }
        return create(ent->m_entity_id);
    }

    EntityReference::EntityReference(int id)
        : entityID_(createEntityID(id)), state_(Active)
    {
        update();
    }

    EntityReference::EntityReference(types::Entity* ent)
        : state_(Active)
    {
        if (ent)
        {
            entityID_ = createEntityID(ent->m_entity_id);
        }
    }

    EntityReference::~EntityReference()
    {
    }

    void EntityReference::setID(int id)
    {
        callHook( EntityHook::OnReplace );
        entityID_.m_id = id;
    }

    EntityReference::State EntityReference::getState() const
    {
        return state_;
    }

    types::Entity* EntityReference::getEntity() const
    {
        if (state_ == Inactive)
        {
            return 0;
        }
        return reinterpret_cast<types::Entity*(*)(int)>(Address_GetEntity)(entityID_.m_id);
    }

    void EntityReference::update()
    {
        // Only update the reference if we are active - if we have been
        // deactivated we just stay as we are.
        if (state_ == Active)
        {
            types::Entity* ent = 
                reinterpret_cast<types::Entity*(*)(int)>(Address_GetEntity)(entityID_.m_id);

            if (0 == ent)
            {
                if(!common::fleetops_present())
                {
                    callHook( EntityHook::OnDestroy );
                    state_ = Inactive;
                }
                else
                {
                    EntityID newID = createEntityID(getScriptInterface()->GetReplacementChild(entityID_.m_id));
                    if (newID.m_id == 0)
                    {
                        callHook(EntityHook::OnDestroy);
                        state_ = Inactive;
                        return;
                    }

                    //Fine, our entity has been replaced so we will use this new ID.
                    entityID_ = newID;

                    //Inform the user via hook interface
                    callHook(EntityHook::OnReplace);
                }
            }
        }
    }

    void EntityReference::callHook(EntityHook::Type type) const
    {
        //Target entity (the entity we're managing).
        std::shared_ptr<Entity> entity = createEntityPtr(getEntity());

        //Similar to updating the monitors, we take a copy of the hooks
        //here so they can be removed during updating.
        auto hooksCopy = hooks_;
        for( auto hookIter = hooksCopy.begin(); hookIter != hooksCopy.end(); ++hookIter )
        {
            std::shared_ptr<EntityHook> hook = hookIter->second;
            if( hook && hook->getType() == type )
            {
                lua_State* _L = common::Storage::instance().mainLuaVM;
                lua_rawgeti(_L, LUA_REGISTRYINDEX, hook->table());
                if (lua_type(_L, -1) == LUA_TTABLE)
                {
                    lua_rawgeti(_L, LUA_REGISTRYINDEX, hook->function());
                    lua_pushvalue(_L, -2);
                    entity_new(_L, entity);
                    hook_new(_L, hook);
                    if (LUA_OK != lua_pcall(_L, 3, 0, 0))
                    {
                        scriptError(std::string("Error in Entity Hook (" + hook->id() + ") : ") + lua_tostring(_L, -1));
                    }
                }
                else
                {
                    lua_rawgeti(_L, LUA_REGISTRYINDEX, hook->function());
                    entity_new(_L, entity);
                    hook_new(_L, hook);
                    if (LUA_OK != lua_pcall(_L, 2, 0, 0))
                    {
                        scriptError(std::string("Error in Entity Hook (" + hook->id() + ") : ") + lua_tostring(_L, -1));
                    }
                }
            }
        }
    }

    bool EntityReference::hasHooks() const
    {
        return !hooks_.empty();
    }

    bool EntityReference::addHook(const std::string& id, EntityHook::Type type, int table, int function, int argument)
    {
        if (hooks_.find(id) != hooks_.end())
        {
            return false;
        }
        hooks_[id] = std::make_shared<EntityHook>(id, type, table, function, argument);
        return true;
    }

    bool EntityReference::unhook(const std::string& id)
    {
        auto iter = hooks_.find(id);
        if (iter == hooks_.end())
        {
            return false;
        }
        hooks_.erase(iter);
        return true;
    }

    bool EntityReference::unhook(const std::shared_ptr<Hook>& hook)
    {
        auto iter = std::find_if(hooks_.begin(), hooks_.end(),
            [&](const std::pair<std::string, std::shared_ptr<EntityHook>>& hookIter)
                {
                    return hookIter.second == hook;
                });
        if(iter == hooks_.end())
        {
            return false;
        }
        hooks_.erase(iter);
        return true;
    }

    int EntityReference::getHooks(lua_State* L) const
    {
        lua_newtable(L);
        for (const auto& hook : hooks_)
        {
            hook_new(L, hook.second);
            lua_setfield(L, -2, hook.first.c_str());
        }
        return 1;
    }

    std::shared_ptr<EntityReference> EntityReference::find(int id)
    {
        for (const auto& ent : entityReferences)
        {
            if (ent->getEntity() && ent->getEntity()->m_entity_id == id && ent->getState() == Active)
            {
                return ent;
            }
        }
        return {};
    }

    void EntityReference::updateReferences()
    {
        std::vector<std::shared_ptr<EntityReference>> toRemove;

        for (const auto& ent : entityReferences)
        {
            ent->update();
            if (ent->getState() == Inactive)
            {
                toRemove.push_back(ent);
            }
        }

        for( std::size_t i = 0; i < toRemove.size(); ++i )
        {
            entityReferences.remove( toRemove[i] );
        }
    }
}
