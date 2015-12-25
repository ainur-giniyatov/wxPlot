#pragma once

#include <wx/wxprec.h>


#define TODO assert(false);
#ifdef _DEBUG
#include <wx/debug.h>
#include <stdio.h>
	#define DPRINTF(__dstr) printf(__dstr);

#else

	#define DPRINTF(__dstr)

#endif

#ifdef __GNUC__
#   define DLLEXPORT __attribute__((dllexport))
#   define DLLIMPORT __attribute__((dllimport))
#elif defined(__VISUALC__)
#   define DLLEXPORT __declspec(dllexport)
#   define DLLIMPORT __declspec(dllimport)
#endif // __GNUC__

#ifdef MAKINGDLL

  #define WXDLLIMPEXP_PLOTLIB DLLEXPORT

#elif defined(MAKINGLIB)

  #define WXDLLIMPEXP_PLOTLIB

#else

  #define WXDLLIMPEXP_PLOTLIB DLLIMPORT

#endif

enum AXIS_DIR {
	AXIS_X = 0,
	AXIS_Y = 1,
	AXIS_Z = 2,

	AXIS_NONE = 999
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

enum LINE_STYLE {
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