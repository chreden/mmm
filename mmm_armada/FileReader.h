#pragma once

//This is just me trying to duplicate some internal armada code

class File
{
	unsigned char m_error;
	unsigned char m_saved_game;
	unsigned char m_binary;
	unsigned char m_block_header;
};

typedef void Addr;

class FileReader
{
private:
	File File;
	int m_version;
	void* m_buffer;
	int m_buffer_size;
	unsigned char m_buffer_mine;
	std::list<Addr*> m_addr_list;
	std::map<void*, void*> m_old_new_map;
	std::vector<char*> m_chapter;
	std::vector<char*> m_chapter_end;
	char* inCurrent;
	char* inLast;
	char* nextLine;
};
