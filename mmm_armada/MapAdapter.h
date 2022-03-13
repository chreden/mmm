#pragma once

namespace mmm
{
	template < typename K, typename V >
	class MapAdapter
	{
	public:
		enum Redbl
		{
			_RED,
			_BLACK
		};

		struct Pair
		{
			K first;
			V second;
		};

		std::size_t size() const
		{
			return tree._size;
		}

		class Tree
		{
		public:
			struct Node
			{
				Node*	left;
				Node*	parent;
				Node*	right;
				Pair	value;
				Redbl	rb;
			};
			char _padding_[0x4];
			Node*		  _head;
			unsigned char _multi;
			unsigned int  _size;
		};	
		Tree tree;
	};
}

		/*
		UserDefinedType: std::_Tree<int,std::pair<int const ,AudioStream2D *>,std::map<int,AudioStream2D *,std::less<int>,std::allocator<AudioStream2D *> >::_Kfn,std::less<int>,std::allocator<AudioStream2D *> >
Enum           :   _Redbl, Type: int
Data           :     constant 0x0, Constant, Type: int, _Red
Data           :     constant 0x1, Constant, Type: int, _Black
UserDefinedType:   _Node
Data           :     this+0x0, Member, Type: struct std::_Tree<int,std::pair<int const ,AudioStream2D *>,std::map<int,AudioStream2D *,std::less<int>,std::allocator<AudioStream2D *> >::_Kfn,std::less<int>,std::allocator<AudioStream2D *> >::_Node *, _Left
Data           :     this+0x4, Member, Type: struct std::_Tree<int,std::pair<int const ,AudioStream2D *>,std::map<int,AudioStream2D *,std::less<int>,std::allocator<AudioStream2D *> >::_Kfn,std::less<int>,std::allocator<AudioStream2D *> >::_Node *, _Parent
Data           :     this+0x8, Member, Type: struct std::_Tree<int,std::pair<int const ,AudioStream2D *>,std::map<int,AudioStream2D *,std::less<int>,std::allocator<AudioStream2D *> >::_Kfn,std::less<int>,std::allocator<AudioStream2D *> >::_Node *, _Right
Data           :     this+0xC, Member, Type: struct std::pair<int const ,AudioStream2D *>, _Value

Data           :     this+0x14, Member, Type: enum std::_Tree<int,std::pair<int const ,AudioStream2D *>,std::map<int,AudioStream2D *,std::less<int>,std::allocator<AudioStream2D *> >::_Kfn,std::less<int>,std::allocator<AudioStream2D *> >::_Redbl, _Color
*/




//Data           :   this+0x0, Member, 
/*
Type: class std::_Tree
				<int,
				std::pair<int const ,AudioStream2D *>,
					std::map<int,
							 AudioStream2D *,
							 std::less<int>,
							 std::allocator<AudioStream2D *>
							 >::_Kfn,
				std::less<int>,
				std::allocator<AudioStream2D *> 
				>, _Tr
	
	*/


