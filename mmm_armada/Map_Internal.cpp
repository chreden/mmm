#include "Map_Internal.h"
#include "Type_AI.h"
#include "MemRaider.h"
#include "Team_Internal.h"

namespace mmm
{
	namespace
	{
		const std::size_t Address_Terrain	= 0x00739590;
		const std::size_t Offset_ToRadar		= 40;
		const std::size_t Offset_SizeX		= 84;
		const std::size_t Offset_SizeZ		= 88;
		const std::size_t Offset_MaxWorld	= 92;
		const std::size_t Offset_OffsetX		= 96;
		const std::size_t Offset_OffsetZ		= 96;
		const std::size_t Address_StationPlacement = 0x00738a60;
		const std::size_t Function_StationPlacement_Init = 0x00494ac0;
		const std::size_t Address_PathPlanner = 0x00734b1c;
		//MapRadar
		const std::size_t Address_MapRadar	= 0x00763810;
		const std::size_t Address_MapRadar_Init = 0x004eade0;
		const std::size_t Address_MapRadar_Cleanup = 0x004eb240;
		const std::size_t Address_MapRadar_PostLoad = 0x004eadf0;
		//Fog
		const std::size_t Address_Fog		= 0x00738a54;
		//Terrain Geometry
		const std::size_t Address_TerrainGeometry			= 0x00772140;
		const std::size_t Function_TerrainGeometry_Cleanup   = 0x005931e0;
		const std::size_t Function_TerrainGeometry_Init		= 0x00593010;
		const std::size_t Function_TerrainGeometry_PostLoad	= 0x00593140;
		//Quadtree stuff
		const std::size_t Function_QuadTree_AddRect			= 0x00410540;

        //Visibility and the like.
        const std::size_t Function_IsShrouded = 0x00493bf0;
        const std::size_t Function_IsFogged = 0x00493ae0;
	}

	//Replication of Armada guts for easier access.
	struct Terrain
	{
		float m_min_x;
		float m_min_y;
		float m_min_z;
		float m_max_x;
		float m_max_y;
		float m_max_z;
		//static unsigned char s_load_new_terrain_size;	007395b4
		//static unsigned char s_save_new_terrain_size;	007395b5
	};

	void
	Map::updateMapSize( )
	{
		Terrain& terrain = GetMemVariable<Terrain>( Address_Terrain );

		//We have to tell the minimap that the map has changed size - it seems to just not
		//care. This does all the work that the previous memraider stuff did, but in calls, so
		//more likely to work.
		class MapRadar { };
		MapRadar* radar = reinterpret_cast<MapRadar*>( Address_MapRadar );
		(radar->*memory_function<void (MapRadar::*)()>( Address_MapRadar_Cleanup ))();
		(radar->*memory_function<void (MapRadar::*)()>( Address_MapRadar_Init ))();
		(radar->*memory_function<void (MapRadar::*)()>( Address_MapRadar_PostLoad ))();

		//We also have to update station placement - this is a bit simpler though as the init 
		//method of the global station placement object handles this perfectly
		class Station_Placement { };
		(reinterpret_cast<Station_Placement*>( Address_StationPlacement )->*
			memory_function<void (Station_Placement::*)()>(Function_StationPlacement_Init))();

		//Apparently some offsets need to be applied to make starfleet command work.
			
		memraider::MrNode quadTree = memraider::MrNode( Address_PathPlanner ).getInner().getInner(12);

		//Now I need to fix the issue with the pathfinding - I have to change the path planner to 
		//manually update the terrain bounds, becuase I can't find another way of doing it.
		quadTree.set<float>( 16, terrain.m_max_x + 450 );
		quadTree.set<float>( 20, terrain.m_max_z + 450 );
		quadTree.set<float>( 24, terrain.m_max_x );
		quadTree.set<float>( 28, terrain.m_max_z );
		quadTree.set<unsigned char>( 40, 1 );

		//Here be fixin' for quadtree. This gets rid of the problematic border which may be there if the map is growing
		//to a size bigger than it was before.
		class QuadTree { };
		QuadTree* quadTreePtr = reinterpret_cast<QuadTree*>(quadTree.getAddress());
		(quadTreePtr->*memory_function<void (QuadTree::*)()>( 0x00410bf0 ))();

		//Now we regenerate the full A* path. However we still need to find a way to completely regenerate
		//the quadtree so that it doesn't use the old borders.
		class Path_Planner { };
		Path_Planner* planner = *reinterpret_cast<Path_Planner**>(Address_PathPlanner);
		(planner->*memory_function<void (Path_Planner::*)(bool)>( 0x0040bc80 ))(true);

		//Here we call Cleanup, Init and Post Load to resize the map geometry properly. This ensures that all the proper geometry
		//is created and that the shroud is also properly added.
		class Terrain_Geometry { };
		Terrain_Geometry* geom = reinterpret_cast<Terrain_Geometry*>(Address_TerrainGeometry);
		(geom->*memory_function<void (Terrain_Geometry::*)()>(Function_TerrainGeometry_Cleanup))();
		(geom->*memory_function<void (Terrain_Geometry::*)(const ST3D_Colour&)>(Function_TerrainGeometry_Init))(ST3D_Colour(1,0,0));
		(geom->*memory_function<void (Terrain_Geometry::*)()>(Function_TerrainGeometry_PostLoad))();

		class QuadTreeCell { };
		QuadTreeCell* cell = reinterpret_cast<QuadTreeCell*>( quadTree.getInner().getAddress() );

		typedef void (QuadTree::*AddRectFn)(float, float, float, float, const int&, QuadTreeCell*, bool);
		AddRectFn addRectFunc = memory_function<AddRectFn>( Function_QuadTree_AddRect );

		(quadTreePtr->*addRectFunc)( 0.0f, 0.0f, terrain.m_max_x, 550.0f, -1, cell, false );
		(quadTreePtr->*addRectFunc)( 0.0f, 0.0f, 550.0f, terrain.m_max_z, -1, cell, false );

		//Threat map apparently also needs updating...
		//00429250
		//00428860
		types::AI* ai = *reinterpret_cast<types::AI**>( 0x00735bc4 );
			
		types::Strategic_Map* stratMap = ai->m_team->m_map;

		//(stratMap->*memory_function<void (types::Strategic_Map::*)()>( 0x00429250 ))();
		(stratMap->*memory_function<void (types::Strategic_Map::*)()>( 0x00428860 ))();
		//0001:00027860       ?Init_Maps@Strategic_Map@@AAEXXZ 00428860 f   strategic_map.obj
		//0001:00028250       ?Clean_Up@Strategic_Map@@AAEXXZ 00429250 f   strategic_map.obj
	}

	Vector3 
	Map::getMin( )
	{
		Terrain& terrain = GetMemVariable<Terrain>( Address_Terrain );
		return Vector3(terrain.m_min_x, terrain.m_min_y, terrain.m_min_z);
	}
		
	Vector3 
	Map::getMax( )
	{
		Terrain& terrain = GetMemVariable<Terrain>( Address_Terrain );
		return Vector3(terrain.m_max_x, terrain.m_max_y, terrain.m_max_z);
	}

    Map::eVisibility
    Map::getVisibility( const Vector3& position, TeamPtr player ) const
    {
        if( (*(memory_function<bool (*)(const Vector3&, unsigned long)>(Function_IsShrouded)))( position, 1 << player->getNumber()) )
        {
            return Shrouded;
        }
        else if( (*(memory_function<bool (*)(const Vector3&, unsigned long)>(Function_IsFogged)))( position, 1 << player->getNumber()) )
        {
            return Fogged;
        }
        return Visible;
    }

    luabind::object
    Map::getVisibilityEnum( ) const
    {
        if( !exploration_.is_valid() )
		{
			luabind::object globals  = luabind::globals(common::Storage::instance().mainLuaVM);
			exploration_ = globals["Map_"]["Exploration"];
		}
		return exploration_;
    }

	void 
	Map::setMin( const Vector3& vec )
	{
		Terrain& terrain = GetMemVariable<Terrain>( Address_Terrain );
		terrain.m_min_x = vec.x;
		terrain.m_min_y = vec.y;
		terrain.m_min_z = vec.z;
		updateMapSize();
	}
		
	void 
	Map::setMax( const Vector3& vec )
	{
		Terrain& terrain = GetMemVariable<Terrain>( Address_Terrain );
		terrain.m_max_x = vec.x;
		terrain.m_max_y = vec.y;
		terrain.m_max_z = vec.z;
		updateMapSize();
	}
}