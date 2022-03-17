#pragma once

namespace mmm
{
	template<typename T>
	T* GetEntity(int id);

	template< typename T >
	T* GetEntity(EntityID id);
}

#include "Entities.inl"
