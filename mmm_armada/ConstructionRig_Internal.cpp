#include "ConstructionRig_Internal.h"
#include "Type_ConstructionRig.h"
#include "MemRaider.h"

namespace mmm
{
    std::shared_ptr<ConstructionRig> ConstructionRig::create(types::Entity* entity)
    {
        return std::shared_ptr<ConstructionRig>(new ConstructionRig(static_cast<types::ConstructionRig*>(entity)));
    }

    ConstructionRig::ConstructionRig(types::ConstructionRig* rig)
        : Producer(rig)
    {

    }

    int ConstructionRig::getBeesOnboard() const
    {
        types::ConstructionRig* rig = getConstructionRig();
        return getConstructionRig()->m_numberOfBeesOnboard;
    }

    std::shared_ptr<Entity> ConstructionRig::getConstructionObject() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getConstructionRig()->m_constructionObjectID));
    }

    //Number of bees is going to have to be a class property since it affects all objects o fthis
    //type.
    void ConstructionRig::setBeesOnboard(int value)
    {
        memraider::MrNode(getConstructionRig()->m_class).set<long>(0x490, value);
    }

    types::ConstructionRig* ConstructionRig::getConstructionRig() const
    {
        return static_cast<types::ConstructionRig*>(getEntity());
    }

    int ConstructionRig::index(lua_State* L, const std::string& key) const
    {
        if (key == "constructionObject")
        {
            return entity_new(L, getConstructionObject());
        }
        return Producer::index(L, key);
    }
}
