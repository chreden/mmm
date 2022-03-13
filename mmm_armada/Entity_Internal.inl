#pragma once

namespace mmm
{
	template<typename T>
	void
	entity_allocate_replacement( luabind::detail::object_rep* object, boost::shared_ptr<T> ptr )
	{
		using namespace luabind;
		using namespace luabind::detail;

		lua_State* state = common::Storage::instance().mainLuaVM;

		typedef pointer_holder<EntityPtr, T> holder_type;
		void* storage = object->allocate( sizeof( holder_type ) );
		object->m_classrep = get_class_rep<T>( state );
		object->set_instance(new (storage) holder_type( ptr, registered_class<T>::id, ptr.get()));
	}
}
