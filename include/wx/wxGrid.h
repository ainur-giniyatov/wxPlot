#pragma once

#include "../Area.h"
#include "../Grid.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB wxGrid : public Grid
	{
	public:
		wxGrid(Area *owner);
		virtual ~wxGrid();

		virtual void Render(void *) override;
	protected:
	private:
	};
}