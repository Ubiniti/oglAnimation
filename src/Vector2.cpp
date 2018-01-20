#include "Vector2.h"
// ------------------------------------------------------------------------------------------
template<class T>
Vector2<T> operator+(const Vector2<T> &vec1, const Vector2<T> &vec2)
{
	return Vector2(vec1.x + vec2.x, vec1.y + vec2.y);
}
// ------------------------------------------------------------------------------------------
template<class T>
Vector2<T> operator-(const Vector2<T> &vec1, const Vector2<T> &vec2)
{
	return Vector2(vec1.x - vec2.x, vec1.y - vec2.y);
}
// ------------------------------------------------------------------------------------------