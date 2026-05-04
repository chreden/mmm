#pragma once

#include "Craft_Internal.h"

namespace mmm
{
    namespace types
    {
        class Freighter;
    } 

    class Freighter : public Craft
    {
    public:
        static std::shared_ptr<Freighter> create(types::Entity* entity);
        eResource getResourceCarried() const;
        float getSpaceRemaining() const;
        float getAmountCarried() const;
        bool getDroppingOff() const;
        float getMaxAmount(eResource resource) const;
        float getMaxAmountCurrent() const;
        std::shared_ptr<Entity> getResourceSource() const;
        std::shared_ptr<Entity> getStation() const;
        void setResourceCarried(eResource resource);
        void setAmountCarried(float amount);

        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit Freighter(types::Freighter* freighter);
    private:
        types::Freighter* getFreighter() const;
    };
}
