#pragma once
#include "SeriesTool_fb.h"
#include "Series.h"

class SeriesTool : public SeriesTool_fb
{
private:
	plot::Series *m_series;

	virtual void m_checkBox_nameOnCheckBox(wxCommandEvent& event) override;
	virtual void m_bpButton_fithorOnButtonClick(wxCommandEvent& event) override;
	virtual void m_bpButton_fitvertOnButtonClick(wxCommandEvent& event) override;
	virtual void m_bpButton_fitOnButtonClick(wxCommandEvent& event) override;
	virtual void m_bpButton_deleteOnButtonClick(wxCommandEvent& event) override;
	virtual void m_slider_line_weightOnScroll(wxScrollEvent& event) override;
	virtual void m_slider_marks_sizeOnScroll(wxScrollEvent& event) override;
	virtual void m_checkBox_line_visibleOnCheckBox(wxCommandEvent& event) override;
	virtual void m_checkBox_marks_visibleOnCheckBox(wxCommandEvent& event)	override;

	void m_combo_line_colourOnSelect(wxCommandEvent &event);
	void m_combo_marks_colourOnSelect(wxCommandEvent &event);
	void m_combo_marks_styleOnSelect(wxCommandEvent &event);
	void m_combo_line_styleOnSelect(wxCommandEvent &event);

	//wxDECLARE_EVENT_TABLE();
protected:

public:

	SeriesTool(wxWindow* parent, plot::Series *series, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1), long style = wxTAB_TRAVERSAL);
	virtual ~SeriesTool();

};
