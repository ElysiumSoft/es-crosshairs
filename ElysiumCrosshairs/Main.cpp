#include "Main.h"
//////////////////////////////////////////
//	    ELYSIUMSOFT CROSSHAIRS			//
//		  © ElysiumSoft 2020			//
//			Lewis Youldon				//
//////////////////////////////////////////
//	 Edit values in <InitializeGlobals>	//
//	    to configure for target game	//
//////////////////////////////////////////

//	GLOBALS
HWND g_hwnd;
HBRUSH g_hbrColourKey;
RECT g_rect;
UINT g_width, g_height;
LPCWSTR g_title;
SHORT g_red, g_green, g_blue, g_thickness;
UINT g_crosshair_width, g_crosshair_height;
VOID(*pfDraw)(HDC&);

////////////////////////////////////////////////////////////////////////////////////

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;
	pfDraw = DrawCrosshairs;
	BOOL drawing = true;

	InitializeGlobals();

	if (__argc == 1)
		MessageBox(NULL, L"Could not parse target window title from cmd line! Defaulting to FiveM", L"Error!", MB_OK);
	else if (__argc > 1)
	{
		MessageBox(NULL, __wargv[1], L"Selected target", MB_ICONINFORMATION | MB_OK);
		g_title = __wargv[1];
	}

	if (FAILED(SetupAndRegisterWindowClass(wc, hInstance)))
		return EXIT_FAILURE;

	if (FAILED(GetHWNDCoordinates()))
		return EXIT_FAILURE;

	hwnd = CreateWindowEx(WS_EX_LAYERED, L"ESoft Crosshair", L"ESoft Crosshair", WS_POPUP,
		g_rect.left, g_rect.top, g_width, g_height, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, L"Failed to create window", L"Error", MB_ICONERROR | MB_OK);
		return EXIT_FAILURE;
	}

	SetLayeredWindowAttributes(hwnd, RGB(255, 0, 255), 0, LWA_COLORKEY);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (!GetAsyncKeyState(VK_F4))
	{
		if (GetMessage(&msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (GetAsyncKeyState(VK_F4))
			{
				if (drawing == TRUE)
				{
					SetLayeredWindowAttributes(hwnd, 0, 0, LWA_ALPHA);
					drawing = FALSE;
					Sleep(100);
				}
				else
				{
					SetLayeredWindowAttributes(hwnd, RGB(255, 0, 255), 0, LWA_COLORKEY);
					drawing = TRUE;
					Sleep(100);
				}
			}
		}
	}

	return msg.wParam;
}

////////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (msg)
	{
		case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);
			pfDraw(hdc);
			SetWindowPos(g_hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			EndPaint(hwnd, &ps);
			break;
		}

		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////

VOID DrawCrosshairs(HDC& hdc)
{
	HPEN pen0;
	HPEN pen1 = CreatePen(PS_SOLID, g_thickness, RGB(g_red, g_green, g_blue));
	pen0 = (HPEN)SelectObject(hdc, pen1);

	//	DRAW HORIZONTAL SECTION
	MoveToEx(hdc, ((g_width / 2) - (g_crosshair_width / 2)), (g_height / 2), NULL);
	LineTo(hdc, ((g_width / 2) + (g_crosshair_width / 2)), (g_height / 2));

	//	DRAW VERTICAL SECTION
	MoveToEx(hdc, (g_width / 2), ((g_height / 2) - (g_crosshair_height / 2)), NULL);
	LineTo(hdc, (g_width / 2), ((g_height / 2) + (g_crosshair_height / 2)));
}

HRESULT SetupAndRegisterWindowClass(WNDCLASSEX& wc, HINSTANCE& hInstance)
{
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = g_hbrColourKey;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"ESoft Crosshair";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassExW(&wc))
	{
		MessageBox(NULL, L"Failed to register window!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return E_ABORT;
	}

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////////

HRESULT GetHWNDCoordinates()
{
	g_hwnd = FindWindow(NULL, g_title);
	if (g_hwnd == NULL)
	{
		MessageBox(NULL, L"Could not find window with specified title, is it open?", L"ERROR", MB_ICONERROR | MB_OK);
		return E_HANDLE;
	}

	if (!(GetWindowRect(g_hwnd, &g_rect)))
	{
		MessageBox(NULL, L"Could not get window dimensions", L"ERROR", MB_ICONERROR | MB_OK);
		return E_FAIL;
	}

	g_width = g_rect.right - g_rect.left;
	g_height = g_rect.bottom - g_rect.top;

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////////

VOID InitializeGlobals()
{
	//	TARGET WINDOW NAME
	g_title = L"FiveM";	// Change to target window title!

	//	CROSSHAIR COLOUR
	g_red = 255;
	g_green = 255;
	g_blue = 255;

	//	CROSSHAIR SIZE AND THICKNESS
	g_thickness = 1;		  // Fiddle with
	g_crosshair_width = 27;	  // Values until
	g_crosshair_height = 27;  //    Happy

	//	DEFINES COLOUR TO KEY OUT FOR TRANSPARENCY
	g_hbrColourKey = CreateSolidBrush(RGB(255, 0, 255));
}

