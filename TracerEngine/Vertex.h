#pragma once

#include <GL/glew.h>

namespace TE
{
	struct Position
	{
		float x;
		float y;
	};

	struct ColorRGBA8
	{
		ColorRGBA8() : r(0), g(0), b(0), a(0) { }
		ColorRGBA8(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a) : r(_r), g(_g), b(_b), a(_a) { }
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;

		void set(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a)
		{
			r = _r; g = _g; b = _b; a = _a;
		}
	};

	struct UV
	{
		float u;
		float v;
	};

	struct Vertex
	{
		Position pos;
		ColorRGBA8 color;
		UV uv;

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color.set(r, g, b, a);
		}

		void setUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}

		void setPos(float x, float y)
		{
			pos.x = x;
			pos.y = y;
		}
	};
}