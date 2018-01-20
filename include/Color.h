#pragma once

namespace gle {

	class Color
	{
	public:
		static const Color BLACK;
		static const Color BLUE;
		static const Color CYAN;
		static const Color GREEN;
		static const Color RED;
		static const Color WHITE;

		float r, g, b, a;
		Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
		{}
	};

}