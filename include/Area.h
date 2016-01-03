#pragma once
#include <vector>

#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Axis.h"

#include "Plot.h"
#include "Grid.h"

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
		void AddSeries(Series *series);
		void RemoveSeries(Series *series);
		void DeleteSeries(Series *series);

		std::vector<Series *>& GetSerie() { return m_serie; }


		Axis *GetAxis(AXIS_DIR axis_dir);

		virtual void Zoom(const  Point<double> &zoom_wheel_rel_coord, double xfactor, double yfactor);
		virtual void StartPan(const  Point<double> &pan_start_rel_coord);
		virtual void ProceedPan(const  Point<double> &pan_proceed_rel_coord);
		virtual void EndPan();

		virtual void ZoomSelection(double start_rx, double start_ry, double end_rx, double end_ry);

		//internal use methods start with _
		void _SetOwner(Plot *plot) { m_owner_plot = plot; }
		void _SetGrid(Grid *grid);

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