#pragma once
#include "Box.h"
#include "Scale.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB ScaleBox : public Box, public Scale
	{
	public:
		ScaleBox(AXIS_DIR axis_dir);
		virtual ~ScaleBox();
	protected:
		virtual void _ownersize(int w, int h) override;
	};
}