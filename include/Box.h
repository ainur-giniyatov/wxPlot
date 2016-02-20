#pragma once
#include "plot_defs.h"

namespace plot
{
	enum BOXSTATE
	{
		BOXIDLE,
		BOXMOVING,
		BOXRESIZING
	};

	enum BOXSIDES
	{
		BOXNONESIDE = 0,
		BOXTOP = (1 << 0),
		BOXRIGHT = (1 << 1),
		BOXBOTTOM = (1 << 2),
		BOXLEFT = (1 << 3)
	};

	class DLLIMPEXP_PLOTLIB Plot;

	class DLLIMPEXP_PLOTLIB Box
	{
	public:
		enum {
			MOVEABLE = (1 << 0),
			RESIZEABLE = (1 << 1),
			EXPANDVERT = (1 << 2),
			EXPANDHOR = (1 << 3)
		};

		Box();
		virtual ~Box();

		virtual void Render(void *) = 0;

		auto &_get_rect() { return m_rect; }
		bool _has_flags(int flags) { return (m_flags & flags) == flags; }
		int _get_borderthickenss() { return m_border_thickness; }
		virtual void _ownersize(int w, int h);
		virtual void _setowner(Plot *plot) { m_owner = plot; };
		static int _getsnapdistance() { return s_snapdistance; }
	protected:
		int m_flags;
		Rect<int> m_rect;
		int m_border_thickness;
		Plot *m_owner;
	private:
		Box *m_stickbox[4];//left top right bottom
		static const int s_snapdistance;
	};


	class TitleBox : public Box
	{
	public:
		TitleBox();
		virtual ~TitleBox();
	protected:
		virtual void _setowner(Plot *plot) override;
		const char *m_title;
	};
}