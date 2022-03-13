#pragma once

namespace mmm
{
	class EntityFinderFilter
	{
	public:
		virtual ~EntityFinderFilter( );
		virtual bool call( EntityPtr entity ) = 0;
	};
}
