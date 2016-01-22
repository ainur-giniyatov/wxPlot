#include "myapp.h"
#include "myframe.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	wxImage::AddHandler(new wxPNGHandler);
	MyFrame *mydialog = new MyFrame();

	mydialog->Show();
	return true;
}

int main(int argc, char **argv)
{
	printf("Hello\n");
	wxEntry(argc, argv);
	printf("press enter\n");
	//getchar();
	return 0;
}