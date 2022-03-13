#pragma once

#include "Load_Internal.h"

namespace mmm
{
	class Save
	{
	public:
		Save( );
		void doSave( );
		void setWrite( int position );
		bool write( const std::string& str );
		bool write( float num );
		bool write( bool value );
		int getLength( );
	private:
		void deleteSaveEntities( );
		int position_;
		unsigned char buffer_[Load::MaxBytes];
	};

	void save_register( lua_State* state );
}
