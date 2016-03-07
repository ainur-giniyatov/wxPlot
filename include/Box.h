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

	class DLLIMPEXP_PLOTLIB Subplot;

	class DLLIMPEXP_PLOTLIB Box
	{
	public:
		enum {
			MOVEABLE = (1 << 0),
			RESIZEABLE = (1 << 1),
			EXPANDVERT = (1 << 2),
			EXPANDHOR = (1 << 3),
			BACKENDORIENTED = (1 << 4)
		};

		Box(int flags = MOVEABLE | RESIZEABLE);
		virtual ~Box();

		virtual void Render(void *) = 0;

		auto &_get_rect() { return m_rect; }
		bool _has_flags(int flags) { return (m_flags & flags) == flags; }
		int _get_borderthickenss() { return m_border_thickness; }
		virtual void _ownersize(const Size<int> &ownersize);
		virtual void _setowner(Subplot *subplot) { m_owner = subplot; };
		static int _getsnapdistance() { return s_snapdistance; }

	protected:
		int m_flags;
		Rect<int> m_rect;
		int m_border_thickness;
		Subplot *m_owner;

	private:
		Box *m_stickbox[4];//left top right bottom
		static const int s_snapdistance;
	};


	class TitleBox : public Box
	{
	public:
		TitleBox(int flags = MOVEABLE);
		virtual ~TitleBox();
	protected:
		virtual void _setowner(Subplot *subplot) override;
		const char *m_title;
	};
}