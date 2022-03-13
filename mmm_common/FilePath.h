#ifndef _MMM_MMMCOMMON_FILEPATH_H_INCLUDED
#define _MMM_MMMCOMMON_FILEPATH_H_INCLUDED

namespace mmm
{
	namespace common
	{
		//Manages moving around directories and the like.
		class FilePath
		{
		public:
			std::string goTo( const std::string& path );
		private:
			std::vector<std::string>	currentPath_;
		};
	}
}

#endif
