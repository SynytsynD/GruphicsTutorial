#include <Windows.h>
#include <cmath>
#include "win32_graphics.h"  


global global_state GlobalState;

v2 ProjectPoint(v3 Pos)
{
	v2 Result = Pos.xy / Pos.z;
	Result = 0.5f * (Result + V2(1)) * V2(GlobalState.FrameBufferWidth, GlobalState.FramtBufferHeight);
	return Result;
}

LRESULT Win32WindowCallBack (HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam)
{
	LRESULT result = {}; 

	//switch for processing close/destroy signal
	switch (Message)
	{
		case WM_CLOSE:
		case WM_DESTROY:
	{
		GlobalState.IsRuning = false;
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
	GlobalState.IsRuning = true;

	LARGE_INTEGER TimerFrequency = {};
	Assert(QueryPerformanceFrequency(&TimerFrequency));

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
	
	//WindowHandle - create window
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

	//GetDC function retrieves a handle to a device context (DC) for the client area of a specified window or for the entire screen.
	GlobalState.DeviceContext = GetDC(GlobalState.WindowHandle);

	{
		RECT ClientRect = {};
		Assert(GetClientRect(GlobalState.WindowHandle, &ClientRect));
	/*	GlobalState.FrameBufferWidth = ClientRect.right - ClientRect.left;
		GlobalState.FramtBufferHeight = ClientRect.bottom - ClientRect.top;*/
		GlobalState.FrameBufferWidth = 300;
		GlobalState.FramtBufferHeight = 300;
		GlobalState.FrameBufferPixels = (int*)malloc(sizeof(int) * GlobalState.FrameBufferWidth * GlobalState.FramtBufferHeight);
	}

	LARGE_INTEGER StartTime = {};
	LARGE_INTEGER EndTime = {};
	Assert(QueryPerformanceCounter(&StartTime));

	 //Main loop for hold window
	 while (GlobalState.IsRuning)
	 {
		 Assert(QueryPerformanceCounter(&EndTime));
		 double FrameTime = double(EndTime.QuadPart - StartTime.QuadPart) / double(TimerFrequency.QuadPart);
		 StartTime = EndTime; 

		 MSG Message = {};
		 
		 // PeekMessageA - checks the thread message queue for a posted message
		 while (PeekMessageA(&Message, GlobalState.WindowHandle, 0, 0, PM_REMOVE))
		 {
			 switch (Message.message)
			 {
				case WM_QUIT:
				{
					GlobalState.IsRuning = false;
				}break;
				default:
				{
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}break;
			 }
		 }	

		 for (int Y = 0; Y < GlobalState.FramtBufferHeight; ++Y)
		 { 
			 for (int X = 0; X < GlobalState.FrameBufferWidth; ++X)
			 {
				int PixelId = Y * GlobalState.FrameBufferWidth + X; // formula to get pixel id
				 
				int Red = 0;
				int Green = 0; 
				int Blue = 0;
				int Alpha = 255;
				int PixelColor = Alpha << 24 | Red << 16 | Green << 8 | Blue;

				GlobalState.FrameBufferPixels[PixelId] = PixelColor;
			 }
		 }

		 GlobalState.CurrAngle += float(FrameTime);
		 if (GlobalState.CurrAngle > 2.0f * 3.14f)
		 {
			 GlobalState.CurrAngle -= 2.0f * 3.14f;
		 }

		 for (int TriangleId = 0; TriangleId < 7; ++TriangleId)
		 {
			float Depth = powf(2, float(TriangleId + 1));
				
			v3 Points[3] =
			 {
				V3(-1.0f, -0.5f,Depth),
				V3(1.0f, -0.5f, Depth),
				V3(0.0f, 0.5f, Depth)
			};

			for (int PointId = 0; PointId < ArrayCount(Points); ++PointId)
			{
				v3 TransformedPos = Points[PointId] + V3(cosf(GlobalState.CurrAngle), sinf(GlobalState.CurrAngle), 0);
				v2 PixelPos = ProjectPoint(TransformedPos);

				if (PixelPos.x >= 0.0f && PixelPos.x < GlobalState.FrameBufferWidth &&
					PixelPos.y >= 0.0f && PixelPos.y < GlobalState.FramtBufferHeight)
				{
					int PixelId = int(PixelPos.y) * GlobalState.FrameBufferWidth + int(PixelPos.x);
					GlobalState.FrameBufferPixels[PixelId] = 0xFF00FF00;
				}
			}
		 }
		
		 RECT ClientRect = {};
		 Assert(GetClientRect(GlobalState.WindowHandle, &ClientRect));
		 int ClientWidth = ClientRect.right - ClientRect.left;
		 int ClientHeight = ClientRect.bottom - ClientRect.top;

		BITMAPINFO BitmapInfo = {};
		BitmapInfo.bmiHeader.biSize = sizeof(tagBITMAPINFOHEADER);
		BitmapInfo.bmiHeader.biWidth = GlobalState.FrameBufferWidth;
		BitmapInfo.bmiHeader.biHeight = GlobalState.FramtBufferHeight;
		BitmapInfo.bmiHeader.biPlanes = 1;
		BitmapInfo.bmiHeader.biBitCount = 32;
		BitmapInfo.bmiHeader.biCompression = BI_RGB;
		
		// for copy pixel from buffer to screen 
		Assert(StretchDIBits(GlobalState.DeviceContext,
							0,
							0,
							ClientWidth,
							ClientHeight,
							0,
							0,
							GlobalState.FrameBufferWidth,
							GlobalState.FramtBufferHeight,
							GlobalState.FrameBufferPixels,
							&BitmapInfo,
							DIB_RGB_COLORS,
							SRCCOPY));
	 }
	return 0;
}	