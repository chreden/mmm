#ifndef _MMM_MMMCOMMON_HASH_H
#define _MMM_MMMCOMMON_HASH_H

namespace mmm
{
	class Hash
	{
	public:
						Hash( unsigned int hash );
		explicit		Hash( const std::string& str );
		unsigned int	getHash( ) const;

		operator unsigned int () const;
	private:
		unsigned int hash_;
	};

	unsigned int hashString( const std::string& str );
}

#endif
