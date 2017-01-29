#include "luke_dmm.h"


LukeFrame::LukeFrame(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style): 
	MyFrame(parent, id, wxString(""), pos, size, wxCAPTION | wxCLOSE_BOX | wxMINIMIZE_BOX)
{
	mode = VOLTAGE_MODE;

	luke = new Luke();
	if (!luke->isConnected()) {
	}
}



BEGIN_EVENT_TABLE(LukeFrame, wxFrame)
EVT_IDLE(LukeFrame::OnIdle)
EVT_RADIOBOX(wxID_ANY, LukeFrame::onRadiobox)
END_EVENT_TABLE();


void LukeFrame::onRadiobox(wxCommandEvent &event)
{
	//	mode =

	switch (radio_box_mode->GetSelection()) {
	case VOLTAGE_MODE:
		mode = VOLTAGE_MODE;
		break;
	case CURRENT_MODE:
		mode = CURRENT_MODE;
		break;
	}


	event.Skip();
}

void LukeFrame::OnIdle(wxIdleEvent& event)
{
	if (luke->isConnected()) {

		wxString str;
		if (mode == VOLTAGE_MODE) {
			float value = luke->getVoltage();
			if (value < 1.0 && value > -1.0) {
				str << value * 1000.0;
				text_ctrl_unit->SetValue("mV");
			}
			else {
				str << value;
				text_ctrl_unit->SetValue("V");
			}
			text_ctrl_value->SetValue(str);
		}
		else if (mode == CURRENT_MODE) {
			float value = luke->getCurrent();
			if (value < 1.0 && value > -1.0) {
				str << value * 1000.0;
				text_ctrl_unit->SetValue("mA");
			}
			else {
				str << value;
				text_ctrl_unit->SetValue("A");
			}
			text_ctrl_value->SetValue(str);
		}
	}
}

