#pragma once
#include <wx/graphics.h>

class wxRenderable 
{
public:
	virtual void Render(wxGraphicsContext *gc) = 0;
};