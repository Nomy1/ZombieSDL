#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include <vector>
#include "Errors.h"

namespace TE
{
	GLTexture ImageLoader::loadPNG(std::string filepath)
	{
		std::vector<unsigned char> in;
		std::vector<unsigned char> out;
		if (IOManager::readFileToBuffer(filepath, in) == false)
		{
			fatalError("Failed to read " + filepath + " into buffer");
		}

		GLTexture texture = {};
		int errorCode = decodePNG(out, (&texture)->width, (&texture)->height, &(in[0]), in.size());
		if (errorCode != 0)
		{
			fatalError("Failed to decode PNG " + filepath + " with error " + std::to_string(errorCode));
		}

		glGenTextures(1, &(texture.id));
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		return texture;
	}
}