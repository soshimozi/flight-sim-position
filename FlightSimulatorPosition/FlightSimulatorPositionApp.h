#pragma once
#include "BaseSimConnectApp.h"

EVENT_MAP_BEGIN
DECLARE_EVENT(EVENT_SIMSTART)
EVENT_MAP_END

REQUEST_MAP_BEGIN
DECLARE_REQUEST(DIALOG_MODE_REQUEST)
DECLARE_REQUEST(LANDING_DATA_REQUEST)
DECLARE_REQUEST(AIRCRAFT_DATA_REQUEST)
REQUEST_MAP_END

DATA_DEFINE_BEGIN
DECLARE_DATA_DEFINE(LANDING_PARAMETERS_DEFINITION)
DECLARE_DATA_DEFINE(AIRCRAFT_DATA_DEFINITION)
DATA_DEFINE_END

struct AirlineData
{
	char    strings[1];   // variable-length strings 
};

class CFlightSimulatorPositionApp :
	public CBaseSimConnectApp
{

	void HandleRecvEvent(SIMCONNECT_RECV_EVENT *, DWORD);
	void HandleRecvSimObject(SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE *, DWORD);
	void HandleRecvSystemState(SIMCONNECT_RECV_SYSTEM_STATE *, DWORD);

	BOOL m_showSplash = TRUE;

protected:
	virtual HRESULT OnConnect();
	void ShowSplash();

	DECLARE_DISPATCH_MAP

public:
	CFlightSimulatorPositionApp(HINSTANCE hInstance, LPCSTR szAppName) : CBaseSimConnectApp(hInstance, szAppName) {}
	~CFlightSimulatorPositionApp() {}

	virtual void OnExit() {}

};

