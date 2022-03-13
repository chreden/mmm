#ifndef _MMM_LUAPACK_PACKINFORMATION_H_INCLUDED
#define _MMM_LUAPACK_PACKINFORMATION_H_INCLUDED

namespace mmm
{
	namespace luapack
	{
		class PackInformation
		{
		public:
			const std::wstring& getTitle( ) const;
			const std::wstring& getAuthor( ) const;
			void setTitle( const std::wstring& title );
			void setAuthor( const std::wstring& author );
		private:
			std::wstring title_;
			std::wstring author_;
		};
	}
}

#endif
