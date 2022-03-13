#include "Externals.h"
#include "Folder.h"
#include "File.h"
#include "Pack.h"

#include <regex>
#include <iostream>

namespace mmm
{
	namespace luapack
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

		PackInformation&
		Pack::getPackInformation( )
		{
			return packInformation_;
		}

		const PackInformation&
		Pack::getPackInformation( ) const
		{
			return packInformation_;
		}

		FolderPtr
		Pack::getRootNode( ) const
		{
			return rootNode_;
		}

		namespace
		{
			std::string
			getNodeName( NodePtr node )
			{
				std::string finalName = node->getName();
				if( node->getParent() )
				{
					finalName = getNodeName( node->getParent() ) + finalName;
				}
				if( node->getType() == Node::Type_Folder &&
					node->getParent() )
				{
					finalName += '/';
				}
				return finalName;
			}

			void
			saveNode( NodePtr node, unzFile file )
			{
				zip_fileinfo dirInfo;
				memset( &dirInfo, 0, sizeof(dirInfo) );
				if( node->getParent() )
				{
					zipOpenNewFileInZip( file,
										 getNodeName(node).c_str(),
										 &dirInfo,
										 0, 0, 0, 0, 0, Z_DEFLATED, 5 );
				}

				if( node->getType() == Node::Type_Folder )
				{
					FolderPtr folder = 
						std::static_pointer_cast<Folder>( node );
			
					if( node->getParent() )
					{
						zipCloseFileInZip(file);
					}

					for( std::size_t i = 0; i < folder->getChildCount(); ++i )
					{
						saveNode( folder->getChild(i), file );
					}
				}
				else
				{
					FilePtr fileNode = std::static_pointer_cast<File>( node );
					zipWriteInFileInZip( file, fileNode->getFileData(), fileNode->getFileSize() );
					zipCloseFileInZip(file);
				}
			}
		}

		bool
		Pack::save( const std::string& filename ) const
		{
			//Save the file in the zip format instead of LF. :(
			unzFile file = zipOpen( filename.c_str(), 0 );
			if( 0 == file )
			{
				return false;
			}

			saveNode( rootNode_, file );

			zipClose( file, 0 );

			return true;
		}

		Pack::Pack( )
		{
			//Initialise root node to be a folder so we can actually add other things
			//as children. Doesn't need to have a name because it is just so we can 
			//add things.
			rootNode_ = Folder::Create( "" );
		}

		bool
		Pack::load( const std::string& filename )
		{
			//New version of loading that loads from a zip file instead
			//of loading from a lardfish file.
			unzFile file = unzOpen( filename.c_str() );
			if( 0 == file )
			{
				return false;
			}

			unz_global_info info;
			unzGetGlobalInfo( file, &info );

			FolderPtr rootNode = Folder::Create("");

			for( long i = 0; i < info.number_entry; ++i )
			{
				unz_file_info fileInfo;
				char zipfile_filename[256];
				//Do some stuff with the file.
				if( UNZ_OK != unzGetCurrentFileInfo( file,
									   &fileInfo,
									   zipfile_filename,
									   sizeof(zipfile_filename),
									   0,
									   0,
									   0,
									   0 ) )
				{
					continue;
				}

				std::string fn(zipfile_filename);
				
				std::vector<std::string> path = splitPath( fn );
				FolderPtr parentNode = rootNode;
				bool errorFinding = false;
				for( std::size_t level = 0; 
						level < path.size() - 1;
						++level )
				{
					errorFinding = true;
					FolderPtr potentialParent = 
						std::static_pointer_cast<Folder>(parentNode->getChild(path[level], Node::Type_Folder));
					if( potentialParent )
					{
						parentNode = potentialParent;
						errorFinding = false;
					}
				}

				if( !errorFinding )
				{
					if( fn.back() == '/' )
					{
						parentNode->addChild( Folder::Create(path.back().c_str()) );
					}
					else
					{
						FilePtr newFile = File::Create(path.back().c_str());
						std::size_t fileSize = fileInfo.uncompressed_size;
						std::vector<char> buffer( fileSize + 1, 0 );
						if( fileSize ) 
						{
							unzOpenCurrentFile( file );
							unzReadCurrentFile( file, &buffer[0], fileSize );
							unzCloseCurrentFile( file );
							newFile->setFileData( &buffer[0], fileSize );
						}
						parentNode->addChild( newFile );
					}
				}

				unzGoToNextFile(file);
			}
			
			unzClose( file );
			rootNode_ = rootNode;
			return true;
		}

		FilePtr 
		pack_getFile( const Pack& pack, const std::string& filePath )
		{
			//Split the path
			//Process the string
			std::vector<std::string> parts = splitPath( filePath );
			
			NodePtr currentNode = pack.getRootNode();
			if( !currentNode )
			{
				return FilePtr();
			}

			const std::size_t Count = parts.size();
			for( std::size_t i = 0; i < Count; ++i )
			{
				if( currentNode && 
					currentNode->getType() == Node::Type_Folder )
				{
					FolderPtr folder = std::static_pointer_cast<Folder>( currentNode );
					if( i != Count - 1 )	//If not the last thing.
					{
						NodePtr newNode = folder->getChild( parts[i], Node::Type_Folder );
						if( newNode )
						{
							currentNode = newNode;
						}
					}
					else	//if is file
					{
						NodePtr newNode = currentNode = folder->getChild( parts[i], Node::Type_File );
						if( newNode )
						{
							return std::static_pointer_cast<File>( newNode );
						}
					}
				}
			}
			return FilePtr();
		}
	}
}