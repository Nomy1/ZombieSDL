#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Vertex.h"

namespace TE
{
	enum class GlyphSortType
	{
		FRONT_TO_BACK, 
		BACK_TO_FRONT, 
		TEXTURE
	};

	struct Glyph
	{
		GLuint textureId;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};

	class RenderBatch
	{
	public:
		RenderBatch(GLuint _offset, GLuint _numVertices, GLuint _textureId) : offset(_offset), numVertices(_numVertices), textureId(_textureId)
		{
		}
		GLuint offset;
		GLuint numVertices;
		GLuint textureId;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();
		void begin(GlyphSortType glyphSortTime = GlyphSortType::TEXTURE);
		void end();
		void draw(GLuint textureId, const glm::vec4& texRect, const glm::vec4& uvRect, float depth, const ColorRGBA8& color);
		void renderBatch();

	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph *b);
		static bool compareBackToFront(Glyph* a, Glyph *b);
		static bool compareTexture(Glyph* a, Glyph *b);

		GLuint m_vbo;
		GLuint m_vao;
		GlyphSortType m_glypthSortType;
		std::vector<Glyph*> m_glyphs;
		std::vector<RenderBatch> m_renderBatches;
	};
}

