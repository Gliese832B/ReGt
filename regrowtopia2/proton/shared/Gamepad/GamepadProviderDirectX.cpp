#include "PlatformPrecomp.h"
#include "GamepadProviderDirectX.h"
#include "GamepadDirectX.h"
#include "GamepadManager.h"



#include <wbemidl.h>
#include <oleauto.h>
//#include <wmsstd.h>

//-----------------------------------------------------------------------------
// Enum each PNP device using WMI and check each device ID to see if it contains 
// "IG_" (ex. "VID_045E&PID_028E&IG_00").  If it does, then it's an XInput device
// Unfortunately this information can not be found by just using DirectInput 
//-----------------------------------------------------------------------------
BOOL IsXInputDevice(const GUID* pGuidProductFromDirectInput)
{
	IWbemLocator* pIWbemLocator = NULL;
	IEnumWbemClassObject* pEnumDevices = NULL;
	IWbemClassObject* pDevices[20] = { 0 };
	IWbemServices* pIWbemServices = NULL;
	BSTR                    bstrNamespace = NULL;
	BSTR                    bstrDeviceID = NULL;
	BSTR                    bstrClassName = NULL;
	DWORD                   uReturned = 0;
	bool                    bIsXinputDevice = false;
	UINT                    iDevice = 0;
	VARIANT                 var;
	HRESULT                 hr;

	// CoInit if needed
	hr = CoInitialize(NULL);
	bool bCleanupCOM = SUCCEEDED(hr);

	// So we can call VariantClear() later, even if we never had a successful IWbemClassObject::Get().
	VariantInit(&var);

	// Create WMI
	hr = CoCreateInstance(__uuidof(WbemLocator),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IWbemLocator),
		(LPVOID*)&pIWbemLocator);
	if (FAILED(hr) || pIWbemLocator == NULL)
		goto LCleanup;

	bstrNamespace = SysAllocString(L"\\\\.\\root\\cimv2"); if (bstrNamespace == NULL) goto LCleanup;
	bstrClassName = SysAllocString(L"Win32_PNPEntity");   if (bstrClassName == NULL) goto LCleanup;
	bstrDeviceID = SysAllocString(L"DeviceID");          if (bstrDeviceID == NULL)  goto LCleanup;

	// Connect to WMI 
	hr = pIWbemLocator->ConnectServer(bstrNamespace, NULL, NULL, 0L,
		0L, NULL, NULL, &pIWbemServices);
	if (FAILED(hr) || pIWbemServices == NULL)
		goto LCleanup;

	// Switch security level to IMPERSONATE. 
	CoSetProxyBlanket(pIWbemServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
		RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);

	hr = pIWbemServices->CreateInstanceEnum(bstrClassName, 0, NULL, &pEnumDevices);
	if (FAILED(hr) || pEnumDevices == NULL)
		goto LCleanup;

	// Loop over all devices
	for (;; )
	{
		// Get 20 at a time
		hr = pEnumDevices->Next(10000, 20, pDevices, &uReturned);
		if (FAILED(hr))
			goto LCleanup;
		if (uReturned == 0)
			break;

		for (iDevice = 0; iDevice < uReturned; iDevice++)
		{
			// For each device, get its device ID
			hr = pDevices[iDevice]->Get(bstrDeviceID, 0L, &var, NULL, NULL);
			if (SUCCEEDED(hr) && var.vt == VT_BSTR && var.bstrVal != NULL)
			{
				// Check if the device ID contains "IG_".  If it does, then it's an XInput device
					// This information can not be found from DirectInput 
				if (wcsstr(var.bstrVal, L"IG_"))
				{
					// If it does, then get the VID/PID from var.bstrVal
					DWORD dwPid = 0, dwVid = 0;
					WCHAR* strVid = wcsstr(var.bstrVal, L"VID_");
					if (strVid && swscanf(strVid, L"VID_%4X", &dwVid) != 1)
						dwVid = 0;
					WCHAR* strPid = wcsstr(var.bstrVal, L"PID_");
					if (strPid && swscanf(strPid, L"PID_%4X", &dwPid) != 1)
						dwPid = 0;

					// Compare the VID/PID to the DInput device
					DWORD dwVidPid = MAKELONG(dwVid, dwPid);
					if (dwVidPid == pGuidProductFromDirectInput->Data1)
					{
						bIsXinputDevice = true;
						goto LCleanup;
					}
				}
			}
			VariantClear(&var);
			SAFE_RELEASE(pDevices[iDevice]);
		}
	}

LCleanup:
	VariantClear(&var);
	if (bstrNamespace)
		SysFreeString(bstrNamespace);
	if (bstrDeviceID)
		SysFreeString(bstrDeviceID);
	if (bstrClassName)
		SysFreeString(bstrClassName);
	for (iDevice = 0; iDevice < 20; iDevice++)
		SAFE_RELEASE(pDevices[iDevice]);
	SAFE_RELEASE(pEnumDevices);
	SAFE_RELEASE(pIWbemLocator);
	SAFE_RELEASE(pIWbemServices);

	if (bCleanupCOM)
		CoUninitialize();

	return bIsXinputDevice;
}



HWND hwndMain;

BOOL CALLBACK EnumWindowProc(HWND hwnd, LPARAM lParam)
{
	HINSTANCE hinst=(HINSTANCE)GetModuleHandle(NULL);


#ifdef _WIN64

if((HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE)==hinst &&
   IsWindowVisible(hwnd))
#else
	if((HINSTANCE)GetWindowLongPtr(hwnd, GWL_HINSTANCE)==hinst &&
		IsWindowVisible(hwnd))
#endif
	{
		hwndMain=hwnd;
		return FALSE;
	}
	else
		return TRUE;
}


GamepadProviderDirectX::GamepadProviderDirectX()
{
	m_ignoreXInputCapableDevices = false;
	
}

GamepadProviderDirectX::~GamepadProviderDirectX()
{
}

bool GamepadProviderDirectX::Init()
{
	LogMsg("Initting DirectX windows gamepad provider");
	
	hwndMain=NULL;
	EnumWindows(EnumWindowProc, 0);

	HRESULT result = DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID *) &directinput, 0);
	if (FAILED(result))
	{
		LogError("debug", "Unable to initialize direct input");
		return false;
	}


	//enumerate each device
	result = directinput->EnumDevices(
		DI8DEVCLASS_GAMECTRL,
		&GamepadProviderDirectX::enum_devices_callback,
		this,
		DIEDFL_ATTACHEDONLY);
	if (FAILED(result))
	{
		LogError("Unable to enumerate direct input devices");
	}

	return true; //success
}

void GamepadProviderDirectX::Kill()
{
	SAFE_RELEASE(directinput);
}


BOOL GamepadProviderDirectX::enum_devices_callback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	GamepadProviderDirectX *self = (GamepadProviderDirectX *) pvRef;


	if (self->GetIgnoreXInputCapableDevices() && IsXInputDevice(&lpddi->guidProduct))
	{
		LogMsg("DirectInput ignoring device %s because it's xinput capable", lpddi->tszProductName);
		return TRUE;
	}

	GamepadDirectX *pPad = new GamepadDirectX;
	pPad->SetProvider(self);
	pPad->SetDeviceInstance(*lpddi);
	GetGamepadManager()->AddGamepad(pPad);


	

	//	CL_InputDevice device(new CL_InputDevice_DirectInput(self, lpddi));
	//	self->input_context.add_joystick(device);
	
	return TRUE;
}


void GamepadProviderDirectX::Update()
{
	
}

HWND GamepadProviderDirectX::GetHWND()
{
	return hwndMain;
}
