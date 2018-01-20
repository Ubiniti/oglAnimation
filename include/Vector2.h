#pragma once

template<class T>
class Vector2
{
public:
	T x, y;
	Vector2(T x, T y) : x(x), y(y)
	{}
};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;