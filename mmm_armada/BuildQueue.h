#pragma once

#include "Producer.h"

namespace mmm
{
	//The build queue class manages adding entries
	//into a production queue (for producers only
	//really)
	class BuildQueue
	{
	public:
		static BuildQueuePtr create( ProducerPtr producer );
		//Removes all items from the build queue
		void clear( );
		//Add an item to the queue
		bool push( const std::string& odf );
		//Remove an item from the end (?) of the queue
		void pop( );
		//Complete the current item.
		void complete( );
		//See how many things are in the queue
		int getSize( ) const;
		//Get the contents of the queue (GameObjectClass table)
		luabind::object getItems() const;
		//True if there is nothing
		bool isEmpty() const;
		//Remove the element at the index
		void remove( int index );
		//Get time remaining on the current item.
		float getTimeRemaining() const;
	private:
		explicit BuildQueue( ProducerPtr producer );

		ProducerPtr producer_;
	};

	void buildqueue_register( lua_State* state );
}
