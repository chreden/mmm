#pragma once

#include "Producer.h"

namespace mmm
{
	namespace types { struct ResearchStation; }

	class ResearchStation
		: public Producer
	{
	public:
		static ResearchStationPtr create( types::Entity* entity );
		luabind::object getPods() const;
	protected:
		explicit	 ResearchStation( types::ResearchStation* station );
		virtual void allocateReplacement( luabind::detail::object_rep* object );
	private:
		types::ResearchStation* getResearchStation() const;
	};

	void researchstation_register( lua_State* state );
}
