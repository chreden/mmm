#pragma once

#include "Producer.h"
#include "ResourceTransferInterface.h"

namespace mmm
{
    namespace types { struct MiningStation; }

    class Freighter;
    class MiningStation : public Producer, public ResourceTransferInterface
    {
    public:
        static std::shared_ptr<MiningStation> create(types::Entity* entity);
        std::shared_ptr<Freighter> buildFreighter() const;
        virtual std::shared_ptr<GameObjectClass> getClass() const;

        int index(lua_State* L, const std::string& key) const override;
    protected:
        explicit  MiningStation(types::MiningStation* station);
    private:
        types::MiningStation* getMiningStation() const;

        static const std::size_t Address_BuildFreighter = 0x004b4500;
    };
}
