#include "Load_Internal.h"
#include "Type_Craft.h"

#include "GameObject_Internal.h"
#include "Craft_Internal.h"
#include "Entities_Internal.h"

namespace mmm
{
	Load::Load( )
		: position_( 0 )
	{
		memset( buffer_, 0, sizeof(buffer_) );
	}

	void 
	Load::doLoad( )
	{
		memset( buffer_, 0, sizeof(buffer_) );

		std::vector< EntityPtr > objects;

		Entities::find( objects, isLoadOdf, 0 );

		loadHolders( objects );
		loadMappers( objects );

	}

	void
	Load::loadHolders( const std::vector< EntityPtr >& objects )
	{
		for( std::size_t i = 0; i < objects.size(); ++i )
		{
			CraftPtr craft = boost::static_pointer_cast<Craft>( objects[i] );
			if( craft->getOdf( ) == HolderName )
			{
				const std::string name = craft->getName();
				if( name.size( ) > 2 )
				{
					char packetIndex = name[ 0 ] - 1;
					char numberOfBytes = name[ 1 ];

					int offset = packetIndex * BytesPerPacket;

					for( int b = 0; b < numberOfBytes; ++b )
					{
						buffer_[ offset + b ] = name[ 2 + b ];
					}
				}
			}
		}
	}

	void 
	Load::loadMappers( const std::vector< EntityPtr >& objects )
	{
		for( std::size_t i = 0; i < objects.size(); ++i )
		{
			CraftPtr craft = boost::static_pointer_cast<Craft>( objects[i] );
			if( craft->getOdf() == MapperName )
			{
				const std::string name = craft->getName();
				if( name.size( ) > 2 )
				{
					char packetIndex = name[ 0 ] - 1;
					char numberOfBytes = name[ 1 ];

					int offset = packetIndex * BytesPerPacket;

					for( int b = 0; b < numberOfBytes; ++b )
					{
						if( name[ 2 + b ] == IsZeroChar )
						{
							buffer_[ offset + b ] = 0;
						}
					}
				}
			}
		}
	}

	int 
	Load::getLength( )
	{
		return position_;
	}

	void
	Load::setRead( int position )
	{
		position_ = position;
	}

	bool
	Load::isLoadOdf( EntityPtr ent, void* arguments )
	{
		if( types::isGameObject( ent->getEntity() ) )
		{
			const std::string odf = 
				boost::static_pointer_cast<GameObject>( ent )->getOdf();
			return odf == HolderName || 
					odf == MapperName;
		}
		return false;
	}
}

