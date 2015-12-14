#pragma once

#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Plot.h"
#include "Renderer.h"
#include "Widget.h"
#include "Space.h"

#include <wx/graphics.h>

class WXDLLIMPEXP_PLOTLIB DataNoType;
class WXDLLIMPEXP_PLOTLIB SeriesND;
class WXDLLIMPEXP_PLOTLIB Plot;
class WXDLLIMPEXP_PLOTLIB SpaceND;
class WXDLLIMPEXP_PLOTLIB Renderer;
class WXDLLIMPEXP_PLOTLIB Renderer2D;
class WXDLLIMPEXP_PLOTLIB Widget;

class WXDLLIMPEXP_PLOTLIB LegendsWidget :public Widget
{
public:
	LegendsWidget(Plot *owner);
	virtual ~LegendsWidget();

	void virtual Fit() override;
	virtual void Render(wxGraphicsContext *gc) override;
protected:
private:
	virtual void OnMouseRightUp(int x, int y) override;

	void OnMenuDeleteSeries(wxCommandEvent &event);
	static const int ID_MENU_DELETE_SERIES;
	wxMenuItem *m_menuitem_delete_widget;

	SeriesND *m_pointed_series;
	DECLARE_EVENT_TABLE();
};