#pragma once

namespace mmm
{
	namespace types
	{
		class ObjectivesText
		{
		public:
			const std::string get() const;
			void set( const std::string& str );
		private:
			char _padding_[0x84];
			char m_informationText[ 0x800 ];
			unsigned char m_textIsSet;
		};
	}
}
