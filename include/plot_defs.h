#pragma once

#define TODO assert(false);

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#endif // _MSC_VER

#ifdef _DEBUG
#include <stdio.h>
	#define DPRINTF(__dstr) printf(__dstr);

#else

	#define DPRINTF(__dstr)

#endif




#ifdef __GNUC__
#   define DLLEXPORT __attribute__((dllexport))
#   define DLLIMPORT __attribute__((dllimport))
#elif defined(_MSC_VER)
#   define DLLEXPORT __declspec(dllexport)
#   define DLLIMPORT __declspec(dllimport)
#endif // __GNUC__

#ifdef MAKINGDLL

  #define DLLIMPEXP_PLOTLIB DLLEXPORT

#elif defined(MAKINGLIB)

  #define DLLIMPEXP_PLOTLIB

#else

  #define DLLIMPEXP_PLOTLIB DLLIMPORT

#endif

enum AXIS_DIR {
	AXIS_X = 0,
	AXIS_Y = 1,
	AXIS_Z = 2,

	AXIS_NONE = 999
};

enum Dir {
	DIR_NONE = 0,
	DIR_HOR = (1 << 0),
	DIR_VER = (1 << 1),
	DIR_ALL = (DIR_HOR | DIR_VER)
};

enum MARKER_STYLES {
	MARKER_NONE,
	MARKER_DOT,
	MARKER_CIRCLE,
	MARKER_SQUARE,
	MARKER_TRIANGLE,
	MARKER_ROMB,
	MARKER_CROSS,
	MARKER_PLUS
};

enum LINE_STYLES {
	LINE_NONE,
	LINE_SOLID,
	LINE_DASH1,
	LINE_DASH2,
	LINE_DASH3,
	LINE_DOTS1,
	LINE_DOTS2,
	LINE_DOTS3
};

enum LEFTBUTTON_ACTION {
	LBA_NONE,
	LBA_PAN,
	LBA_ZOOMSELECT
};

template <typename T> struct Point {
	T x;
	T y;
	Point() :x(0), y(0) {};
	Point(T x, T y) { Point::x = x; Point::y = y; };
	Point(const Point<T>& p) { x = p.x; y = p.y; }

	inline Point<T> operator - (const Point<T>& p1) { return Point<T>(x - p1.x, y - p1.y); }
	inline Point<T> operator + (const Point<T>& p1) { return Point<T>(x + p1.x, y + p1.y); }
	inline Point<T> operator / (T d) { return Point<T>(x / d, y / d); }

};

template <typename T> struct Rect {

	Rect() :left(0), right(0), top(0), bottom(0) {};
	Rect(T l, T t, T w, T h) { left = l; right = left + w; top = t; bottom = top + h; }
	Rect(const Point<T> &p1, const Point<T> &p2)
	{
		if (p2.x > p1.x)
		{
			left = p1.x;
			right = p2.x;
		}
		else
		{
			left = p2.x;
			right = p1.x;
		}

		if (p2.y > p1.y)
		{
			top = p1.y;
			bottom = p2.y;
		}
		else
		{
			top = p2.y;
			bottom = p1.y;
		}
	}

	Rect(Rect &r) { left = r.left; right = r.right; top = r.top; bottom = r.bottom; }

	inline T Width() { return right - left; }
	inline T Height() { return bottom - top; }

	inline void SetLeft(T l, bool keepwidth = true)
	{
		T w = right - left;
		left = l;
		if (keepwidth)
			right = left + w;
	}

	inline void SetRight(T r, bool keepwidth = true)
	{
		T w = right - left;
		right = r;
		if (keepwidth)
			left = right - w;
	}

	inline void SetTop(T t, bool keepheight = true)
	{
		T h = bottom - top;
		top = t;
		if (keepheight)
			bottom = top + h;

	}

	inline void SetBottom(T b, bool keepheight = true)
	{
		T h = bottom - top;
		bottom = b;
		if (keepheight)
			top = bottom - h;

	}

	inline void SetCenterHor(T c)
	{
		T h1, h2;
		h1 = (right - left) / 2;
		h2 = (right - left) - h1;
		left = c - h1;
		right = c + h2;
	}

	inline void SetCenterVer(T c)
	{
		T h1, h2;
		h1 = (bottom - top) / 2;
		h2 = (bottom - top) - h1;
		top = c - h1;
		bottom = c + h2;
	}

	inline void Inflate(T dd)
	{
		left -= dd;
		right += dd;
		top -= dd;
		bottom += dd;
	}

	inline bool IsInside(const Point<T> &p)
	{
		return p.x >= left && p.x <= right && p.y >= top && p.y <= bottom;
	}

	inline Point<T> Middle() { return Point<T>((right - left) / (T)2, (bottom - top) / (T)2); }
	inline void MoveTo(const Point<T>& p) { T w = right - left, h = bottom - top; left = p.x; top = p.y, right = left + w; bottom = top + h; }

	T left, right, top, bottom;
private:

};

#include <iostream>
#include <chrono>

class Timer
{
public:
	Timer() : beg_(clock_::now()) {}
	void reset() { beg_ = clock_::now(); }
	double elapsed() const {
		return std::chrono::duration_cast<second_>
			(clock_::now() - beg_).count();
	}

private:
	typedef std::chrono::high_resolution_clock clock_;
	typedef std::chrono::duration<double, std::ratio<1> > second_;
	std::chrono::time_point<clock_> beg_;
};