#pragma once
#include "DXSampleHelper.h"
#include "Win32Application.h"
#include <dxgi1_2.h>

class Application
{
public:
	Application(UINT width, UINT height, std::string name);
	virtual ~Application();

	virtual void OnInit() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;
	virtual void OnDestroy() = 0;

	virtual void OnKeyDown(UINT8 /*key*/)   {}
	virtual void OnKeyUp(UINT8 /*key*/)     {}

	UINT GetWidth() const           { return m_width; }
	UINT GetHeight() const          { return m_height; }
	const CHAR* GetTitle() const   { return m_title.c_str(); }

	void ParseCommandLineArgs(_In_reads_(argc) WCHAR* argv[], int argc);

protected:
	std::wstring GetAssetFullPath(LPCWSTR assetName);
	void GetHardwareAdapter(_In_ IDXGIFactory2* pFactory, _Outptr_result_maybenull_ IDXGIAdapter1** ppAdapter);
	void SetCustomWindowText(LPCSTR text);

protected:
	UINT m_width;
	UINT m_height;
	float m_aspectRatio;
	bool m_useWarpDevice;

private:
	std::wstring m_assetsPath;
	std::string m_title;
};
