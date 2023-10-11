#include <Windows.h>
#include "win32_graphics.h"  

global global_state GlobalState;

WNDPROC Wndproc;

LRESULT Win32WindowCallBack (HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam)
{
	LRESULT result = {}; 

	switch (Message)
	{
		case WM_CLOSE:
		case WM_DESTROY:
	{
		GlobalState.isRuning = false;
	}break;
	default:
	{
		result = DefWindowProcA(WindowHandle, Message, WParam, LParam);
	}break;
	}

	return result;
}

int APIENTRY WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	GlobalState.isRuning = true;

	WNDCLASSA WindowsClass = {};
	WindowsClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	WindowsClass.lpfnWndProc = Win32WindowCallBack;
	WindowsClass.hInstance = hInstance;
	WindowsClass.hCursor = LoadCursorA(NULL, LPCSTR IDC_ARROW);
	WindowsClass.lpszClassName = "Gruphics Tutorail";
	if (!RegisterClassA( &WindowsClass))
	{
		InvalidCodePath; 
	}
	
	 GlobalState.WindowHandle = CreateWindowExA( 
		0,
		WindowsClass.lpszClassName,
		"Graphics Tutorial",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1280,
		720,
		NULL,
		NULL,
		hInstance,
		NULL);

	 if (!GlobalState.WindowHandle)
	 {
		 InvalidCodePath;
	 }

	 while (GlobalState.isRuning)
	 {
		 MSG Message = {};
		 
		 while (PeekMessageA(&Message, GlobalState.WindowHandle, 0, 0, PM_REMOVE))
		 {
			 switch (Message.message)
			 {
				case WM_QUIT:
				{
					GlobalState.isRuning = false;
				}break;
				default:
				{
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}break;
			 }
		 }	
	 }

	return 0;
}	