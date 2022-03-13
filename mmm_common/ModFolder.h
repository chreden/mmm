#pragma once

#include <vector>
#include <string>

namespace mmm
{
	namespace common
	{
		/**
			Search for files in all the different locations that
			they can be in.
		*/
		class ModFolder
		{
		public:
			/**
				Default constructor - scans for all available mods.
			*/
			ModFolder( );
			/**
				Find the location of a file.
				@param filename The target file.
				@param out The location of the file.
				@return True if the file was found, otherwise false.
			*/
			bool getFile( const std::string& filename, std::string& out ) const;
		private:
			std::vector< std::string > possiblePaths_;
		};
	}
}