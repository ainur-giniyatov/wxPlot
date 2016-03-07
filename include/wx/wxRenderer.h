#pragma once
#include "plot_defs.h"
#include "../Renderer.h"

namespace plot
{
	
	template <typename T1, typename T2>
	class DLLIMPEXP_PLOTLIB wxRendererTyped : public Renderer
	{
	public:
		wxRendererTyped();
		virtual ~wxRendererTyped();

		virtual Series *_isspotted(Point<int> &mouse_coord, int *dotindex_first, int *dotindex_last) override;
	protected:
	private:
		virtual void Render(void *) override;
		size_t m_left_index, m_right_index;//indexes of leftmost and rightmost visible markers
	};

	template DLLIMPEXP_PLOTLIB class wxRendererTyped<double, double>;
	template DLLIMPEXP_PLOTLIB class wxRendererTyped<int, int>;
}