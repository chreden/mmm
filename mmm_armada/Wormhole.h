#pragma once

#include "AreaEffectObject_Internal.h"

namespace mmm
{
    namespace types
    {
        struct Wormhole;
    }

    class Shipyard;
    class Wormhole final : public AreaEffectObject
    {
    public:
        static std::shared_ptr<Wormhole> create(types::Entity* entity);

        std::shared_ptr<Wormhole> getPartner() const;
        GateStatus getStatus() const;
        std::string getName() const;
        std::shared_ptr<Team> getOwner() const;

        bool getExpireOnClose() const;
        bool getDeleteOnTransport() const;

        bool setPartner(const std::shared_ptr<Entity>& other);
        void setExpireOnClose(bool value);
        void setDeleteOnTransport(bool value);
        void setName(const std::string& name);
        void setStatus(GateStatus status);
        void setOwner(const std::shared_ptr<Team>& owner);
        void setShipyard(const std::shared_ptr<Shipyard>& shipyard);
        types::Wormhole* getWormhole() const;

        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit Wormhole(types::Wormhole* wormhole);
    };

    void wormhole_register(lua_State* L);
}
