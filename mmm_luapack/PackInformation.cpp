#include "Externals.h"
#include "PackInformation.h"

namespace mmm
{
	namespace luapack
	{
		const std::wstring&
		PackInformation::getTitle( ) const
		{
			return title_;
		}

		const std::wstring&
		PackInformation::getAuthor( ) const
		{
			return author_;
		}

		void 
		PackInformation::setTitle( const std::wstring& title )
		{
			title_ = title;
		}

		void 
		PackInformation::setAuthor( const std::wstring& author )
		{
			author_ = author;
		}
	}
}
