#ifndef WXMARKSTYLECOMBOBOX_H
#define WXMARKSTYLECOMBOBOX_H

#include <wx/odcombo.h>


class wxMarkStyleComboBox : public wxOwnerDrawnComboBox
{
    public:
        wxMarkStyleComboBox(wxWindow *parent, wxWindowID id);
        virtual ~wxMarkStyleComboBox();
        void SetMarkStyleSelection(int indx);
        void SetColourIndex(int color_indx);
        void SetMarkSize(int mark_size);
    protected:
    private:
        virtual void OnDrawBackground(wxDC& dc, const wxRect& rect, int item, int flags) const;
        int m_colour_indx;
        int m_mark_size;
};

#endif // WXMARKSTYLECOMBOBOX_H
