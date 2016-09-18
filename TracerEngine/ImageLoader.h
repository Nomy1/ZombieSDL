#pragma once

#include "GLTexture.h"
#include <string>

namespace TE
{
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(const std::string filepath);
	};
}
