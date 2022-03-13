#pragma once

namespace mmm
{
	namespace types { struct Queue; }

	class Queue
	{
	public:
		int				getSize() const;
		luabind::object getEntries() const;
		const Vector3	getOffset() const;
		void			remove( EntityPtr entity );
	protected:
		explicit		Queue( types::Queue* queue );
		types::Queue*	getQueue() const;
	private:
		types::Queue* queue_;
	};

	void queue_register( lua_State* state );
}
