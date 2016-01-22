#ifndef WXLINESTYLECOMBOBOX_H
#define WXLINESTYLECOMBOBOX_H

//#include "../colorbase.h"
#include <wx/odcombo.h>

class wxLineStyleComboBox : public wxOwnerDrawnComboBox
{
    public:
        wxLineStyleComboBox(wxWindow *parent, wxWindowID id);
        virtual ~wxLineStyleComboBox();
        int GetPenStyleSelection();
        void SetPenStyleSelection(int indx);
        void SetColourIndex(int colour_indx);
        void SetWidth(int width);
    protected:
    private:
        virtual void OnDrawBackground(wxDC& dc, const wxRect& rect, int item, int flags) const;
    protected:
    private:
        int m_colour_indx;
        int m_width;
};

#endif // WXLINESTYLECOMBOBOX_H
