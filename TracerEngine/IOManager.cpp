#include "IOManager.h"
#include <fstream>

namespace TE
{
	bool IOManager::readFileToBuffer(const std::string filepath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filepath, std::ios::binary);
		if (file.fail())
		{
			perror(filepath.c_str());
			return false;
		}

		// seek to file end
		file.seekg(0, std::ios::end);

		// get file size
		auto filesize = file.tellg();

		// reset file seek position
		file.seekg(0, std::ios::beg);

		// disregard file header bytes
		filesize -= file.tellg();

		// file buffer with file contents
		buffer.resize(filesize);
		file.read((char*)&(buffer[0]), filesize);
		file.close();

		return true;
	}
}