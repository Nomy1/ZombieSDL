#include <algorithm>
#include "SpriteBatch.h"

namespace TE
{
	SpriteBatch::SpriteBatch() : m_vbo(0), m_vao(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::init()
	{
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType glyphSortTime /* = GlyphSortType::TEXTURE*/)
	{
		m_glypthSortType = glyphSortTime;
		m_renderBatches.clear();
		
		// destroy allocated pointers for glyphs
		for (unsigned int i = 0; i < m_glyphs.size(); i++)
		{
			delete m_glyphs[i];
		}

		m_glyphs.clear();
	}

	void SpriteBatch::end()
	{
		sortGlyphs();
		createRenderBatches();
	}

	// Rect definition
	// x = x position
	// y = y position
	// z = width
	// w = height
	void SpriteBatch::draw(GLuint textureId, const glm::vec4& texRect, const glm::vec4& uvRect, float depth, const ColorRGBA8& color)
	{
		Glyph* newGlyph = new Glyph;
		newGlyph->textureId = textureId;
		newGlyph->depth = depth;

		newGlyph->topLeft.color = color;
		newGlyph->topLeft.setPos(texRect.x, texRect.y + texRect.w);
		newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		newGlyph->bottomLeft.color = color;
		newGlyph->bottomLeft.setPos(texRect.x, texRect.y);
		newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

		newGlyph->bottomRight.color = color;
		newGlyph->bottomRight.setPos(texRect.x + texRect.z, texRect.y);
		newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		newGlyph->topRight.color = color;
		newGlyph->topRight.setPos(texRect.x + texRect.z, texRect.y + texRect.w);
		newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		m_glyphs.push_back(newGlyph);
	}

	void SpriteBatch::renderBatch()
	{
		glBindVertexArray(m_vao);
		for (unsigned int i = 0; i < m_renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].textureId);
			glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
		}
		glBindVertexArray(0);
	}

	void SpriteBatch::createRenderBatches()
	{
		// no need to create batches if no glyphs exist
		if (m_glyphs.empty())
			return;

		// initialize vertices count
		std::vector<Vertex> vertices;
		vertices.resize(m_glyphs.size() * 6);

		m_renderBatches.emplace_back(0, 6, m_glyphs[0]->textureId);

		// set first glyph vertices
		int vertexOffset = 0;
		int currVertex = 0;
		vertices[currVertex++] = m_glyphs[0]->topLeft;
		vertices[currVertex++] = m_glyphs[0]->bottomLeft;
		vertices[currVertex++] = m_glyphs[0]->bottomRight;
		vertices[currVertex++] = m_glyphs[0]->bottomRight;
		vertices[currVertex++] = m_glyphs[0]->topRight;
		vertices[currVertex++] = m_glyphs[0]->topLeft;
		vertexOffset += 6;

		// set the rest
		for (unsigned int i = 1; i < m_glyphs.size(); i++)
		{
			if (m_glyphs[i]->textureId != m_glyphs[i-1]->textureId)
			{
				// create new render batch if texture is different
				m_renderBatches.emplace_back(vertexOffset, 6, m_glyphs[i]->textureId);
			}
			else
			{
				m_renderBatches.back().numVertices += 6;
			}

			vertices[currVertex++] = m_glyphs[i]->topLeft;
			vertices[currVertex++] = m_glyphs[i]->bottomLeft;
			vertices[currVertex++] = m_glyphs[i]->bottomRight;
			vertices[currVertex++] = m_glyphs[i]->bottomRight;
			vertices[currVertex++] = m_glyphs[i]->topRight;
			vertices[currVertex++] = m_glyphs[i]->topLeft;
			vertexOffset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		// orphan buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size()*sizeof(Vertex), vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::createVertexArray()
	{
		if (m_vao == 0)
		{
			glGenVertexArrays(1, &m_vao);
		}
		glBindVertexArray(m_vao);

		if (m_vbo == 0)
		{
			glGenBuffers(1, &m_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// setup attribute pointers
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}

	void SpriteBatch::sortGlyphs()
	{
		switch (m_glypthSortType)
		{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(m_glyphs.begin(), m_glyphs.end(), compareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_glyphs.begin(), m_glyphs.end(), compareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(m_glyphs.begin(), m_glyphs.end(), compareTexture);
			break;
		}
	}

	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph *b) { return (a->depth < b->depth); }
	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph *b) { return (a->depth > b->depth); }
	bool SpriteBatch::compareTexture(Glyph* a, Glyph *b) { return (a->textureId < b->textureId); }
}
