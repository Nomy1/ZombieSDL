#include "GlslProgram.h"
#include "Errors.h"

#include <vector>
#include <string>
#include <fstream>

namespace TE
{
	GlslProgram::GlslProgram() : m_attribCnt(0), m_programId(0), m_vertShaderId(0), m_fragShaderId(0)
	{
	}


	GlslProgram::~GlslProgram()
	{
	}

	void GlslProgram::compileShaders(const std::string& vertShaderFilepath, const std::string& fragShaderFilepath)
	{
		// create program
		m_programId = glCreateProgram();

		// vertex shader
		m_vertShaderId = glCreateShader(GL_VERTEX_SHADER);
		compileShader(vertShaderFilepath, &m_vertShaderId);

		// fragment shader
		m_fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		compileShader(fragShaderFilepath, &m_fragShaderId);
	}

	void GlslProgram::compileShader(const std::string filepath, GLuint* shaderId)
	{
		if (*shaderId == 0)
		{
			fatalError("Shader failed to compile: " + filepath);
		}

		// open shader file
		std::ifstream shaderIfstream(filepath);
		if (shaderIfstream.fail())
		{
			perror(filepath.c_str());
			fatalError("Failed to read file at path: " + filepath);
		}

		// read file contents
		std::string fileContents = "";
		std::string line;
		while (std::getline(shaderIfstream, line))
		{
			fileContents += line + "\n";
		}

		shaderIfstream.close();

		// compile
		const char* contentsPtr = fileContents.c_str();
		glShaderSource(*shaderId, 1, &contentsPtr, nullptr);
		glCompileShader(*shaderId);

		// error checking
		GLint compileStatus;
		glGetShaderiv(*shaderId, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus == GL_FALSE)
		{
			GLint maxLen = 0;
			glGetShaderiv(*shaderId, GL_INFO_LOG_LENGTH, &maxLen);

			std::vector<char> errorLog(maxLen);
			glGetShaderInfoLog(*shaderId, maxLen, &maxLen, &errorLog[0]);

			glDeleteShader(*shaderId);
			std::printf("%s\n", &(errorLog[0]));
			fatalError("Failed to compile shader: " + filepath + "\n");
		}
	}

	void GlslProgram::addAttribute(const std::string attribName)
	{
		glBindAttribLocation(m_programId, m_attribCnt++, attribName.c_str());
	}

	void GlslProgram::linkShaders()
	{
		// attach shaders to program and link program
		glAttachShader(m_programId, m_vertShaderId);
		glAttachShader(m_programId, m_fragShaderId);
		glLinkProgram(m_programId);

		// error checking
		GLint isLinked = 0;
		glGetProgramiv(m_programId, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLen = 0;
			glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &maxLen);
			std::vector<GLchar> errorLog(maxLen);
			glGetProgramInfoLog(m_programId, maxLen, &maxLen, &errorLog[0]);
			printf("%s\n", &(errorLog[0]));
			fatalError("Could not link program! \n");

			// error cleanup
			glDeleteProgram(m_programId);
			glDeleteShader(m_vertShaderId);
			glDeleteShader(m_fragShaderId);

			return;
		}

		// cleanup
		glDetachShader(m_programId, m_vertShaderId);
		glDetachShader(m_programId, m_fragShaderId);
		glDeleteShader(m_vertShaderId);
		glDeleteShader(m_fragShaderId);
	}

	void GlslProgram::enable()
	{
		glUseProgram(m_programId);
		for (int i = 0; i < m_attribCnt; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}

	void GlslProgram::disable()
	{
		glUseProgram(0);
		for (int i = 0; i < m_attribCnt; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}

	GLuint GlslProgram::getUniformLoc(const std::string uniformName)
	{
		GLint locId = glGetUniformLocation(m_programId, uniformName.c_str());
		if (locId == GL_INVALID_INDEX)
		{
			fatalError("Cannot find Uniform " + uniformName + " not found in shader!");
		}

		return locId;
	}
}