#pragma once

namespace mmm
{
	class Entities
	{
	public:
		typedef bool (*FindComparator)(EntityPtr, void*);

		static EntityPtr	add( const std::string& odf, int team, const Vector3& position );
		static EntityPtr	add( const std::string& odf, TeamPtr team, const Vector3& position );
		static void			find( std::vector<EntityPtr>& ents, FindComparator comparator, void* argument );
		static bool			remove( EntityPtr entity );
		static void			getActiveEntities( std::vector<EntityPtr>& results );
	};
}
