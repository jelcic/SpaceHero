#ifndef _TYPES_H
#define _TYPES_H

namespace Engine
{
	enum class Orientation { left, right };

	class Vec2
	{
	public:
		Vec2() { X = 0; Y = 0; };
		Vec2(float x, float y) : X(x), Y(y) {};
		~Vec2() {};
		float X;
		float Y;

		const Vec2& operator=(float xy)
		{
			X = xy;
			Y = xy;
			return *this;
		};

		const Vec2& operator=(const Vec2& v)
		{
			X = v.X;
			Y = v.Y;
			return *this;
		};

		const Vec2 operator+(const Vec2& v)
		{
			return Vec2(X+v.X, Y+v.Y);
		};

		const Vec2 operator-(const Vec2& v)
		{
			return Vec2(X - v.X, Y - v.Y);
		};

		const Vec2 operator*(float xy)
		{
			return Vec2(X*xy, Y*xy);
		};

		const Vec2 operator*(const Vec2& v)
		{
			return Vec2(X*v.X, Y*v.Y);
		};

		const Vec2 operator+(float xy)
		{
			return Vec2(X+xy, Y+xy);
		};

		const Vec2 operator-(float xy)
		{
			return Vec2(X-xy, Y-xy);
		};

		const Vec2& operator+=(float xy)
		{
			X = X + xy;
			Y = Y + xy;
			return *this;
		};
		const Vec2& operator+=(const Vec2& v)
		{
			X = X + v.X;
			Y = Y + v.Y;
			return *this;
		};

		const Vec2& operator*=(float xy)
		{
			X = X * xy;
			Y = Y * xy;
			return *this;
		};
		const Vec2& operator*=(const Vec2& v)
		{
			X = X * v.X;
			Y = Y * v.Y;
			return *this;
		};

		// Different versions of operator -=
		const Vec2& operator-=(float xy)
		{
			X = X - xy;
			Y = Y - xy;
			return *this;
		};
		const Vec2& operator-=(const Vec2& v)
		{
			X = X - v.X;
			Y = Y - v.Y;
			return *this;
		};
	};

	class Size
	{
	public:
		Size() { Width = 0; Height = 0; };
		Size(int W, int H) { Width = W; Height = H; };
		~Size() {};
		int Width;
		int Height;
	};

}
#endif /* _TYPES_H */