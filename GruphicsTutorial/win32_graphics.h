#ifndef WIN32_GRAPHICS_H
#define WIN32_GRAPHICS_H

#include <stdint.h>
#include <stdio.h>
#include <float.h>
#include <stddef.h>
	
#define global static
#define local_global static

#define Assert(Expression) if (!(Expression)) {__debugbreak();} 
#define InvalidCodePath Assert(!"Invalid Code Path")
#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

#include "graphics_math.h"

struct global_state
{
	HWND WindowHandle;
	bool IsRuning;
	HDC DeviceContext;
	int FrameBufferWidth;	
	int FramtBufferHeight;
	int* FrameBufferPixels;	

	float CurrAngle;
};

#endif // !WIN32_GRAPHICS_H
