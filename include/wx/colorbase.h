#pragma once

#include <wx/pen.h>
#include <wx/dcclient.h>
#include <wx/graphics.h>

#include "../plot_defs.h"

extern wxDash MYDASHES[][6];
extern int MYDASHES_COUNT;
extern long COLOR_BASE[];
extern int DLLIMPEXP_PLOTLIB COLOR_BASE_COUNT;


extern MARKER_STYLES MARKERSTYLES[];
extern int MARKERSTYLES_COUNT;

//void PutMark(wxGraphicsContext *gc, int x, int y, MARKER_STYLES marker_style, int mark_size);
//void PrepareMarkGC(wxGraphicsContext *gc, MARKER_STYLES marker_style, int mark_size, int colour_index);
