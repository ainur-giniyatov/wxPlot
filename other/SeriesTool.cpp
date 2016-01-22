#include "SeriesTool.h"


void SeriesTool::m_checkBox_nameOnCheckBox(wxCommandEvent & event)
{
	m_series->GetRenderer()->SetVisible(event.IsChecked());
	m_series->SeriesUpdated();
}

void SeriesTool::m_bpButton_fithorOnButtonClick(wxCommandEvent & event)
{
	m_series->GetData(AXIS_X)->Fit();
}

void SeriesTool::m_bpButton_fitvertOnButtonClick(wxCommandEvent & event)
{
	m_series->GetData(AXIS_Y)->Fit();
}

void SeriesTool::m_bpButton_fitOnButtonClick(wxCommandEvent & event)
{
	m_series->Fit();
}

void SeriesTool::m_bpButton_deleteOnButtonClick(wxCommandEvent & event)
{
	plot::Plot *plotwindow;
	plotwindow = m_series->GetOwner()->GetOwner();
	m_series->GetOwner()->DeleteSeries(m_series);
	GetParent()->Destroy();
	plotwindow->_SetViewModifiedFlag();
	plotwindow->RedrawPlot();
	
}

void SeriesTool::m_slider_line_weightOnScroll(wxScrollEvent & event)
{
	m_series->GetRenderer()->SetLineThickness(event.GetPosition());
	m_series->SeriesUpdated();
}

void SeriesTool::m_slider_marks_sizeOnScroll(wxScrollEvent & event)
{
	m_series->GetRenderer()->SetMarkerSize(event.GetPosition());
	m_series->SeriesUpdated();
}

void SeriesTool::m_checkBox_line_visibleOnCheckBox(wxCommandEvent & event)
{
	m_series->GetRenderer()->SetLineVisible(event.IsChecked());
	m_series->SeriesUpdated();
}

void SeriesTool::m_checkBox_marks_visibleOnCheckBox(wxCommandEvent & event)
{
	m_series->GetRenderer()->SetMarksVisible(event.IsChecked());
	m_series->SeriesUpdated();
}

void SeriesTool::m_combo_line_colourOnSelect(wxCommandEvent & event)
{
	DPRINTF("SeriesTool::m_combo_line_colourOnSelect\n");
	m_series->GetRenderer()->SetLineColourIndex(event.GetSelection());
	m_series->SeriesUpdated();
}

void SeriesTool::m_combo_marks_colourOnSelect(wxCommandEvent & event)
{
	DPRINTF("SeriesTool::m_combo_marks_colourOnSelect\n");
	m_series->GetRenderer()->SetMarkerColourIndex(event.GetSelection());
	m_series->SeriesUpdated();
}

void SeriesTool::m_combo_marks_styleOnSelect(wxCommandEvent & event)
{
	DPRINTF("SeriesTool::m_combo_marks_styleOnSelect\n");
	m_series->GetRenderer()->SetMarkerStyle((MARKER_STYLES)(int)event.GetClientData());
	m_series->SeriesUpdated();
}

void SeriesTool::m_combo_line_styleOnSelect(wxCommandEvent & event)
{
}

SeriesTool::SeriesTool(wxWindow * parent, plot::Series *series, wxWindowID id, const wxPoint & pos, const wxSize & size, long style):SeriesTool_fb(parent, id, pos, size, style)
{
	m_series = series;

	m_checkBox_name->SetLabel(m_series->GetSeriesName());
	m_checkBox_name->SetValue(m_series->GetRenderer()->GetVisible());
	m_slider_line_weight->SetValue(m_series->GetRenderer()->GetLineThickness());
	m_slider_marks_size->SetValue(m_series->GetRenderer()->GetMarkerSize());
	m_checkBox_line_visible->SetValue(m_series->GetRenderer()->GetLineVisible());
	m_checkBox_marks_visible->SetValue(m_series->GetRenderer()->GetMarksVisible());
	m_combo_line_colour->SetColorSelection(m_series->GetRenderer()->GetLineColourIndex());
	m_combo_marks_colour->SetColorSelection(m_series->GetRenderer()->GetMarkerColourIndex());
	m_combo_marks_style->SetMarkStyleSelection(m_series->GetRenderer()->GetMarkerStyle());


	m_combo_line_colour->Connect(wxEVT_COMBOBOX, (wxObjectEventFunction)&SeriesTool::m_combo_line_colourOnSelect, nullptr, this);
	m_combo_marks_colour->Connect(wxEVT_COMBOBOX, (wxObjectEventFunction)&SeriesTool::m_combo_marks_colourOnSelect, nullptr, this);
	m_combo_marks_style->Connect(wxEVT_COMBOBOX, (wxObjectEventFunction)&SeriesTool::m_combo_marks_styleOnSelect, nullptr, this);
}

SeriesTool::~SeriesTool()
{
}
