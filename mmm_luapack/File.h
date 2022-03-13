#ifndef _MMM_LUAPACK_FILE_H_INCLUDED
#define _MMM_LUAPACK_FILE_H_INCLUDED

#ifndef _MMM_LUAPACK_NODE_H_INCLUDED
	#include "Node.h"
#endif

namespace mmm
{
	namespace luapack
	{
		class File;
		typedef std::shared_ptr<File> FilePtr;

		class File
			: public Node
		{
		public:
			virtual Type getType( ) const;
			
			int			getFileSize() const;
			const char*	getFileData() const;

			void		setFileData( const char* data, int size );

			static FilePtr Create( const std::string& name );
		private:
			File( const std::string& name );
			virtual ~File( );

			std::vector<char> fileData_;
		};
	}
}

#endif
