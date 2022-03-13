#include "Externals.h"
#include "Folder.h"
#include <algorithm>

namespace mmm
{
	namespace luapack
	{
		Node::Type 
		Folder::getType( ) const
		{
			return Type_Folder;
		}

		int		
		Folder::getChildCount( ) const
		{
			return static_cast<int>( children_.size() );
		}

		NodePtr 
		Folder::getChild( int index ) const
		{
			if( index >= getChildCount() )
			{
				return NodePtr();
			}
			return children_[index];
		}

		NodePtr 
		Folder::getChild( const std::string& name, Type type )
		{
			for( std::size_t i = 0; i < children_.size(); ++i )
			{
				if( children_[i]->getName() == name && 
					children_[i]->getType() == type ) 
				{
					return children_[i];
				}
			}
			return NodePtr();
		}

		bool
		Folder::addChild( NodePtr node )
		{
			for( std::size_t i = 0; i < children_.size(); ++i )
			{
				if( children_[i]->getName() == node->getName() ) 
				{
					return false;
				}
			}

			node->setParent( shared_from_this() );
			children_.push_back( node );
			return true;
		}

		bool	
		Folder::addChild( const char* name )
		{
			return addChild( Folder::Create( name )  );
		}

		FolderPtr
		Folder::Create( const std::string& name )
		{
			return FolderPtr( new Folder( name ), deleter );
		}

		Folder::Folder( const std::string& name )
			: Node( name )
		{
		}
		
		Folder::~Folder( )
		{

		}
	}
}