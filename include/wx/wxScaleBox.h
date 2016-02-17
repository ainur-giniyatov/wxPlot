#pragma once

#include "wxPlotWindow.h"
#include "../Box.h"
#include "../Scale.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB wxScaleBox : public Box
	{
	public:
		wxScaleBox(wxPlotWindow *plot, Dir orient, AXIS_DIR axis_dir);
		virtual ~wxScaleBox();
		Scale *GetScale() { return m_scale; }
		virtual void Render(void *) override;

	protected:
	private:
		Dir m_orient;
		Scale *m_scale;
		// Inherited via Scale
		//virtual void ScaleRedraw() override;
	};
}