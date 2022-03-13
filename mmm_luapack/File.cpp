#include "Externals.h"
#include "File.h"

namespace mmm
{
	namespace luapack
	{
		Node::Type 
		File::getType( ) const
		{
			return Type_File;
		}

		int
		File::getFileSize( ) const
		{
			return static_cast<int>( fileData_.size() ) - 1;
		}

		const char*
		File::getFileData( ) const
		{
			if( getFileSize() == 0 )
			{
				return nullptr;
			}
			return &fileData_[0];
		}

		void		
		File::setFileData( const char* data, int size )
		{
			if( nullptr == data )
			{
				return;
			}

			fileData_.resize( size + 1 );
			if( 0 != size )
			{
				memcpy( &fileData_[0], data, size );
			}
		}

		FilePtr
		File::Create( const std::string& name )
		{
			return FilePtr( new File( name ), deleter );
		}

		File::File( const std::string& name )
			: Node( name )
		{
			//Some things here???
		}
		
		File::~File( )
		{

		}
	}
}