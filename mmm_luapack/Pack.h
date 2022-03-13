#ifndef _MMM_LUAPACK_PACK_H_INCLUDED
#define _MMM_LUAPACK_PACK_H_INCLUDED

#ifndef _MMM_LUAPACK_PACKINFORMATION_H_INCLUDED
	#include "PackInformation.h"
#endif

namespace mmm
{
	namespace luapack
	{
		class Pack
		{
		public:
								   Pack( );
				  PackInformation& getPackInformation();
			const PackInformation& getPackInformation() const;
			FolderPtr			   getRootNode( ) const;
			bool				   load( const std::string& filename );
			bool				   save( const std::string& filename ) const;
		private:
			PackInformation		packInformation_;
			FolderPtr			rootNode_;
		};

		FilePtr pack_getFile( const Pack& pack, const std::string& filePath );
	}
}

#endif
