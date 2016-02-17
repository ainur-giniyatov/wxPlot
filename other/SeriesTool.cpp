#include "SeriesTool.h"


void SeriesTool::m_checkBox_nameOnCheckBox(wxCommandEvent & event)
{
	if (m_series == nullptr)
		return;

	m_series->GetRenderer()->SetVisible(event.IsChecked());
	m_series->SeriesUpdated();
}

void SeriesTool::m_bpButton_fithorOnButtonClick(wxCommandEvent & event)
{
	if (m_series == nullptr)
		return;

	m_series->GetData(AXIS_X)->Fit();
}

void SeriesTool::m_bpButton_fitvertOnButtonClick(wxCommandEvent & event)
{
	if (m_series == nullptr)
		return;

	m_series->GetData(AXIS_Y)->Fit();
}

void SeriesTool::m_bpButton_fitOnButtonClick(wxCommandEvent & event)
{
	if (m_series == nullptr)
		return;

	//m_series->Fit();
	assert(0);
}

void SeriesTool::m_bpButton_deleteOnButtonClick(wxCommandEvent & event)
{
	if (m_series == nullptr)
		return;

	plot::Plot *plotwindow;
	plotwindow = m_series->GetOwner()->GetOwner();
	m_series->GetOwner()->DeleteSeries(m_series);
	
	
	
	plotwindow->_SetViewModifiedFlag();
	plotwindow->RedrawPlot();
	
	SetSelectedSeries(nullptr);
}

void SeriesTool::m_slider_line_weightOnScroll(wxScrollEvent & event)
{
	if (m_series == nullptr)
		return;

	m_series->GetRenderer()->GetLine()->SetThickness(event.GetPosition());
	m_series->SeriesUpdated();
}

void SeriesTool::m_slider_marks_sizeOnScroll(wxScrollEvent & event)
{
	if (m_series == nullptr)
		return;

	m_series->GetRenderer()->GetMarker()->SetSize(event.GetPosition());
	m_series->SeriesUpdated();

	m_combo_marks_style->CopyMarkerAttribs((plot::wxMarker*)m_series->GetRenderer()->GetMarker());
}

void SeriesTool::m_checkBox_line_visibleOnCheckBox(wxCommandEvent & event)
{
	if (m_series == nullptr)
		return;

	m_series->GetRenderer()->GetLine()->SetVisible(event.IsChecked());
	m_series->SeriesUpdated();
}

void SeriesTool::m_checkBox_marks_visibleOnCheckBox(wxCommandEvent & event)
{
	if (m_series == nullptr)
		return;

	m_series->GetRenderer()->GetMarker()->SetVisible(event.IsChecked());
	m_series->SeriesUpdated();
}

void SeriesTool::m_combo_line_colourOnSelect(wxCommandEvent & event)
{
	DPRINTF("SeriesTool::m_combo_line_colourOnSelect\n");
	if (m_series == nullptr)
		return;
	
	m_series->GetRenderer()->GetLine()->SetColourIndex(event.GetSelection());
	m_series->SeriesUpdated();

}

void SeriesTool::m_combo_marks_colourOnSelect(wxCommandEvent & event)
{
	DPRINTF("SeriesTool::m_combo_marks_colourOnSelect\n");
	if (m_series == nullptr)
		return;
	

	m_series->GetRenderer()->GetMarker()->SetFillColourIndex(event.GetSelection());
	m_series->SeriesUpdated();

	m_combo_marks_style->CopyMarkerAttribs((plot::wxMarker*)m_series->GetRenderer()->GetMarker());
}

void SeriesTool::m_combo_marks_styleOnSelect(wxCommandEvent & event)
{
	DPRINTF("SeriesTool::m_combo_marks_styleOnSelect\n");
	if (m_series == nullptr)
		return;

	m_series->GetRenderer()->SetMarker(m_combo_marks_style->GetSelectedMarker()->Clone());
	m_series->SeriesUpdated();
}

void SeriesTool::m_combo_line_styleOnSelect(wxCommandEvent & event)
{
}

SeriesTool::SeriesTool(wxWindow * parent, wxWindowID id, const wxPoint & pos, const wxSize & size, long style):SeriesTool_fb(parent, id, pos, size, style)
{
	SetSelectedSeries(nullptr);

	m_combo_line_colour->Connect(wxEVT_COMBOBOX, (wxObjectEventFunction)&SeriesTool::m_combo_line_colourOnSelect, nullptr, this);
	m_combo_marks_colour->Connect(wxEVT_COMBOBOX, (wxObjectEventFunction)&SeriesTool::m_combo_marks_colourOnSelect, nullptr, this);
	m_combo_marks_style->Connect(wxEVT_COMBOBOX, (wxObjectEventFunction)&SeriesTool::m_combo_marks_styleOnSelect, nullptr, this);
}

SeriesTool::~SeriesTool()
{
}

void SeriesTool::SetSelectedSeries(plot::Series * series)
{
	m_series = series;

	if (m_series != nullptr)

	{
		Enable();
		m_checkBox_name->SetLabel(m_series->GetSeriesName());
		m_checkBox_name->SetValue(m_series->GetRenderer()->GetVisible());

		m_slider_line_weight->SetValue(m_series->GetRenderer()->GetLine()->GetThickness());

		m_checkBox_line_visible->SetValue(m_series->GetRenderer()->GetLine()->GetVisible());

		m_combo_line_colour->SetColorSelection(m_series->GetRenderer()->GetLine()->GetColourIndex());

		m_slider_marks_size->SetValue(m_series->GetRenderer()->GetMarker()->GetSize());

		m_checkBox_marks_visible->SetValue(m_series->GetRenderer()->GetMarker()->GetVisible());

		m_combo_marks_colour->SetColorSelection(m_series->GetRenderer()->GetMarker()->GetFillColourIndex());

		m_combo_marks_style->SetMarkStyleSelection((plot::wxMarker *)(m_series->GetRenderer()->GetMarker()));
		Refresh();
	}
	else
	{
		Disable();
		m_checkBox_name->SetLabel("NA");
		m_checkBox_name->SetValue(false);

		m_slider_line_weight->SetValue(0);

		m_checkBox_line_visible->SetValue(false);

		m_combo_line_colour->SetColorSelection(0);

		m_slider_marks_size->SetValue(1);

		m_checkBox_marks_visible->SetValue(false);

		m_combo_marks_colour->SetColorSelection(0);

		Refresh();
	}
}
