#pragma once
#include <wx/graphics.h>
#include "../Marker.h"

namespace plot
{

	class DLLIMPEXP_PLOTLIB wxMarker : public Marker
	{
	public:
		wxMarker();
		virtual ~wxMarker();
		virtual wxMarker *Clone() = 0;
		void InitStyleAndColour(wxGraphicsContext *gc);

		virtual int _getid() = 0;
	protected:
		
	private:
	};

	class DLLIMPEXP_PLOTLIB wxMarkerCircle : public wxMarker
	{
	public:
		wxMarkerCircle();
		wxMarkerCircle(int border_color_indx, int fill_color_indx, int size = 4, bool vsbl = true);
		virtual wxMarker *Clone() override;
		virtual ~wxMarkerCircle();
		virtual void Render(void *, Point<int> &coord) override;
		virtual bool _isspotted(Point<int> &mouse_coord, Point<int> &marker_coord) override;
		virtual int _getid() override { return s_id; };
	protected:
	private:
		static const int s_id;
	};

	class DLLIMPEXP_PLOTLIB wxMarkerSquare : public wxMarker
	{
	public:
		wxMarkerSquare();
		wxMarkerSquare(int border_color_indx, int fill_color_indx, int size = 4, bool vsbl = true);
		virtual wxMarker *Clone() override;
		virtual ~wxMarkerSquare();
		virtual void Render(void *, Point<int> &coord) override;
		virtual bool _isspotted(Point<int> &mouse_coord, Point<int> &marker_coord) override;
		virtual int _getid() override { return s_id; };
	protected:
	private:
		static const int s_id;
	};

	class DLLIMPEXP_PLOTLIB wxMarkerRomb : public wxMarker
	{
	public:
		wxMarkerRomb();
		wxMarkerRomb(int border_color_indx, int fill_color_indx, int size = 4, bool vsbl = true);
		virtual wxMarker *Clone() override;
		virtual ~wxMarkerRomb();
		virtual void Render(void *, Point<int> &coord) override;
		virtual bool _isspotted(Point<int> &mouse_coord, Point<int> &marker_coord) override;
		virtual int _getid() override { return s_id; };
	protected:
	private:
		static const int s_id;
		wxPoint2DDouble m_vertexes[5];
	};
}