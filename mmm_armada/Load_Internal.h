#pragma once

namespace mmm
{
	class Load
	{
	public:
		explicit Load( );
		void				doLoad( );
		int				  getLength( );
		void			  setRead( int position );
		template<typename T>
		T read();
	private:
		static bool isLoadOdf( EntityPtr ent, void* arguments ); 
		void loadHolders( const std::vector< EntityPtr >& objects );
		void loadMappers( const std::vector< EntityPtr >& objects );
			
		//Constants. These are shared by save.
		static const unsigned char ZeroChar = '-';
		static const unsigned char IsZeroChar = '+';
		static const unsigned char IsNonZeroChar = '-';

		static const int MaxPackets = 255;
		static const int BytesPerPacket = 125;
		static const int MaxBytes = MaxPackets * BytesPerPacket;

		friend class Save;

		//Some data for loading.
		int position_;
		unsigned char buffer_[ MaxBytes ];
	};

	void load_register( lua_State* state );
}

#include "Load_Internal.inl"