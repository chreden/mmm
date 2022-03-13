#ifndef _MMM_LUAPACK_FOLDER_H_INCLUDED
#define _MMM_LUAPACK_FOLDER_H_INCLUDED

#ifndef _MMM_LUAPACK_NODE_H_INCLUDED
	#include "Node.h"
#endif

namespace mmm
{
	namespace luapack
	{
		class Folder;
		typedef std::shared_ptr<Folder> FolderPtr;

		class Folder
			: public Node, public std::enable_shared_from_this<Folder>
		{
		public:
			virtual Type getType( ) const;
			
			int		getChildCount( ) const;
			NodePtr getChild( int index ) const;
			NodePtr getChild( const std::string& name, Type type );

			bool	addChild( NodePtr node );
			bool	addChild( const char* name );

			static FolderPtr Create( const std::string& name );
		private:
			Folder( const std::string& name );
			virtual ~Folder( );

			std::vector<NodePtr> children_;
		};
	}
}

#endif
