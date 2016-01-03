#pragma once

#include "Renderer.h"

namespace plot
{
	template <typename T1, typename T2>
	class DLLIMPEXP_PLOTLIB wxRendererTyped : public Renderer
	{
	public:
		wxRendererTyped();
		virtual ~wxRendererTyped();


	protected:
	private:
		virtual void Render(void *) override;
		virtual void PutMark(void *, int x, int y) override;
		virtual void PutLine(void *, int x, int y, int w, int h) override;
	};

	template DLLIMPEXP_PLOTLIB class wxRendererTyped<double, double>;
	template DLLIMPEXP_PLOTLIB class wxRendererTyped<int, int>;
}