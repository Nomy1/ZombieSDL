#pragma once

#include <GL/glew.h>
#include <string>

namespace TE
{
	class GlslProgram
	{
	public:
		GlslProgram();
		~GlslProgram();

		void compileShaders(const std::string& vertShaderFilepath, const std::string& fragShaderFilepath);
		void addAttribute(const std::string attribName);
		void linkShaders();
		void enable();
		void disable();
		GLuint getUniformLoc(const std::string uniformName);
	private:
		void compileShader(const std::string filepath, GLuint* shaderId);
		int m_attribCnt;
		GLuint m_programId;
		GLuint m_vertShaderId;
		GLuint m_fragShaderId;
	};
}