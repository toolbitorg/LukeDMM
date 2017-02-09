#include "luke_dmm.h"

LukeFrame::LukeFrame(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style): 
	MyFrame(parent, id, wxString(""), pos, size, wxCAPTION | wxCLOSE_BOX | wxMINIMIZE_BOX)
{
	mode = VOLTAGE_MODE;

	text_ctrl_unit->SetFont(wxFont(32, wxFONTFAMILY_SWISS,
		wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	text_ctrl_value->SetFont(wxFont(32, wxFONTFAMILY_SWISS,
		wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	luke = new Luke();
	if (!luke->isConnected()) {
	}
	timer = new wxTimer(this);
	Connect(wxEVT_TIMER, wxTimerEventHandler(LukeFrame::OnTimer));
	timer->Start(100);
}

LukeFrame::~LukeFrame()
{
	delete luke;
	timer->Stop();
	delete timer;
}


BEGIN_EVENT_TABLE(LukeFrame, wxFrame)
EVT_IDLE(LukeFrame::OnIdle)
EVT_RADIOBOX(wxID_ANY, LukeFrame::onRadiobox)
END_EVENT_TABLE();


void LukeFrame::onRadiobox(wxCommandEvent &event)
{
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

void LukeFrame::OnTimer(wxTimerEvent& WXUNUSED(event))
{
	if (luke->isConnected()) {

		float value;
		if (mode == VOLTAGE_MODE) {
			value = luke->getVoltage();
			if (value < 1.0 && value > -1.0) {
				value = value * 1000.0;
				text_ctrl_unit->SetValue("mV");
			}
			else {
				text_ctrl_unit->SetValue("V");
			}
		}
		else if (mode == CURRENT_MODE) {
			value = luke->getCurrent();
			if (value < 1.0 && value > -1.0) {
				value = value * 1000.0;
				text_ctrl_unit->SetValue("mA");
			}
			else {
				text_ctrl_unit->SetValue("A");
			}
		}
		wxString str;
		str.Printf(wxT("%3.2f"), value);
		text_ctrl_value->SetValue(str);
		text_ctrl_value->SetSelection(-1, -1);
	}
}

void LukeFrame::OnIdle(wxIdleEvent& event)
{
}

