
#include "main.h"
#include "luke_dmm.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	LukeFrame *lukeframe = new LukeFrame(NULL, wxID_ANY);
	lukeframe->Show(true);

	return true;
}



