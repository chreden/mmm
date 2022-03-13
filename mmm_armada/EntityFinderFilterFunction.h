#include "EntityFinderFilter.h"

namespace mmm
{
	class EntityFinderFilterFunction : public EntityFinderFilter
	{
	public:
		explicit EntityFinderFilterFunction( luabind::object function );
		virtual ~EntityFinderFilterFunction();
		virtual bool call( EntityPtr entity );
	private:
		luabind::object function_;
	};
}
