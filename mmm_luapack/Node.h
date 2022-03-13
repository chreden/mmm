#ifndef _MMM_LUAPACK_NODE_H_INCLUDED
#define _MMM_LUAPACK_NODE_H_INCLUDED

namespace mmm
{
	namespace luapack
	{
		class Node;
		typedef std::shared_ptr<Node> NodePtr;
		typedef std::weak_ptr<Node> NodeView;

		class __declspec(novtable) Node
		{
		public:
			enum Type
			{
				Type_Node = 0,
				Type_File,
				Type_Folder
			};

			const std::string& getName( ) const;
			void			   setName( const std::string& name );
			virtual Type	   getType( ) const = 0;
			virtual	NodePtr	   getParent( ) const;
			virtual void	   setParent( NodePtr parent );
			virtual ~Node( );

		protected:
			static void deleter( const Node* node );
			explicit Node( const std::string& name );
		private:
			std::string				name_;
			NodeView				parent_;
		};
	}
}

#endif
