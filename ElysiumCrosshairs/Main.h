#pragma once


#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <iostream>
#include <string>

#include <shellapi.h>

HRESULT SetupAndRegisterWindowClass(WNDCLASSEX&, HINSTANCE&);
HRESULT GetHWNDCoordinates();
VOID DrawCrosshairs(HDC&);
VOID InitializeGlobals();
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);