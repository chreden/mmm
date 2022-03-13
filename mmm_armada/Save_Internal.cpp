#include "Save_Internal.h"
#include "Type_Craft.h"

#include "Entities_Internal.h"
#include "Craft_Internal.h"

namespace mmm
{
	Save::Save( )
		: position_( 0 )
	{
		memset( buffer_, 0, sizeof(buffer_) );
	}

	void 
	Save::deleteSaveEntities( )
	{
		std::vector<EntityPtr> objects;
			
		Entities::find( objects, Load::isLoadOdf, 0 );
			
		for( std::size_t i = 0; i < objects.size( ); ++i )
		{
			Entities::remove( objects[ i ] );
		}
	}

	void
	Save::doSave( )
	{
		//Right, we need to remove any holders or mappers in the area.
		deleteSaveEntities( );

		//Right, now that we know how the long the data is, we can write it to the 
		//packets (that we will be making).
		const int PacketsToMake = static_cast<int>( ceil( static_cast<double>( position_ ) / 
			static_cast<double>( Load::BytesPerPacket ) ) );

		int bytesToWrite = position_;

		char holderName[128];
		char mapperName[128];

		for( int i = 0; i < PacketsToMake; ++i )
		{
			int baseIndex = i * Load::BytesPerPacket;

			memset( holderName, 0, sizeof(holderName) );
			memset( mapperName, 0, sizeof(mapperName) );

			char packetIndex = i + 1;

			holderName[0] = packetIndex;
			mapperName[0] = holderName[0];

			int bytesThisPacket = std::min( Load::BytesPerPacket, bytesToWrite );

			holderName[1] = bytesThisPacket;
			mapperName[1] = holderName[1];

			for( int b = 0; b < bytesThisPacket; ++b )
			{
				char data = buffer_[ baseIndex + b ];
				holderName[ 2 + b ] = data == 0 ? Load::ZeroChar : data;
				mapperName[ 2 + b ] = data == 0 ? Load::IsZeroChar : Load::IsNonZeroChar;
			}

			//Create the new objects
			CraftPtr holder( boost::static_pointer_cast<Craft>( Entities::add( HolderName, 0, Vector3( 1900 + static_cast<float>(i) * 50, 0, 2200 ) ) ) );
			CraftPtr mapper( boost::static_pointer_cast<Craft>( Entities::add( MapperName, 0, Vector3( 1900 + static_cast<float>(i) * 50, 0, 2150 ) ) ) );

			holder->setName( holderName );
			mapper->setName( mapperName );

			holder->setInvincible( true );
			mapper->setInvincible( true );

			bytesToWrite -= bytesThisPacket;
		}
	}
	
	void
	Save::setWrite( int position )
	{
		position_ = position;
	}

	bool
	Save::write( const std::string& str )
	{
		const std::size_t SizeToWrite = str.size() + 1;
		if( position_ + SizeToWrite >= Load::MaxBytes )
		{
			return false;
		}
		memcpy( &buffer_[ position_ ], str.c_str( ), str.size() + 1 );
		position_ += str.size( ) + 1;
		return true;
	}

	bool
	Save::write( float num )
	{
		if( position_ + sizeof(float) >= Load::MaxBytes )
		{
			return false;
		}
		memcpy( &buffer_[ position_ ], &num, sizeof(float) );
		position_ += sizeof(float);
		return true;
	}

	bool
	Save::write( bool value )
	{
		if( position_ + sizeof(bool) >= Load::MaxBytes )
		{
			return false;
		}
		memcpy( &buffer_[ position_ ], &value, sizeof(bool) );
		position_ += sizeof(bool);
		return true;
	}

	int
	Save::getLength( )
	{
		return position_;
	}
}
