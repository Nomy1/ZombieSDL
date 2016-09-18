#pragma once
#include <vector>
#include <string>

namespace TE
{
	class IOManager
	{
	public:
		static bool readFileToBuffer(const std::string filepath, std::vector<unsigned char>& buffer);
	};
}
