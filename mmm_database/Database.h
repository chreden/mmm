#ifndef _MMM_MMMDATABASE_DATABASE_H
#define _MMM_MMMDATABASE_DATABASE_H

#include <string>

namespace mmm
{
	namespace db
	{
		class DatabaseSchema;

		class Database
		{
		public:
			explicit Database( DatabaseSchema* schema );
					 Database( const std::string& filename, DatabaseSchema* schema );
					 Database( );
			void	 initialise( const std::string& filename, DatabaseSchema* schema );
			void	 initialise( DatabaseSchema* schema );
		};
	}
}

#endif
