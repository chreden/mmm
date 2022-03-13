#include "FilePath.h"

#include <algorithm>
#include <sstream>

namespace mmm
{
	namespace common
	{
		namespace
		{
			std::vector<std::string>
			splitPath( const std::string& target )
			{
				std::regex regex("[^/\\\\]+");
				return std::vector<std::string>( std::sregex_token_iterator( target.begin(), target.end(), regex ),
												 std::sregex_token_iterator() );
			}
		}

		std::string
		FilePath::goTo( const std::string& path )
		{
			std::vector<std::string> workingPath( currentPath_.begin(), currentPath_.end() );

			std::vector<std::string> steps = splitPath( path );
			if( steps.empty() )
			{
				throw 0;
			}

			std::for_each( steps.begin(), steps.begin() + steps.size() - 1, 
				[&workingPath](const std::string& step)
			{
				if( step == ".." )
				{
					//Potentially going up one level - depending on what goes on this could be 
					//bad. 
					if( workingPath.empty() )
					{
						throw 0;
					}	
					//Remove the path element from the path.
					workingPath.pop_back();
				}
				else
				{
					workingPath.push_back( step );
				}
			});

			std::stringstream finalPath;
			std::for_each( workingPath.begin(), workingPath.end(),
				[&finalPath](const std::string& section)
			{
				finalPath << section << '/';
			});
			finalPath << steps.back();

			currentPath_.swap( workingPath );
			return finalPath.str();
		}
	}
}