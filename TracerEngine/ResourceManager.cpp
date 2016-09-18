#include "ResourceManager.h"

namespace TE
{
	TextureCache ResourceManager::m_textureCache;

	GLTexture ResourceManager::getTexture(std::string filepath)
	{
		return m_textureCache.getTexture(filepath);
	}
}