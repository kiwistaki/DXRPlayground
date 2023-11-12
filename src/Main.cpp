#include "stdafx.h"
#include "DXRSample.h"

_Use_decl_annotations_
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	DXRSample sample(1280, 720, "DXR Sample");
	return Win32Application::Run(&sample, hInstance, nCmdShow);
}
