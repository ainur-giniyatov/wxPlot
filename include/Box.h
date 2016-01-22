#pragma once

#include "plot_defs.h"
#include "pevent.h"
#include "Series.h"
#include "Data.h"
#include "Plot.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB DataNoType;
	class DLLIMPEXP_PLOTLIB Series;
	class DLLIMPEXP_PLOTLIB Plot;
	class DLLIMPEXP_PLOTLIB PEventHandler;
	class DLLIMPEXP_PLOTLIB PEvent;
	class DLLIMPEXP_PLOTLIB PEventSeriesAdded;

	class DLLIMPEXP_PLOTLIB Box: public PEventHandler
	{
	public:

		enum ResizeOnSide {
			RESONSIDE_LEFT = (1 << 0),
			RESONSIDE_RIGHT = (1 << 1),
			RESONSIDE_TOP = (1 << 2),
			RESONSIDE_BOTTOM = (1 << 3)
		};

		enum StickedFlag {
			STICKEDTO_NONE = 0,
			STICKEDTO_RIGHT = (1 << 0),
			STICKEDTO_LEFT = (1 << 1),
			STICKEDTO_TOP = (1 << 2),
			STICKEDTO_BOTTOM = (1 << 3),
			STICKEDTO_HOR_CENTER = (1 << 4),
			STICKEDTO_VER_CENTER = (1 << 5)
		};


		Box(Plot *owner);
		virtual ~Box();

		virtual void Render(void *) = 0;

		bool CheckIsMouseInside(int mx, int my);
		virtual void MouseMove(int mx, int my);
		virtual void MouseLeftDown(int mx, int my);
		virtual void MouseLeftUp(int mx, int my);
		virtual void MouseRightDown(int mx, int my);
		virtual void MouseRightUp(int mx, int my);


		virtual void Sizing();

		void BringToFront();
	protected:
		Plot *m_owner;
		Rect<int> m_rect;

		int m_border_thickness;

		bool m_isresizable;
		bool m_ismovable;
		bool m_snaptoborder;
		bool m_snaptocenter;
		bool m_snaptoeachother;
		bool m_sticky;
		int m_sticked_to;

		int m_flag_move_dir;
		int m_flag_expand_dir;
		int m_snap_offset;

		bool m_ontop;

		
	private:

		int m_snap_distance;

		void start_moving(const Point<int>& mcoords);
		void proceed_moving(const Point<int>& mcoords);
		void end_moving();
		bool m_ismoving;
		Point<int> m_start_move_mouse_coords;
		Point<int> m_start_move_initial_p1;

		bool m_isresizing;
		void start_resizing(const Point<int> &mcoords);
		void proceed_resizing(const Point<int> &mcoords);
		void end_resizing();
		int m_flag_resonside;


		//helper funcs
		bool ismouseatpoint(const Point<int>& mouse_p, const Point<int>& p, int ar);//mouse x, mouse y, point x, point y, active radius

	};


	class DLLIMPEXP_PLOTLIB TitleBox : public Box
	{
	public:
		TitleBox(Plot *owner);
		virtual ~TitleBox();

		//	virtual void Render(wxGraphicsContext *gc) override;
		virtual void Sizing() override;
	protected:
	private:
	};

	class DLLIMPEXP_PLOTLIB LegendsBox : public Box
	{
	public:
		LegendsBox(Plot *owner);
		virtual ~LegendsBox();
		void AddSeries(Series *series);
		void RemoveSeries(Series *series);

		//virtual void Sizing() override;

		struct LegendItem
		{
			Series *m_series;
			Rect<int> m_rect;
		};

	protected:
		std::vector<LegendItem *> m_items;

	private:
		//virtual void MouseRightUp(int mx, int my) override;
		void OnSeriesAdded(PEvent& event);
		void OnSeriesNameChanged(PEvent& event);
	};
}