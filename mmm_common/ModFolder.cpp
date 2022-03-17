#include "ModFolder.h"
#include <Shlobj.h>
#include <fstream>
#include "mmm_common.h"

namespace mmm
{
	namespace common
	{
		namespace
		{
			//Get the Appdata path. A slash is not appended to the path as this is
			//done later.
			std::string 
			getAppdataPath( )
			{
				char appdataPathBuffer[MAX_PATH];
				SHGetFolderPathA( 0, CSIDL_APPDATA, nullptr, 0, appdataPathBuffer);
				return std::string(appdataPathBuffer) + "/Star Trek Armada II Fleet Operations";
			}

			std::string 
			getModName( )
			{
				std::string commandLine( GetCommandLineA() );

				std::cmatch results;
				std::regex rx( "/mod \".+\"" );
				std::regex_search( commandLine.c_str(), results, rx );

				if( results.empty( ) )
				{
					return "";
				}

				std::string thing = results[0];
				std::size_t firstPos = thing.find_first_of( "\"" );
				std::size_t endPos = thing.find_last_of( "\"" );
				return thing.substr( firstPos + 1, endPos - firstPos - 1 );
			}
		 
			std::string
			getParentMod( std::ifstream& modIniFile ) 
			{
				//If we don't even have a valid ini file then we just
				//return an empty string.
				if( !modIniFile )
				{
					return std::string();
				}

				modIniFile.seekg( 0, std::ios::end );
				std::vector<char> modIniFileBuffer( modIniFile.tellg() );
				modIniFile.seekg( 0, std::ios::beg );
				modIniFile.read( &modIniFileBuffer[0], modIniFileBuffer.size() );
				std::string modIniFileString( modIniFileBuffer.begin(), modIniFileBuffer.end() );
				
			
				//Search for the parent mod in the file.
				std::cmatch results;
				std::regex rx( "ParentMod=(.*)" );
				std::regex_search( modIniFileString.c_str(), results, rx );

				if( results.empty( ) )
				{
					return std::string();
				}

				OutputDebugStringA( results[1].str().c_str() );
				return results[1];
			}

			void
			getModTree( std::vector<std::string>& modTree )
			{
				const std::string appdata = getAppdataPath();
				std::string currentMod = getModName();

				while ( !currentMod.empty() )
				{
					std::ifstream modIniFile( appdata + "/mods/" + currentMod + "/info.ini" );
					if( !modIniFile )
					{
						modIniFile.open( "mods/" + currentMod + "/info.ini" );
					}

					std::string parentMod = getParentMod( modIniFile );
					if( !parentMod.empty() )
					{
						modTree.push_back( parentMod );
					}
					currentMod = parentMod;
				}
			}
		}

		ModFolder::ModFolder( )
		{
			//Get the app data path where some things may be stored.
			const std::string appdata = getAppdataPath();

			//Extra options if we are running in fleet operations.
			if(common::fleetops_present())
			{
				std::string mod = getModName();
				if( !mod.empty() )
				{
					possiblePaths_.push_back( appdata + "/mods/" + mod + "/missions/" );
					possiblePaths_.push_back( "mods/" + mod + "/missions/" );
			
					//Now need to parse the mod tree.
					std::vector<std::string> modTree;
					getModTree( modTree );

					const std::size_t Count = modTree.size();
					for( std::size_t i = 0; i < Count; ++i )
					{
						std::string parentMod = modTree[i];
						possiblePaths_.push_back( appdata + "/mods/" + parentMod + "/missions/" );
						possiblePaths_.push_back( "mods/" + parentMod + "/missions/" );
					}
				}
				possiblePaths_.push_back( appdata + "/missions/" );
			}

			//Just try the program folder/missions as we've failed to find
			//the file elsewhere.
			possiblePaths_.push_back( "missions/" );
		
			//The general structure - the first node is the first one we'll try, then
			//its children.
			//Appdata / Mod / Missions	[FLEETOPS]
			//Program / Mod / Missions	[FLEETOPS]
			//[Repeat Begin]
			//Appdata / Parent / Missions	[FLEETOPS]
			//Program / Parent / Missions	[FLEETOPS]
			//[Repeat End]
			//Appdata / Missions			[FLEETOPS]
			//Program / Missions			[FLEETOPS] [STOCK]
		}

		bool
		ModFolder::getFile( const std::string& filename, std::string& out ) const
		{
			const std::size_t Count = possiblePaths_.size();
			for( std::size_t i = 0; i < Count; ++i )
			{
				std::string path = possiblePaths_[i] + filename;
				std::ifstream luaFile( path );
				if( luaFile )
				{
					out = path;
					return true;
				}
			}
			return false;
		}
	}
}
