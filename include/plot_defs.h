#pragma once

#include <wx/wxprec.h>



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
