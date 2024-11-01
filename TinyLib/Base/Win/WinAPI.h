// This file is an advanced windows.h definition so that I can customize.
#pragma once

// GetTickCount needs this.
#define _WIN32_WINNT 0x0601

#ifdef GDI_GRAPHICS
#include <Windows.h>
#include <wingdi.h>
#else

// No GDI functionality needed.
#define NOGDI


#include <shtypes.h>
#include <Windows.h>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl/client.h>
#include <dwrite.h>
#include <d2d1.h>

// Needed for DirectX.
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "dxgi.lib")
#endif

// Encryption
#pragma comment(lib, "Advapi32.lib")

// Undefines
#undef Rectangle
#undef NOGDI