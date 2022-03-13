#include "Externals.h"
#include "Node.h"

namespace mmm
{
	namespace luapack
	{
		Node::Node( const std::string& name )
			: name_( name )
		{

		}

		Node::~Node( )
		{

		}

		void
		Node::deleter( const Node* node )
		{
			delete node;
		}

		Node::Type	   
		Node::getType( ) const
		{
			return Type_Node;
		}

		const std::string&
		Node::getName( ) const
		{
			return name_;
		}

		void
		Node::setName( const std::string& name )
		{
			name_ = name;
		}

		NodePtr	   
		Node::getParent( ) const
		{
			return parent_.lock();
		}
		
		void	   
		Node::setParent( NodePtr parent )
		{
			parent_ = parent;
		}
	}
}

