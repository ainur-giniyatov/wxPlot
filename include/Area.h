#pragma once
#include <vector>

#include "plot_defs.h"
#include "Series.h"
#include "Axis.h"

#include "Plot.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB DataNoType;
	class DLLIMPEXP_PLOTLIB Series;
	class DLLIMPEXP_PLOTLIB Axis;
	class DLLIMPEXP_PLOTLIB Plot;
	class DLLIMPEXP_PLOTLIB Grid;

	class DLLIMPEXP_PLOTLIB Area
	{
	public:
		Area(int dim_num);
		virtual ~Area();

		Plot *GetOwner() { return m_owner_plot; }

		Grid *GetGrid() { return m_grid; }
		void SetGrid(Grid *grid);

		void AddSeries(Series *series);
		void RemoveSeries(Series *series);
		void DeleteSeries(Series *series);

		std::vector<Series *>& GetSerie() { return m_serie; }

		bool IsValid();
		void Validate();

		Axis *GetAxis(AXIS_DIR axis_dir);

		//internal use methods start with _
		const std::vector<Axis *> _get_axes();
		void _setowner(Plot *plot) { m_owner_plot = plot; };
		Plot *_getowner() { return m_owner_plot; };

	protected:

		Plot *m_owner_plot;

		std::vector<Series *> m_serie;

		Grid *m_grid;


		//helpers
	//	void update_uniq_plots();
	private:

		int m_dim_num;
		Axis **m_axes;

		Point<double> m_pan_start_axes_offset;
		Point<double> m_pan_start_rel_coord;
	};

}