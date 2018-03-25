#pragma once
#include "stdafx.h"

#include <SimConnect.h>
#include <string>
#include <objbase.h>

#define DECLARE_DISPATCH_MAP virtual void DispatchProc (SIMCONNECT_RECV*, DWORD);
#define BEGIN_DISPATCH_MAP(tp) void tp::DispatchProc(SIMCONNECT_RECV* pData, DWORD cbData) { \
	switch(pData->dwID) {

#define END_DISPATCH_MAP default: break; } }

#define ADD_HANDLER(key, tp, func) case key: \
	func(reinterpret_cast<tp *>(pData), cbData); \
	break;

#define DECLARE_DISPATCH_HANDLER (func, tp) void func(tp *pData, DWORD cbData);

#define DECLARE_SIMCONNECT_APP(classname) classname *pApp;

#define DECLARE_SIMCONNECT_APPSTART(classname, appname) int __stdcall DLLStart(void) { \
	CoInitializeEx(NULL, COINIT_MULTITHREADED); \
	pApp = new classname(hDll, appname); \
	if (pApp) { \
		pApp->Connect(); \
		} \
	return 0; \
}

#define DECLARE_SIMCONNECT_APPSTOP() void __stdcall DLLStop(void) { \
	if (pApp != NULL) { \
		pApp->OnExit(); \
		delete pApp; \
		} \
}

#define DATA_DEFINE_BEGIN static enum DATA_DEFINE_ID {
#define DECLARE_DATA_DEFINE(id) id,
#define DATA_DEFINE_END LAST_DATA };

#define EVENT_MAP_BEGIN static enum EVENT_ID {
#define DECLARE_EVENT(id) id,
#define EVENT_MAP_END LAST_EVENT };

#define INPUT_MAP_BEGIN static enum INPUT_ID {
#define DECLARE_INPUT(id) id,
#define INPUT_MAP_END LAST_INPUT };

#define GROUP_MAP_BEGIN static enum GROUP_ID  {
#define DECLARE_GROUP(id) id,
#define GROUP_MAP_END LAST_GROUP };

#define REQUEST_MAP_BEGIN static enum REQUEST_ID {
#define DECLARE_REQUEST(id) id,
#define REQUEST_MAP_END LAST_REQUEST };

#define SIMCONNECT_SYSTEM_EVENT_SIMSTART "SimStart"
#define SIMCONNECT_SYSTEM_STATE_DIALOGMODE "DialogMode"

class CBaseSimConnectApp
{
	static void CALLBACK DispatchProcStatic(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext)
	{
		CBaseSimConnectApp* pThis = reinterpret_cast<CBaseSimConnectApp*>(pContext);
		pThis->DispatchProc(pData, cbData);
	}

protected:
	HANDLE m_hSimConnect;
	HINSTANCE m_hInstance;
	LPCSTR m_szAppName;

	virtual void DispatchProc(SIMCONNECT_RECV* pData, DWORD cbData) = 0;
	virtual HRESULT OnConnect() = 0;

public:
	CBaseSimConnectApp(HINSTANCE hInstance, LPCSTR szAppName) : m_hInstance(hInstance), m_szAppName(szAppName), m_hSimConnect(NULL)
	{}

	virtual ~CBaseSimConnectApp() {
		if (m_hSimConnect != NULL) {
			SimConnect_Close(m_hSimConnect);
		}
	}

	virtual void OnExit() = 0;

	HRESULT Connect() {
		if (m_hSimConnect != NULL) return S_OK;

		HRESULT hr;
		if (SUCCEEDED(hr = SimConnect_Open(&m_hSimConnect, m_szAppName, NULL, 0, NULL, 0)))
		{
			if (SUCCEEDED(hr = OnConnect()))
			{
				return SimConnect_CallDispatch(m_hSimConnect, CBaseSimConnectApp::DispatchProcStatic, this);
			}
		}
	}

	inline HRESULT SubscribeToSystemEvent(int eventId, std::string eventName) {
		return SimConnect_SubscribeToSystemEvent(m_hSimConnect, eventId, eventName.c_str());
	}

	inline HRESULT SetSystemState(const char * szState, DWORD dwInteger, float fFloat, const char * szString) {
		return SimConnect_SetSystemState(m_hSimConnect, szState, dwInteger, fFloat, szString);
	}

	inline HRESULT RequestSystemState(SIMCONNECT_DATA_REQUEST_ID RequestID, const char * szState) {
		return SimConnect_RequestSystemState(m_hSimConnect, RequestID, szState);
	}

	inline HRESULT RequestDataOnSimObjectType(SIMCONNECT_DATA_REQUEST_ID RequestID, SIMCONNECT_DATA_DEFINITION_ID DefineID, DWORD dwRadiusMeters, SIMCONNECT_SIMOBJECT_TYPE type) {
		return SimConnect_RequestDataOnSimObjectType(m_hSimConnect, RequestID, DefineID, dwRadiusMeters, type);
	}

};

