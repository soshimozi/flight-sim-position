#include "stdafx.h"
#include "FlightSimulatorPositionApp.h"

#include "SplashScreen.h"

#using <ClassLibrary1.dll>

BEGIN_DISPATCH_MAP(CFlightSimulatorPositionApp)
	ADD_HANDLER(SIMCONNECT_RECV_ID_EVENT, SIMCONNECT_RECV_EVENT, HandleRecvEvent)
	ADD_HANDLER(SIMCONNECT_RECV_ID_SIMOBJECT_DATA_BYTYPE, SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE, HandleRecvSimObject)
	ADD_HANDLER(SIMCONNECT_RECV_ID_SYSTEM_STATE, SIMCONNECT_RECV_SYSTEM_STATE, HandleRecvSystemState)
END_DISPATCH_MAP


HRESULT CFlightSimulatorPositionApp::OnConnect()
{
	// get things started
	return SubscribeToSystemEvent(EVENT_SIMSTART, SIMCONNECT_SYSTEM_EVENT_SIMSTART);
}

void CFlightSimulatorPositionApp::HandleRecvEvent(SIMCONNECT_RECV_EVENT *pData, DWORD cbData)
{
	ClassLibrary1::Class1 ^pLibrary = gcnew ClassLibrary1::Class1();
	pLibrary->Test();

	switch (pData->uEventID)
	{
	case EVENT_SIMSTART:
		if (m_showSplash)
		{
			m_showSplash = FALSE;

			// ask system to turn on dialog mode
			SetSystemState(SIMCONNECT_SYSTEM_STATE_DIALOGMODE, 1, 0, NULL);

			// Send a request to ask whether Dialog Mode is on 
			RequestSystemState(DIALOG_MODE_REQUEST, SIMCONNECT_SYSTEM_STATE_DIALOGMODE);
		}
		//pLibrary->Test();
		break;

	default:
		break;
	}
}

void CFlightSimulatorPositionApp::ShowSplash() 
{
	FlightSimulatorPosition::SplashScreen ^frm = gcnew FlightSimulatorPosition::SplashScreen();
	frm->ShowDialog();
}

void CFlightSimulatorPositionApp::HandleRecvSimObject(SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE *pData, DWORD cbData)
{

}

void CFlightSimulatorPositionApp::HandleRecvSystemState(SIMCONNECT_RECV_SYSTEM_STATE *pData, DWORD cbData)
{
	switch (pData->dwRequestID)
	{
	case DIALOG_MODE_REQUEST:

		// If Dialog Mode is on, show a Message box 
		if (pData->dwInteger != 0) {

			ShowSplash();

			// Send a request to turn Dialog Mode off 
			SetSystemState(SIMCONNECT_SYSTEM_STATE_DIALOGMODE, 0, 0, NULL);
		}
		break;
	}
}