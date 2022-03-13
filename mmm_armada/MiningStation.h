#pragma once

#include "Producer.h"
#include "ResourceTransferInterface.h"

namespace mmm
{
	namespace types { struct MiningStation; }

	class MiningStation
		: public Producer, public ResourceTransferInterface
	{
	public:
		static MiningStationPtr create( types::Entity* entity );

		FreighterPtr buildFreighter( );

		virtual GameObjectClassPtr getClass() const;
	protected:
		explicit	   MiningStation( types::MiningStation* station );
		virtual void   allocateReplacement( luabind::detail::object_rep* object );
	private:
		types::MiningStation* getMiningStation() const;

		static const std::size_t Address_BuildFreighter = 0x004b4500;
	};

	void miningstation_register( lua_State* state );
}
