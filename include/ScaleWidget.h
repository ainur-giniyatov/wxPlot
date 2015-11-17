#pragma once

#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Plot.h"
#include "Renderer.h"
#include "Scale.h"
#include "Widget.h"

#include <wx/graphics.h>

class WXDLLIMPEXP_PLOTLIB DataNoType;
class WXDLLIMPEXP_PLOTLIB SeriesND;
class WXDLLIMPEXP_PLOTLIB Plot;
class WXDLLIMPEXP_PLOTLIB SpaceND;
class WXDLLIMPEXP_PLOTLIB Renderer;
class WXDLLIMPEXP_PLOTLIB Renderer2D;
class WXDLLIMPEXP_PLOTLIB Scale;
class WXDLLIMPEXP_PLOTLIB Widget;


class WXDLLIMPEXP_PLOTLIB ScaleWidget :public Widget, public Scale
{
public:
	ScaleWidget(Plot *owner);
	virtual ~ScaleWidget();

	/*calculate size*/
	void virtual Fit() override;

	virtual void Render(wxGraphicsContext *gc) override;

	virtual void MouseWheel(double factor, int x, int y) override;

protected:
private:
	virtual void proceed_dragging(int x, int y) override;

	// Inherited via Scale
	virtual void ScaleRedraw() override;

	wxOrientation m_orient;
};