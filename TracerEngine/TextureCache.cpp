#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace TE
{
	TextureCache::TextureCache() : m_textureMap()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string filepath)
	{
		// try to find texture
		auto mapIterator = m_textureMap.find(filepath);

		// create new texture if not found
		if (mapIterator == m_textureMap.end())
		{
			GLTexture newTexture = ImageLoader::loadPNG(filepath);

			// insert new texture into map
			m_textureMap.insert(make_pair(filepath, newTexture));
			//std::cout << "Loaded cached texture\n";
			return newTexture;
		}

		//std::cout << "Loaded texture " + filepath + "\n";
		// return texture
		return mapIterator->second;
	}
}