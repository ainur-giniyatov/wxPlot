#ifndef WXCOLORCOMBOBOX_H
#define WXCOLORCOMBOBOX_H

#include <wx/odcombo.h>


class wxColorComboBox : public wxOwnerDrawnComboBox
{
    public:
        wxColorComboBox(wxWindow *parent, wxWindowID id);
        virtual ~wxColorComboBox();
        int GetColourSelection();
        void SetColorSelection(int indx);
    protected:
    private:
        virtual void OnDrawBackground(wxDC& dc, const wxRect& rect, int item, int flags) const;

};

#endif // WXCOLORCOMBOBOX_H
