#pragma once

#include "../ScaleBox.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB wxScaleBox : public ScaleBox
	{
	public:
		wxScaleBox(AXIS_DIR axis_dir);
		virtual ~wxScaleBox();

	private:


		// Inherited via ScaleBox
		virtual void Render(void *) override;

	};

}