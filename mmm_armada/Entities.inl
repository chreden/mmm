#pragma once

#include "ScriptInterface.h"

namespace mmm
{
    template<typename T>
    T* GetEntity(int id)
    {
		//Used if we just came through from the bit below.
#ifdef _MMM_FLEETOPS_GRC_FIX
		if (id == 0)
		{
			return 0;
		}
#endif
		//First we try to get it with the normal methods - this works for most things.
		T* ent = static_cast<T*>(reinterpret_cast<T * (*)(int)>(0x004cfff0)(id));

		//Now we try with the fleetops GRC fix
#ifdef _MMM_FLEETOPS_GRC_FIX
		if (ent != 0)
		{
			return ent;
		}

		ent = GetEntity<T>(getScriptInterface()->GetReplacementChild(id));
#endif
		//Now we just get the thing ourself - required for some things. Should add a check to make sure the 
		//entity is actually active though.
		if (ent != 0)
		{
			return ent;
		}

		EntityID entID;
		entID.m_id = id;

		if (getScriptInterface()->IsValid(id))
		{
			return static_cast<T*>(GetEntityPointerManager()->m_entity_pointer[entID.m_index].m_entity);
		}

		//Is not good enough!
		/*
		if( GetEntityPointerManager()->m_entity_pointer[entID.m_index].m_id.m_used )
		{
			return static_cast<T*>( GetEntityPointerManager()->m_entity_pointer[entID.m_index].m_entity );
		}
		*/

		//Has static so get warned about casting from ent to random.
		return ent;
    }

	template< typename T >
	T* GetEntity(EntityID id)
	{
		return GetEntity<T>(id.m_id);
	}
}