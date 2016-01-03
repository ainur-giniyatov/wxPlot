#include "wx/colorbase.h"
//#include <wx/pen.h>

wxDash MYDASHES[5][6] = {
    {0, 0, 0, 0, 0, 0},
    {8, 4, 8, 4, 8, 4},
    {8, 2, 2, 2, 2, 2},
    {3, 2, 3, 2, 3, 2},
    {10, 8, 3, 8, 10, 8}
    };

int MYDASHES_COUNT = 4;

long COLOR_BASE[] = {
    0x8B0000,
    0x006400,
    0x00FF00,
    0xFFFF00,
    0x8B8B52,
    0x00008B,
    0x32CD9A,
    0x3F85CD,
    //0xD3D3D3,
    0x969696,
    0x0000FF,
    0xFF00FF
    };
int COLOR_BASE_COUNT = sizeof(COLOR_BASE) / sizeof(long);

MARKER_STYLES MARKERSTYLES[] = {MARKER_CIRCLE, MARKER_CROSS, MARKER_ROMB, MARKER_SQUARE, MARKER_PLUS};
int MARKERSTYLES_COUNT = sizeof(MARKERSTYLES) / sizeof(MARKER_STYLES);

wxPoint2DDouble mark_pointsdouble[4];


void PutMark(wxGraphicsContext *gc, int x, int y, MARKER_STYLES marker_style, int mark_size)
{

    static wxPoint2DDouble points2d[5];
    switch(marker_style)
    {
    case MARKER_CIRCLE:
        gc->DrawEllipse(x - mark_size, y - mark_size, mark_size * 2, mark_size * 2);
        break;
    case MARKER_SQUARE:
        gc->DrawRectangle(x - mark_size, y - mark_size, mark_size * 2, mark_size * 2);
        break;
    //case MARKSTYLE_TRIANGLEVERT:
    //    break;
    //case MARKSTYLE_TRIANGLEHORIZ:
    //    break;
    case MARKER_ROMB:
        for(int i = 0; i < 4; i++)
        {
            points2d[i] = mark_pointsdouble[i] + wxPoint2DDouble(x, y);
        }
        points2d[4] = points2d[0];
        gc->DrawLines(5, points2d);
        break;
    case MARKER_CROSS:
        for(int i = 0; i < 4; i++)
        {
            points2d[i] = mark_pointsdouble[i] + wxPoint2DDouble(x, y);
        }
        gc->StrokeLines(2, points2d);
        gc->StrokeLines(2, points2d + 2);
        break;
    case MARKER_PLUS:
        for(int i = 0; i < 4; i++)
        {
            points2d[i] = mark_pointsdouble[i] + wxPoint2DDouble(x, y);
        }
        gc->StrokeLines(2, points2d);
        gc->StrokeLines(2, points2d + 2);
        break;
    default:
        assert(0);

    }

}

void PrepareMarkGC(wxGraphicsContext *gc, MARKER_STYLES marker_style, int mark_size, int colour_index)
{
	assert(colour_index < COLOR_BASE_COUNT);
    wxPen pen = wxPen(*wxBLACK);//wxColour(COLOR_BASE[colour_index]));
	wxBrush brush = wxBrush(wxColour(COLOR_BASE[colour_index]));//colour_index

    switch(marker_style)
    {
    //case MARKSTYLE_TRIANGLEVERT:
    //    break;
    //case MARKSTYLE_TRIANGLEHORIZ:
    //    break;
    case MARKER_ROMB:
        mark_pointsdouble[0] = wxPoint2DDouble(0, -mark_size);
        mark_pointsdouble[1] = wxPoint2DDouble(mark_size, 0);
        mark_pointsdouble[2] = wxPoint2DDouble(0, mark_size);
        mark_pointsdouble[3] = wxPoint2DDouble(-mark_size, 0);
        break;
    case MARKER_CROSS:
        pen.SetColour(wxColour(COLOR_BASE[colour_index]));
        mark_pointsdouble[0] = wxPoint2DDouble(-mark_size, -mark_size);
        mark_pointsdouble[1] = wxPoint2DDouble(mark_size, mark_size);
        mark_pointsdouble[2] = wxPoint2DDouble(mark_size, -mark_size);
        mark_pointsdouble[3] = wxPoint2DDouble(-mark_size, mark_size);
        pen.SetWidth(mark_size > 2 ? 2 : 1);
        break;
    case MARKER_PLUS:
        pen.SetColour(wxColour(COLOR_BASE[colour_index]));
        mark_pointsdouble[0] = wxPoint2DDouble(0, -mark_size);
        mark_pointsdouble[1] = wxPoint2DDouble(0, mark_size);
        mark_pointsdouble[2] = wxPoint2DDouble(-mark_size, 0);
        mark_pointsdouble[3] = wxPoint2DDouble(mark_size, 0);
        pen.SetWidth(mark_size > 2 ? 2 : 1);
        break;
    default:
        ;

    }
    gc->SetPen(pen);
    gc->SetBrush(brush);
}

//
//#00008B	0
//#006400	1
//#00FF00	2
//#00FFFF	3
//#528B8B	4
//#8B0000	5
//#9ACD32	6
//#CD853F	7
//#D3D3D3	8
//#FF0000	9
//#FF00FF   10

//LTVA	1
//ROPV	2
//LTIA	0
//ROPC	10
//HFC5	9
//
//BVDA	1
//HFV5	8
//BIDA	0
//HFC5	8
//
//PFTN	1
//PFMS	0
//HFTN	5
//HFMS	9
//SLDF	6
//RLDF	7
//TSTS	3
//
//ASAT	1
//FSAT	0
//AQAT	5
//
//AQAP	1
//FSAP	0
//ASAP	5
//TSTS	3
//
//AQAP-ASAP	1
//AQAP-FSAP	0
//
//FSAP	1
//ASAP	0
//FSAT	5
//ASAT	4
