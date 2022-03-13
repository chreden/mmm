#pragma once

#include "Craft_Internal.h"

namespace mmm
{
	namespace types { struct ResearchPod; }

	class ResearchPod 
		: public Craft
	{
	public:
		static ResearchPodPtr create( types::Entity* entity );
		EntityPtr	 getStation() const;
	protected:
		explicit	 ResearchPod( types::ResearchPod* pod );
		virtual void allocateReplacement( luabind::detail::object_rep* obj );
	private:
		types::ResearchPod* getResearchPod() const;
	};

	void researchpod_register( lua_State* state );
}

