#ifndef B_FIT_PNG_H
#define B_FIT_PNG_H

#include <wx/mstream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

static const unsigned char b_fit_png[] = 
{
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 
	0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 
	0x00, 0x00, 0x00, 0x10, 0x08, 0x06, 0x00, 0x00, 0x00, 0x1F, 
	0xF3, 0xFF, 0x61, 0x00, 0x00, 0x00, 0x6D, 0x49, 0x44, 0x41, 
	0x54, 0x78, 0xDA, 0x63, 0x64, 0xA0, 0x10, 0x30, 0x42, 0xE9, 
	0xFF, 0x48, 0x6C, 0x92, 0x0D, 0xF8, 0x0F, 0x63, 0x7F, 0x40, 
	0xB0, 0xC1, 0x40, 0x00, 0xC9, 0x50, 0x5C, 0x72, 0x28, 0x2E, 
	0x00, 0x29, 0x12, 0x40, 0x75, 0x19, 0x36, 0xF0, 0xFF, 0x03, 
	0x01, 0x03, 0x60, 0xAE, 0xC2, 0x66, 0x08, 0xBA, 0x3A, 0x4C, 
	0x2F, 0x08, 0xE0, 0x0E, 0x17, 0x38, 0x1F, 0xDD, 0x00, 0x06, 
	0x42, 0x36, 0xE2, 0x0B, 0x64, 0x62, 0x62, 0x01, 0x6F, 0x0C, 
	0xA1, 0x78, 0x81, 0x62, 0x17, 0x50, 0x1C, 0x06, 0xD4, 0x8A, 
	0x05, 0x5C, 0xDE, 0x81, 0x1B, 0x82, 0x37, 0x1D, 0x20, 0xAB, 
	0x24, 0x39, 0x25, 0x32, 0x90, 0x01, 0x90, 0xBD, 0x40, 0x16, 
	0xC0, 0xE6, 0x02, 0x92, 0xD8, 0x00, 0x8E, 0x7F, 0x40, 0x10, 
	0xE6, 0x5D, 0x3F, 0x19, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 
	0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82, 
};

wxBitmap& b_fit_png_to_wx_bitmap()
{
	static wxMemoryInputStream memIStream( b_fit_png, sizeof( b_fit_png ) );
	static wxImage image( memIStream, wxBITMAP_TYPE_PNG );
	static wxBitmap bmp( image );
	return bmp;
};


#endif //B_FIT_PNG_H
