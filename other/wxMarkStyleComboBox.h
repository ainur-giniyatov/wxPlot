#ifndef WXMARKSTYLECOMBOBOX_H
#define WXMARKSTYLECOMBOBOX_H

#include <vector>
#include <wx/odcombo.h>
#include "wx/wxMarker.h"

class wxMarkStyleComboBox : public wxOwnerDrawnComboBox
{
    public:
        wxMarkStyleComboBox(wxWindow *parent, wxWindowID id);
        virtual ~wxMarkStyleComboBox();
        void SetMarkStyleSelection(plot::wxMarker *marker);
		plot::wxMarker *GetSelectedMarker();
		void CopyMarkerAttribs(plot::wxMarker *marker);
    protected:
    private:
        virtual void OnDrawBackground(wxDC& dc, const wxRect& rect, int item, int flags) const;
        

		std::vector<plot::wxMarker *> m_markers;
};

#endif // WXMARKSTYLECOMBOBOX_H
