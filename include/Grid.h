#pragma once
#include "plot_defs.h"
#include "Series.h"
//#include "Axis.h"
//#include "Area.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB Series;
	//class DLLIMPEXP_PLOTLIB Axis;
	//class DLLIMPEXP_PLOTLIB Area;
	template <class T> class DLLIMPEXP_PLOTLIB ValueAdaptor;

	class DLLIMPEXP_PLOTLIB Grid
	{
	public:
		/*constructor invokes owner_space->SetGrid(this)*/
		Grid();
		virtual ~Grid();

		virtual void Render(void *) = 0;
		void GridUpdated();

//		void _setowner(Area *area) { m_owner = area; }
	protected:
//		Area *m_owner;
	private:
	};
}