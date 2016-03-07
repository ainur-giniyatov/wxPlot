#include <algorithm>
#include <math.h>
#include <assert.h>
#include <string>
#include <string.h>
#include <vector>
#include <iterator>

#include "SubPlot.h"
#include "Series.h"
#include "Renderer.h"

using namespace plot;

static char *s_subplotname = "plot";

Subplot::Subplot(const char *subplotname)
{

	DPRINTF("Subplot ctor\n");
	m_panning = false;
	m_zoomselecting = false;
	m_zoomsel_switch = false;
	m_orientation = ORIENTATION_NORMAL;
	m_is_data_view_modified = true;

	if (subplotname == NULL)
		m_subplot_name = s_subplotname;
	else
	{
		m_subplot_name = (char *)malloc(strlen(subplotname) + 1);
		strcpy(m_subplot_name, subplotname);
	}

	m_lbaction = LBA_ZOOMSELECT;

	m_selected_box = nullptr;
	m_selected_box_state = BOXIDLE;
	m_selected_box_sides = BOXNONESIDE;

}

void Subplot::SetSubplotName(const char * subplotname)
{
	if (m_subplot_name != NULL && m_subplot_name != s_subplotname)
		free(m_subplot_name);

	if (subplotname == NULL)
		m_subplot_name = s_subplotname;
	else
	{
		m_subplot_name = (char *)malloc(strlen(subplotname) + 1);
		strcpy(m_subplot_name, subplotname);
	}
}

void plot::Subplot::AddSeries(Series * series)
{
	m_serie.push_back(series);
	series->_setowner(this);
	if(series->_getxscale() != nullptr)
		series->_getxscale()->_refresh_plot_list();

	if(series->_getyscale() != nullptr)
		series->_getyscale()->_refresh_plot_list();

	_refresh_dependant_scales();
	m_is_data_view_modified = true;
	RedrawPlot();
}

void plot::Subplot::DeleteSeries(Series * series)
{
	m_serie.erase(std::remove(m_serie.begin(), m_serie.end(), series), m_serie.end());
	delete series;
	_refresh_dependant_scales();
	m_is_data_view_modified = true;
	RedrawPlot();
}

void Subplot::Clear(bool update)
{
	assert(0);
}

Subplot::~Subplot()
{
	DPRINTF("Subplot dtor\n");

	if (m_subplot_name != NULL && m_subplot_name != s_subplotname)
		free(m_subplot_name);

	for (auto box : m_boxes)
		delete box;

	for (auto series : m_serie)
	{

		delete series;
	}

}

void plot::Subplot::SetOrientation(ORIENTATION orientation)
{
	m_orientation = orientation;
	plot_resized();
	Validate();
}


void plot::Subplot::Validate(bool refresh_buffer)
{
	if(refresh_buffer)
		m_is_data_view_modified = true;

	RedrawPlot();
}

//void Subplot::RemoveBox(Box * box)
//{
//	assert(box->_getowner() == this);
//
//	auto tail_i = std::remove_if(m_boxes.begin(), m_boxes.end(), [box](Box *ibox) { return ibox == box; });
//	if (tail_i != m_boxes.end())
//	{
//		m_boxes.erase(tail_i, m_boxes.end());
//		(*tail_i)->_setowner(nullptr);
//		Validate(false);
//	}
//	else
//		assert(0);//this cannot happen
//
//}
//
//void Subplot::DeleteBox(Box * box)
//{
//	RemoveBox(box);
//	delete box;
//}
//
void Subplot::AddBox(Box *box)
{
	if (std::any_of(m_boxes.begin(), m_boxes.end(), [box](Box *b) { return b == box; }))
	{
		return;
	}

	m_boxes.push_back(box);
	box->_setowner(this);

	box->_ownersize(m_size);
	Validate(false);
}
//
//void plot::Subplot::ArrangeBoxes()
//{
//	for_each(m_boxes.begin(), m_boxes.end(), [](Box *box) {box->Sizing(); });
//}


void plot::Subplot::Fit(int axis_mask)
{


	//for (int xd = 0; xd < 3; xd++)
	//	if ((1 << xd) & axis_mask)
	//	{
	//		double vmax = 0, vmin = 0;
	//		bool data_aval = false;

	//		for (auto scale : m_dependant_scales)
	//		{
	//			if (xd != scale->_get_axis_dir())
	//				continue;

	//			for (auto axis : scale->_get_axes())
	//			{
	//				for (auto data : axis->_get_adj_datas())
	//				{
	//					vmax = data->GetDataMax();
	//					vmin = data->GetDataMin();
	//					data_aval = true;
	//					break;
	//				}
	//				if (data_aval)
	//					break;
	//			}

	//			if (data_aval)
	//				break;
	//		}

	//		if (!data_aval)
	//			continue;

	//		for (auto scale : m_dependant_scales)
	//		{
	//			if (xd != scale->_get_axis_dir())
	//				continue;

	//			for (auto axis : scale->_get_axes())
	//			{
	//				for (auto data : axis->_get_adj_datas())
	//				{
	//					double tvmin, tvmax;
	//					tvmin = data->GetDataMin();
	//					tvmax = data->GetDataMax();
	//					vmax = vmax > tvmax ? vmax : tvmax;
	//					vmin = vmin < tvmin ? vmin : tvmin;

	//				}
	//			}
	//			double range = vmax - vmin;
	//			scale->SetOffset(vmin - range / 10.);
	//			scale->SetRange(range + range / 5.);
	//			scale->Validate();
	//		}
	//	}
	//
	Validate();
	validate_other_plots();

}

void plot::Subplot::_refresh_dependant_scales()
{
	//collect all scales and make unique
	m_dependant_scales.clear();
	auto & ds = m_dependant_scales;
	for_each(m_serie.begin(), m_serie.end(), [&ds](Series *series) {
		if(series->_getxscale() != nullptr)
			ds.push_back(series->_getxscale());

		if(series->_getyscale() != nullptr)
			ds.push_back(series->_getyscale());
	});
	std::sort(m_dependant_scales.begin(), m_dependant_scales.end());
	m_dependant_scales.erase(std::unique(m_dependant_scales.begin(), m_dependant_scales.end()), m_dependant_scales.end());
}

const Rect<int> plot::Subplot::_plot_to_backend(Rect<int>& rect)
{
	Rect<int> brect;
	auto bsize = _get_backend_size();

	if (m_orientation == ORIENTATION_NORMAL)
	{
		brect.left = rect.left;
		brect.right = rect.right;
		brect.bottom = bsize.h - rect.top;
		brect.top = bsize.h - rect.bottom;
	}

	if (m_orientation == ORIENTATION_ROTATED)
	{
		brect.bottom = rect.left;
		brect.top = rect.right;
		brect.left = rect.bottom ;
		brect.right = rect.top;
	}

	return brect;
}

Box * plot::Subplot::hitbox(const Point<int>& mouse_backend_coord)
{
	Box *hitbox = nullptr;
	auto mcoord = backend_to_plot(mouse_backend_coord);
	for (auto box : m_boxes)
	{
		if (box->_get_rect().IsInside(mcoord)) {
			hitbox = box;
			break;
		}
	}

	return hitbox;
}

Series * plot::Subplot::hitseries(int *dotindex_first, int *dotindex_last, const Point<int>& mouse_backend_coord)
{
	*dotindex_first = -1;
	*dotindex_last = -1;
	Series *rseries = nullptr;
	auto mcoord = backend_to_plot(mouse_backend_coord);

//	for (auto area : m_areas)
//	{
//		for (auto series = area->GetSerie().rbegin(); series != area->GetSerie().rend(); ++series)
//		{
//			rseries = (*series)->GetRenderer()->_isspotted(mcoord, dotindex_first, dotindex_last);
//			if (rseries != nullptr)
//			{
//#ifdef _DEBUG
//				printf("spot: %s, [%i %i]\n", rseries->GetSeriesName(), *dotindex_first, *dotindex_last);
//#endif
//				return rseries;
//			}
//		}
//	}

	return rseries;
}

void plot::Subplot::leftdown(const Point<int>& mouse_backend_coord)
{
	auto p = backend_to_plot(mouse_backend_coord);

	if (boxprocess_leftdown(mouse_backend_coord))
		return;

	StartPan(p);
}

void plot::Subplot::leftup(const Point<int>& mouse_backend_coord)
{
	auto p = backend_to_plot(mouse_backend_coord);
	boxprocess_leftup(mouse_backend_coord);
	EndPan();
}

void plot::Subplot::rightdown(const Point<int>& mouse_backend_coord)
{
}

void plot::Subplot::rightup(const Point<int>& mouse_backend_coord)
{
}

void plot::Subplot::motion(int mousestate, const Point<int>& mouse_backend_coord)
{
	auto p = backend_to_plot(mouse_backend_coord);

	if ((mousestate & MOUSESTATE_LEFTBUTTON) && m_selected_box != nullptr)
	{
		boxprocess_mousemove(mouse_backend_coord);
	}

	if((mousestate & MOUSESTATE_LEFTBUTTON) && m_panning)
		ProceedPan(p);

}

void plot::Subplot::wheel(int keymodstate, int mousestate, const Point<int> &mouse_backend_coord)
{
	auto p = backend_to_plot(mouse_backend_coord);

	double f;

	if (mousestate & MOUSESTATE_WHEELUP)
		f = 1.2;

	if (mousestate & MOUSESTATE_WHEELDOWN)
		f = 0.8;

	for (auto scale : m_dependant_scales)
	{
		if(scale->_get_axis_dir() == AXIS_X && !(keymodstate & KEYMOD_CTRL))
			scale->ZoomAt((double)p.x / (double)m_size.w, f);

		if (scale->_get_axis_dir() == AXIS_Y)
			scale->ZoomAt((double)p.y / (double)m_size.h, f);

		scale->Validate();
	}

	Validate(true);
	validate_other_plots();
}


bool plot::Subplot::boxprocess_leftdown(const Point<int>& mouse_backend_coord)
{
	//process interaction with on-plot boxes
	for (auto box : m_boxes)
	{
		Point<int> mcoord;
		if (box->_has_flags(Box::BACKENDORIENTED))
		{
			mcoord.x = mouse_backend_coord.x;
			mcoord.y = _get_backend_size().h - mouse_backend_coord.y;
		}
		else
			mcoord = backend_to_plot(mouse_backend_coord);

		if (box->_get_rect().IsInside(mcoord) && box->_has_flags(Box::MOVEABLE))
		{
			m_selected_box = box;
			auto &rect = m_selected_box->_get_rect();
			auto border_thickness = m_selected_box->_get_borderthickenss();
			int x = mcoord.x;
			int y = mcoord.y;
			m_selected_box_sides = BOXNONESIDE;
			if (rect.left <= x && rect.left + border_thickness >= x)
				m_selected_box_sides |= BOXLEFT;

			if ((rect.right >= x && rect.right - border_thickness <= x) && !(m_selected_box_sides & BOXLEFT))
				m_selected_box_sides |= BOXRIGHT;

			if (rect.top >= y && rect.top - border_thickness <= y)
				m_selected_box_sides |= BOXTOP;

			if ((rect.bottom <= y && rect.bottom + border_thickness >= y) && !(m_selected_box_sides & BOXTOP))
				m_selected_box_sides |= BOXBOTTOM;

			m_box_click_delta = Point<int>(x - rect.left, rect.top - y);
			m_box_click_delta2 = Point<int>(rect.right - x, y - rect.bottom);

			if (m_selected_box_sides == BOXNONESIDE)
			{
				m_selected_box_state = BOXMOVING;
			}
			else
			{
				if (box->_has_flags(Box::RESIZEABLE))
					m_selected_box_state = BOXRESIZING;
			}

			return true;
		}
	}
	return false;
}

void plot::Subplot::boxprocess_leftup(const Point<int>& mouse_backend_coord)
{
	auto mcoord = backend_to_plot(mouse_backend_coord);
	m_selected_box = nullptr;
}

void plot::Subplot::boxprocess_mousemove(const Point<int>& mouse_backend_coord)
{

	Point<int> mcoord;
	if (m_selected_box->_has_flags(Box::BACKENDORIENTED))
	{
		mcoord.x = mouse_backend_coord.x;
		mcoord.y = _get_backend_size().h - mouse_backend_coord.y;
	}
	else
		mcoord = backend_to_plot(mouse_backend_coord);

	auto &rect = m_selected_box->_get_rect();
	auto snap_distance = m_selected_box->_getsnapdistance();
	int x = mcoord.x;
	int y = mcoord.y;
	if (m_selected_box_state == BOXMOVING)
	{
		if (!m_selected_box->_has_flags(Box::EXPANDVERT))
		{
			auto ny = y + m_box_click_delta.y;
			if (abs(ny - m_size.h) < snap_distance)
				ny = m_size.h;

			if (abs(ny - rect.Height()) < snap_distance)
				ny = rect.Height();
			rect.SetTop(ny);
		}

		if (!m_selected_box->_has_flags(Box::EXPANDHOR))
		{
			auto nx = x - m_box_click_delta.x;
			if (abs(nx) < snap_distance)
				nx = 0;
			if (abs(nx + rect.Width() - m_size.w) < snap_distance)
				nx = m_size.w - rect.Width();
			rect.SetLeft(nx);
		}
	}
	if (m_selected_box_state == BOXRESIZING)
	{
		int wr, hr, ms, v;
		wr = rect.Width();
		hr = rect.Height();
		ms = m_selected_box->_get_borderthickenss() * 2 + 5;

		if (!m_selected_box->_has_flags(Box::EXPANDVERT))
		{
			if (m_selected_box_sides & BOXTOP)
			{
				v = y + m_box_click_delta.y;
				if (abs(v - m_size.h) < snap_distance)
					v = m_size.h;
				if (v - rect.bottom >= ms)
					rect.SetTop(v, false);
				else
					rect.SetTop(rect.bottom + ms, false);
			}

			if (m_selected_box_sides & BOXBOTTOM)
			{
				v = y - m_box_click_delta2.y;
				if (abs(v) < snap_distance)
					v = 0;
				if (rect.top - v > ms)
					rect.SetBottom(v, false);
				else
					rect.SetBottom(rect.top - ms, false);
			}

		}

		if (!m_selected_box->_has_flags(Box::EXPANDHOR))
		{
			if (m_selected_box_sides & BOXLEFT)
			{
				v = x - m_box_click_delta.x;
				if (abs(v) < snap_distance)
					v = 0;
				if (rect.right - v > ms)
					rect.SetLeft(v, false);
				else
					rect.SetLeft(rect.right - ms, false);
			}

			if (m_selected_box_sides & BOXRIGHT)
			{
				v = x + m_box_click_delta2.x;
				if (abs(m_size.w - v) < snap_distance)
					v = m_size.w;
				if (v - rect.left > ms)
					rect.SetRight(v, false);
				else
					rect.SetRight(ms + rect.left, false);
			}
		}
	}

	Subplot::Validate(false);
}

void Subplot::StartPan(const Point<int> &pan_start_coord)
{
	DPRINTF("StartPan\n");
	assert(!m_panning);

	const Point<int> &p = pan_start_coord;

	for (auto scale : m_dependant_scales)
	{
		if (scale->_get_axis_dir() == AXIS_X)
			scale->StartPanAt((double)p.x / (double)m_size.w);

		if (scale->_get_axis_dir() == AXIS_Y)
			scale->StartPanAt((double)p.y / (double)m_size.h);
	}

	m_panning = true;
}

void Subplot::ProceedPan(const Point<int> &pan_start_coord)
{
	DPRINTF("ProceedPan\n");
	if (!m_panning)
		return;

	const Point<int> p = pan_start_coord;

	for (auto scale : m_dependant_scales)
	{
		if (scale->_get_axis_dir() == AXIS_X)
			scale->ProceedPanAt((double)p.x / (double)m_size.w);

		if (scale->_get_axis_dir() == AXIS_Y)
			scale->ProceedPanAt((double)p.y / (double)m_size.h);

		scale->Validate();
	}

	Validate();

	validate_other_plots();


}

void Subplot::EndPan()
{
	DPRINTF("EndPan\n");

	if (!m_panning)
		return;

	for (auto scale : m_dependant_scales)
	{
		if (scale->_get_axis_dir() == AXIS_X)
			scale->EndPanAt();

		if (scale->_get_axis_dir() == AXIS_Y)
			scale->EndPanAt();
	}

	emit_viewchanged();

	m_panning = false;
}
void plot::Subplot::validate_other_plots()
{
	//temporary
	std::vector<Subplot *> plots;
	for_each(m_dependant_scales.begin(), m_dependant_scales.end(), [&plots](Scale *scale) {
		auto ploti = scale->_get_plots();
		std::copy(ploti.begin(), ploti.end(), std::back_inserter(plots));
	});
	std::sort(plots.begin(), plots.end());
	plots.erase(std::unique(plots.begin(), plots.end()), plots.end());
	for_each(plots.begin(), plots.end(), [this](Subplot *plot) {if (plot != this) plot->Validate(); });

}
//
//void Subplot::StartZoomSelect(const Point<double> &zoom_sel_start_rel_coord)
//{
//	DPRINTF("Subplot::StartZoomSelect\n");
//	assert(!m_zoomselecting);
//
//	m_zoom_sel_start_rel_coord = zoom_sel_start_rel_coord;
//	m_zoomsel_switch = true;
//	m_zoomselecting = false;
//}
//
//void Subplot::ProceedZoomSelect(const Point<double> &zoom_sel_proceed_rel_coord)
//{
//	DPRINTF("Subplot::ProceedZoomSelect\n");
//
//	m_zoom_sel_end_rel_coord = zoom_sel_proceed_rel_coord;
//	int width, height, xd, yd;
//	auto bsize = _get_backend_size();
//	width = bsize.w;
//	height = bsize.h;
//
//	xd = abs((m_zoom_sel_end_rel_coord.x - m_zoom_sel_start_rel_coord.x) * width);
//	yd = abs((m_zoom_sel_end_rel_coord.y - m_zoom_sel_start_rel_coord.y) * height);
//
//	if (m_zoomselecting)
//	{
//		DrawZoomSelection();
//		if (xd < 10 || yd < 10)
//		{
//
//			m_zoomselecting = false;
//			m_zoomsel_switch = false;
//		}
//	}
//	else
//	{
//		if (m_zoomsel_switch && (xd > 10 && yd > 10))
//		{
//			m_zoomselecting = true;
//			m_zoomsel_switch = false;
//		}
//	}
//
//}
//
//void Subplot::EndZoomSelect()
//{
//	DPRINTF("Subplot::EndZoomSelect\n");
//	if (!m_zoomselecting && !m_zoomsel_switch)
//		return;
//
//	if (m_zoomselecting)
//	{
//		//for (auto area : m_areas)
//		//{
//		//	area->ZoomSelection(m_zoom_sel_start_rel_coord, m_zoom_sel_end_rel_coord);
//		//}
//		//for (auto space : m_spaces)
//		//{
//		//	space->ZoomSelection(m_start_rx_zsel, m_start_ry_zsel, m_end_rx_zsel, m_end_ry_zsel);
//		//}
//	}
//
////	RedrawPlot();
//
//	m_zoomselecting = false;
//	m_zoomsel_switch = false;
//
//	emit_viewchanged();
//}
//

void plot::Subplot::plot_resized()
{
	int w, h;
	auto backendsize = _get_backend_size();

	if (m_orientation == ORIENTATION_NORMAL)
	{
		m_size.w = backendsize.w;
		m_size.h = backendsize.h;
	}

	if (m_orientation == ORIENTATION_ROTATED)
	{
		m_size.w = backendsize.h;
		m_size.h = backendsize.w;
	}

	for (auto box : m_boxes)
		box->_ownersize(m_size);
}

const Point<int> plot::Subplot::backend_to_plot(const Point<int>& backendpoint)
{
	Point<int> p;

	if (m_orientation == ORIENTATION_NORMAL)
	{
		p.x = backendpoint.x;
		p.y = m_size.h - backendpoint.y;
	}

	if (m_orientation == ORIENTATION_ROTATED)
	{
		p.x = backendpoint.y;
		p.y = backendpoint.x;
	}

	return p;
}

const Size<int> plot::Subplot::backend_to_plot(const Size<int>& backendsize)
{
	Size<int> s;

	if (m_orientation == ORIENTATION_NORMAL)
	{
		s.w = backendsize.w;
		s.h = backendsize.h;
	}

	if (m_orientation == ORIENTATION_ROTATED)
	{
		s.w = backendsize.h;
		s.h = backendsize.w;
	}

	return s;
}

//void plot::Subplot::update_dependant_scales()
//{
//	std::vector<Scale *> &scales = m_dependant_scales;
//	scales.clear();
//	//for_each(m_areas.begin(), m_areas.end(), [&scales](Area *area)
//	//	{
//	//		auto axes = area->_get_axes();
//	//		for_each(axes.begin(), axes.end(), [&scales](Axis *axis) {if (axis->GetCommonScale() != nullptr) scales.push_back(axis->GetCommonScale()); });
//	//	}
//	//);
//
//	std::string tag("scalebox");
//	for (auto box : m_boxes)
//		if (box->_get_tag().compare(tag) == 0)
//			scales.push_back(dynamic_cast<Scale*>(box));
//
//	scales.erase(std::unique(scales.begin(), scales.end()), scales.end());
//}

