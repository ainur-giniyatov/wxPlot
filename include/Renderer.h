#pragma once

#include "plot_defs.h"

#include "Series.h"
#include "Data.h"
#include "Plot.h"
#include "Space.h"
#include "Axis.h"
#include "ValueAdaptor.h"

#include <wx/graphics.h>

template <typename T> class WXDLLIMPEXP_PLOTLIB DataTyped;
class WXDLLIMPEXP_PLOTLIB DataNoType;
class WXDLLIMPEXP_PLOTLIB SeriesND;
class WXDLLIMPEXP_PLOTLIB Plot;
class WXDLLIMPEXP_PLOTLIB Axis;
class WXDLLIMPEXP_PLOTLIB SpaceND;
template <typename T> class WXDLLIMPEXP_PLOTLIB ValueAdaptor;

class WXDLLIMPEXP_PLOTLIB Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	void SetOwner(SeriesND *series);
	SeriesND *GetOwner() { return m_owner_series; }

	virtual void Render(wxGraphicsContext *gc) = 0;
protected:
	SeriesND *m_owner_series;

	int m_text_pos;
};
//
//class WXDLLIMPEXP_PLOTLIB Renderer1D : public Renderer
//{
//public:
//	Renderer1D();
//	virtual ~Renderer1D();
//
//};
//
//template<typename T> class WXDLLIMPEXP_PLOTLIB Renderer1DTyped : public Renderer1D
//{
//public:
//	Renderer1DTyped();
//	virtual ~Renderer1DTyped();
//
//	virtual void Render(wxGraphicsContext *gc) override;
//};
//
//template  class Renderer1DTyped<int>;
//template  class Renderer1DTyped<float>;

class WXDLLIMPEXP_PLOTLIB Renderer2D : public Renderer
{
public:
	Renderer2D();
	virtual ~Renderer2D();

};

template<typename T1, typename T2> class WXDLLIMPEXP_PLOTLIB Renderer2DTyped : public Renderer2D
{
public:
	Renderer2DTyped();
	virtual ~Renderer2DTyped();

	virtual void Render(wxGraphicsContext *gc) override;
};

template WXDLLIMPEXP_PLOTLIB class Renderer2DTyped<int, int>;
template WXDLLIMPEXP_PLOTLIB class Renderer2DTyped<time_t, int>;
template WXDLLIMPEXP_PLOTLIB class Renderer2DTyped<float, float>;
template WXDLLIMPEXP_PLOTLIB class Renderer2DTyped<time_t, float>;
//template WXDLLIMPEXP_PLOTLIB class Renderer2DTyped<double>;
//template WXDLLIMPEXP_PLOTLIB class Renderer2DTyped<float>;
//template WXDLLIMPEXP_PLOTLIB class Renderer2DTyped<short int>;
