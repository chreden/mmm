#pragma once

namespace mmm
{
	class StringAdapter
	{
	public:
		operator std::string() const;
		StringAdapter& operator=( const std::string& value );
	private:
		char	_padding_[4];
		char*	ptr_;
		char	_morepadding_[8];

		static const std::size_t Address_Assign = 0x00672c6a;
	};
}
