#include <algorithm>
#include <math.h>
#include <assert.h>
#include <string>
#include <string.h>
#include <vector>
#include <iterator>

#include "Plot.h"

using namespace plot;

static char *s_plotname = "plot";

Plot::Plot(const char *plotname)
{
	
	DPRINTF("Plot ctor\n");
	m_panning = false;
	m_zoomselecting = false;
	m_zoomsel_switch = false;
	m_orientation = ORIENTATION_ROTATED;
	m_is_data_view_modified = true;

	if (plotname == NULL)
		m_plot_name = s_plotname;
	else
	{
		m_plot_name = (char *)malloc(strlen(plotname) + 1);
		strcpy(m_plot_name, plotname);
	}

	m_lbaction = LBA_ZOOMSELECT;

	m_selected_box = nullptr;
	m_selected_box_state = BOXIDLE;
	m_selected_box_sides = BOXNONESIDE;

}

void Plot::SetPlotName(const char * plotname)
{
	if (m_plot_name != NULL && m_plot_name != s_plotname)
		free(m_plot_name);

	if (plotname == NULL)
		m_plot_name = s_plotname;
	else
	{
		m_plot_name = (char *)malloc(strlen(plotname) + 1);
		strcpy(m_plot_name, plotname);
	}
}

void Plot::AddArea(Area * area)
{
	if (std::none_of(m_areas.begin(), m_areas.end(), [area](Area *a) {return area == a; }))
	{
		m_areas.push_back(area);
		area->_setowner(this);
		
		_refresh_dependant_scales();
	}
}
void Plot::RemoveArea(Area * area)
{
	assert(area->_getowner() == this);
	auto tormv = std::remove(m_areas.begin(), m_areas.end(), area);
	if (tormv != m_areas.end())
	{
		m_areas.erase(tormv, m_areas.end());
		_refresh_dependant_scales();
	}
}

void Plot::DeleteArea(Area * area)
{
	RemoveArea(area);
	delete area;
}

void Plot::Clear(bool update)
{
	assert(0);
}

Plot::~Plot()
{
	DPRINTF("Plot dtor\n");
	std::vector<Area *> areas(m_areas);
	for (auto area : areas)
	{
		delete area;
	}

	if (m_plot_name != NULL && m_plot_name != s_plotname)
		free(m_plot_name);

	for (auto box : m_boxes)
		delete box;


}


void plot::Plot::Validate(bool refresh_buffer)
{
	if(refresh_buffer)
		_SetViewModifiedFlag();

	RedrawPlot();
}

//void Plot::RemoveBox(Box * box)
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
//void Plot::DeleteBox(Box * box)
//{
//	RemoveBox(box);
//	delete box;
//}
//
void Plot::AddBox(Box *box)
{
	if (std::any_of(m_boxes.begin(), m_boxes.end(), [box](Box *b) { return b == box; }))
	{
		return;
	}

	m_boxes.push_back(box);
	box->_setowner(this);
	int w, h;
	GetSize(&w, &h);
	box->_ownersize(w, h);
	Validate(false);
}
//
//void plot::Plot::ArrangeBoxes()
//{
//	for_each(m_boxes.begin(), m_boxes.end(), [](Box *box) {box->Sizing(); });
//}


void plot::Plot::Fit(int axis_mask)
{
	//std::vector<Scale *> scales;

	////collect all common scales and remove duplicates
	//for (auto area : m_areas)
	//	for (auto axis : area->_get_axes())
	//		if (axis->GetCommonScale() != nullptr && ((1 << axis->_get_axis_dir()) & axis_mask))
	//			scales.push_back(axis->GetCommonScale());
	//scales.erase(std::unique(scales.begin(), scales.end()), scales.end());

	//for (int xd = 0; xd < 3; xd++)
	//	if ((1 << xd) & axis_mask)
	//	{
	//		double vmax = 0, vmin = 0;
	//		bool data_aval = false;

	//		for (auto scale : scales)
	//		{
	//			if (xd != scale->_get_axis_dir())
	//				continue;

	//			for (auto axis : scale->GetAxes())
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

	//		for (auto scale : scales)
	//		{
	//			if (xd != scale->_get_axis_dir())
	//				continue;

	//			for (auto axis : scale->GetAxes())
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
	//			scale->RedrawDependantPlots(false);
	//		}
	//	}
	//
	//	for (auto scale : scales)
	//		scale->RedrawDependantPlots();
	
}

void Plot::_SetViewModifiedFlag()
{
	m_is_data_view_modified = true;
}

void plot::Plot::_refresh_dependant_scales()
{
	//collect all scales and make unique
	m_dependant_scales.clear();
	auto & ds = m_dependant_scales;
	for_each(m_areas.begin(), m_areas.end(), [&ds](Area *area) {
		auto axes = area->_get_axes();
		for_each(axes.begin(), axes.end(), [&ds](Axis *axis) {
			if (axis->_getcommonscale() != nullptr)
				ds.push_back(axis->_getcommonscale());
		});
	});

	ds.erase(std::unique(ds.begin(), ds.end()), ds.end());
}

void Plot::StartPan(const Point<double> &pan_start_rel_coord)
{
	DPRINTF("StartPan\n");
	assert(!m_panning);

	for (auto scale : m_dependant_scales)
	{
		if (scale->_get_axis_dir() == AXIS_X)
			scale->StartPanAt(pan_start_rel_coord.x);

		if (scale->_get_axis_dir() == AXIS_Y)
			scale->StartPanAt(pan_start_rel_coord.y);
	}
	m_panning = true;
}

void Plot::ProceedPan(const Point<double> &pan_proceed_rel_coord)
{
	DPRINTF("ProceedPan\n");
	if (!m_panning)
		return;

	for (auto scale : m_dependant_scales)
	{
		if (scale->_get_axis_dir() == AXIS_X)
			scale->ProceedPanAt(pan_proceed_rel_coord.x);

		if (scale->_get_axis_dir() == AXIS_Y)
			scale->ProceedPanAt(pan_proceed_rel_coord.y);

		scale->Validate();
	}

	Validate();

	std::vector<Plot *> plots;
	for_each(m_dependant_scales.begin(), m_dependant_scales.end(), [&plots](Scale *scale) {
		auto ploti = scale->_get_plots();
		std::copy(ploti.begin(), ploti.end(), std::back_inserter(plots)); 
	});
	plots.erase(std::unique(plots.begin(), plots.end()), plots.end());
	for_each(plots.begin(), plots.end(), [this](auto plot) {if(plot != this) plot->Validate(); });
	

}

void Plot::EndPan()
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

void Plot::StartZoomSelect(const Point<double> &zoom_sel_start_rel_coord)
{
	DPRINTF("Plot::StartZoomSelect\n");
	assert(!m_zoomselecting);

	m_zoom_sel_start_rel_coord = zoom_sel_start_rel_coord;
	m_zoomsel_switch = true;
	m_zoomselecting = false;
}

void Plot::ProceedZoomSelect(const Point<double> &zoom_sel_proceed_rel_coord)
{
	DPRINTF("Plot::ProceedZoomSelect\n");

	m_zoom_sel_end_rel_coord = zoom_sel_proceed_rel_coord;
	int width, height, xd, yd;
	GetSize(&width, &height);

	xd = abs((m_zoom_sel_end_rel_coord.x - m_zoom_sel_start_rel_coord.x) * width);
	yd = abs((m_zoom_sel_end_rel_coord.y - m_zoom_sel_start_rel_coord.y) * height);

	if (m_zoomselecting)
	{
		DrawZoomSelection();
		if (xd < 10 || yd < 10)
		{
		
			m_zoomselecting = false;
			m_zoomsel_switch = false;
		}
	}
	else
	{
		if (m_zoomsel_switch && (xd > 10 && yd > 10))
		{
			m_zoomselecting = true;
			m_zoomsel_switch = false;
		}
	}

}

void Plot::EndZoomSelect()
{
	DPRINTF("Plot::EndZoomSelect\n");
	if (!m_zoomselecting && !m_zoomsel_switch)
		return;

	if (m_zoomselecting)
	{
		//for (auto area : m_areas)
		//{
		//	area->ZoomSelection(m_zoom_sel_start_rel_coord, m_zoom_sel_end_rel_coord);
		//}
		//for (auto space : m_spaces)
		//{
		//	space->ZoomSelection(m_start_rx_zsel, m_start_ry_zsel, m_end_rx_zsel, m_end_ry_zsel);
		//}
	}

//	RedrawPlot();

	m_zoomselecting = false;
	m_zoomsel_switch = false;

	emit_viewchanged();
}

void Plot::Zoom(const Point<double> &zoom_wheel_rel_coord, double xfactor, double yfactor)
{
	DPRINTF("Zoom wheel\n");

	//for (auto area : m_areas)
	//	area->Zoom(zoom_wheel_rel_coord, xfactor, yfactor);

}

void plot::Plot::plot_resized()
{
	int w, h;
	GetSize(&w, &h);
	for (auto box : m_boxes)
		box->_ownersize(w, h);
}

//void plot::Plot::update_dependant_scales()
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

