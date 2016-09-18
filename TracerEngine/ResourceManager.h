#pragma once
#include "TextureCache.h"
#include "GLTexture.h"
#include <string>

namespace TE
{
	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string filepath);

	private:
		static TextureCache m_textureCache;
	};
}
