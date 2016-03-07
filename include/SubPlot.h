#pragma once
#include "plot_defs.h"
#include "Series.h"
#include "Scale.h"
#include "Box.h"

#include <vector>

namespace plot
{
	class DLLIMPEXP_PLOTLIB Series;
	class DLLIMPEXP_PLOTLIB Scale;
	class SeriesSelection;

	class DLLIMPEXP_PLOTLIB Subplot
	{
	public:
		enum ORIENTATION
		{
			ORIENTATION_NORMAL,
			ORIENTATION_ROTATED
		};

		enum MOUSESTATE {
			MOUSESTATE_LEFTBUTTON = (1 << 0),
			MOUSESTATE_MIDDLEBUTTON = (1 << 1),
			MOUSESTATE_RIGHTBUTTON = (1 << 2),
			MOUSESTATE_WHEELUP = (1 << 3),
			MOUSESTATE_WHEELDOWN = (1 << 4)
		};

		enum KEYMODSTATE {
			KEYMOD_CTRL = (1 << 0),
			KEYMOD_SHIFT = (1 << 1),
			KEYMOD_ALT = (1 << 2)
		};

		Subplot(const char *plotname = NULL);
		virtual ~Subplot();

		void SetOrientation(ORIENTATION orientation);
		ORIENTATION GetOrientation() { return m_orientation; }

		void SetSubplotName(const char *subplotname = NULL);
		const char *GetSubplotName() { return m_subplot_name; }

		void AddSeries(Series *series);
		void DeleteSeries(Series *series);
		std::vector<Series*> &GetSerie() { return m_serie; };

		void Clear(bool update = true);

		virtual void RedrawPlot() = 0;
		
		void Validate(bool refresh_buffer = true);


		//void RemoveBox(Box *box);
		//void DeleteBox(Box *box);
		void AddBox(Box *box);
		//void ArrangeBoxes();

		void SetLeftButtonAction(LEFTBUTTON_ACTION lba) { m_lbaction = lba; };

		void Fit(int axis_mask);

		//internal use methods start with _
		const Size<int> &_get_size() { return m_size; }
		void _refresh_dependant_scales();
		ORIENTATION _get_orientation() { return m_orientation; }
		virtual const Size<int> _get_backend_size() = 0;
		const auto &_get_dependant_scales() { return m_dependant_scales; }
		const Rect<int> _plot_to_backend(Rect<int> &rect);

	protected:
		virtual void emit_viewchanged() = 0;

		Box *hitbox(const Point<int> &mouse_backend_coord);
		Series *hitseries(int *dotindex_first, int *dotindex_last, const Point<int> &mouse_backend_coord);

		//mouse handlers
		void leftdown(const Point<int> &mouse_backend_coord);
		void leftup(const Point<int> &mouse_backend_coord);
		void rightdown(const Point<int> &mouse_backend_coord);
		void rightup(const Point<int> &mouse_backend_coord);
		void motion(int mousestate, const Point<int> &mouse_backend_coord);
		void wheel(int keymodstate, int mousestate, const Point<int> &mouse_backend_coord);

		bool boxprocess_leftdown(const Point<int> &mouse_backend_coord);
		void boxprocess_leftup(const Point<int> &mouse_backend_coord);
		void boxprocess_mousemove(const Point<int> &mouse_backend_coord);
		//void leftmove(const Point<int> &mouse_backend_coord);
		

		//void StartZoomSelect(const Point<double> &zoom_sel_start_rel_coord);
		//void ProceedZoomSelect(const Point<double> &zoom_sel_proceed_rel_coord);
		//void EndZoomSelect();
		//virtual void DrawZoomSelection() = 0;


		std::vector<Series*> m_serie;

		/*holds pointers to Scale objects that depend on the plot*/
		std::vector<Scale *> m_dependant_scales;
		//void update_dependant_scales();
		bool m_panning;

		bool m_zoomsel_switch;
		bool m_zoomselecting;
		Point<double> m_zoom_sel_start_rel_coord;
		Point<double> m_zoom_sel_end_rel_coord;
		char *m_subplot_name;

		Box *m_selected_box;
		BOXSTATE m_selected_box_state;
		int m_selected_box_sides;
		Point<int> m_box_click_delta;//distance between top left and mouse
		Point<int> m_box_click_delta2;//distance between bottom right and mouse
		std::vector<Box *> m_boxes;

		Size<int> m_size;
		void plot_resized();
		
		std::vector<Scale *> m_scales;

		LEFTBUTTON_ACTION m_lbaction;

		bool m_is_data_view_modified;
		ORIENTATION m_orientation;
		//helpers
		const Point<int> backend_to_plot(const Point<int> &backendpoint);
		const Size<int> backend_to_plot(const Size<int> &backendsize);

	private:
		void StartPan(const Point<int> &pan_start_coord);
		void ProceedPan(const Point<int> &pan_start_coord);
		void EndPan();

		void validate_other_plots();
	};

}