#pragma once
#include <map>
#include <string>
#include "GLTexture.h"

namespace TE
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string filepath);

	private:
		std::map<std::string, GLTexture> m_textureMap;
	};
}
