#include "../plot_defs.h"
#include "../Box.h"

namespace plot
{
	class wxBox :public Box
	{
	public:
		wxBox();
		virtual ~wxBox();

	protected:
	private:

		// Inherited via Box
		virtual void Render(void *) override;

	};

	class wxTitleBox : public TitleBox
	{
	public:
		wxTitleBox();
		virtual ~wxTitleBox();
	private:


		// Inherited via TitleBox
		virtual void Render(void *) override;
		virtual void _ownersize(int w, int h) override;

	};
}