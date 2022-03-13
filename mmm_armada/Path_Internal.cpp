#include "Path_Internal.h"
#include "WormholeType.h"
#include "PathType.h"

namespace mmm
{
	namespace
	{
        using namespace types;

		// Address of the static AiPath::find function.
        const std::size_t Address_Find			= 0x0044fb10;

		const std::size_t Address_SetPointCount	= 0x0044f990;

		const std::size_t Address_SetPoints		= 0x0044f990;
        // Address of the AiPath set label function.
		const std::size_t Address_SetLabel		= 0x0044f920;
        // Address of the AiPath class' default constructor
        const std::size_t Address_PathDefaultConstructor = 0x0044ef40;

        // Static AiPath find function.
        auto path_find = memory_function<AiPath* (*)(const char*)>( Address_Find );
        // The AiPath set label function.
        auto path_set_label = memory_function<void (AiPath::*)(const char*)>( Address_SetLabel );
        // Default constructor for the AiPath class.
        auto path_default_constructor = memory_function<void (AiPath::*)()>( Address_PathDefaultConstructor );
	}

	types::AiPath* 
	Path::get( const std::string& name )
	{
        return path_find( name.c_str() );
	}

    Path::Path( )
        : path_( armada_new<types::AiPath>( ) )
    {
        (path_->*path_default_constructor)( );
    }

	Path::Path( const std::string& name )
		: path_( nullptr )
	{
		path_ = get( name );
		if( nullptr == path_ )
		{
            auto path = mmm::armada_new<types::AiPath>( );

            (path->*path_default_constructor)();

			(path->*memory_function< void (types::AiPath::*)( int ) >( Address_SetPoints ))
				( 0 );

            (path->*path_set_label)( name.c_str() );

			path_ = path;
		}
	}

	Path::Path( types::AiPath* path )
		: path_( path )
	{

	}

	int 
	Path::count( ) const
	{
		return path_->pointCount;
	}

	const std::string
	Path::getName() const
	{
		if( path_->m_pLabel )
		{
			return path_->m_pLabel;
		}
		return ""; 
	}

	const Vector3
	Path::getPoint( int index ) const
	{
		if( index > count() )
		{
			return Vector3();
		}
		return path_->points[ index - 1 ];
	}

	bool
	Path::setPoint( int index, const Vector3& point )
	{
		if( index <= 0 || index > count() )
		{
			return false;
		}
		path_->points[ index - 1 ] = point;			
		return true;
	}

	void 
	Path::appendPoint( const Vector3& point )
	{
		setSize( count() + 1 );
		path_->points[ path_->pointCount - 1 ] = point;
	}

	void
	Path::prependPoint( const Vector3& point )
	{
		setSize( count() + 1 );
		for( int i = count() - 1; i >= 1; --i )
		{
			path_->points[ i ] = path_->points[ i - 1 ];
		}
		path_->points[ 0 ] = point;			
	}

	void
	Path::setSize( int size )
	{
		(path_->*memory_function< void (types::AiPath::*)( int ) >( Address_SetPointCount ))
			( size );
	}

	luabind::object   
	Path::getPoints() const
	{
		luabind::object points = luabind::newtable( common::Storage::instance().mainLuaVM );
		const int Count = count();
		for( int i = 1; i <= Count; ++i )
		{
			points[i] = path_->points[i-1];
		}
		return points;
	}

	void			  
	Path::remove( int index )
	{
		if( index <= 0 || index > count() )
		{
			return;
		}

		std::vector<Vector3> existingPoints( count() );
		memcpy( &existingPoints[0],
				path_->points,
				path_->pointCount );

		(path_->*memory_function< void (types::AiPath::*)( int ) >( Address_SetPoints ))
			( path_->pointCount - 1 );

		if( path_->pointCount )
		{
			existingPoints.erase( existingPoints.begin() + index - 1 );
			memcpy( path_->points,
					&existingPoints[0],
					path_->pointCount );
		}
	}

	types::AiPath* 
	Path::getPath() const
	{
		return path_;
	}
}