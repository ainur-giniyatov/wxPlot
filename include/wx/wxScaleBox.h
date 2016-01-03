#pragma once

#include "wxPlotWindow.h"
#include "../Box.h"
#include "../Scale.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB wxScaleBox : public Box, public Scale
	{
	public:
		wxScaleBox(wxPlotWindow *plot, Dir orient);
		virtual ~wxScaleBox();

		virtual void Render(void *) override;

	protected:
	private:
		Dir m_orient;

		// Inherited via Scale
		virtual void ScaleRedraw() override;
	};
}