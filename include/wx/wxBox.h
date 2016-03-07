#include "../plot_defs.h"
#include "../Box.h"

namespace plot
{
	class wxBox :public Box
	{
	public:
		wxBox(int flags);
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
		virtual void _ownersize(const Size<int> &ownersize) override;

	};
}