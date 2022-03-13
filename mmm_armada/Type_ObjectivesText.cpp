#include "Type_ObjectivesText.h"

namespace mmm
{
	namespace types
	{
		const std::string 
		ObjectivesText::get() const
		{
			return m_informationText;
		}

		void
		ObjectivesText::set( const std::string& text )
		{
			memset( m_informationText, 0, sizeof(m_informationText) );
			strcpy( m_informationText, text.c_str() );
		}
	}
}