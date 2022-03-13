#pragma once

namespace mmm
{
	namespace types { struct Ordnance; }

	class OrdnanceDamage
	{
	public:
		static OrdnanceDamagePtr create( types::Ordnance* ordnance );
		
		float getTotal() const;
		Special getFlags() const;

		void setTotal( float value );
		void setFlags( Special value );
	private:
		explicit OrdnanceDamage( types::Ordnance* ordnance );

		types::Ordnance* ordnance_;
	};

	void ordnancedamage_register( lua_State* state );
}
