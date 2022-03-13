#pragma once

#include "TerrainObjectClass_Internal.h"

namespace mmm
{
	namespace types
	{
		struct ScrapClass;
	}

	class ScrapClass
		: public TerrainObjectClass
	{
	public:
		explicit ScrapClass( types::ScrapClass* obj );
			
		float	 getRotationSpeed( ) const;
		void	 setRotationSpeed( float value );
	private:
		types::ScrapClass* getScrapClass() const;
	};

	void scrapclass_register( lua_State* state );
}
