#include <windows.h> 
#include "tchar.h"

namespace glb
{
	TCHAR str[128];
	INT t = 0, width = 750, height = 700, x = 0, y = 0, step = 2000, stepSpan = 1;
	INT screenX, screenY, screenWidth, screenHeight;
	INT horizontalMove, verticalMove;
}

void WindowStep(HWND hWnd);

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение");

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc = WindowProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hCursor = LoadCursor(NULL, IDC_WAIT);
	wcl.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = szClassWindow;
	wcl.hIconSm = NULL;
	if (!RegisterClassEx(&wcl))
		return 0;
	hWnd = CreateWindowEx(
		0,
		szClassWindow,
		TEXT("My first window."),
		WS_THICKFRAME,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInst,
		NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return lpMsg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)
		{
			glb::x = 0;
			glb::y = 0;
			glb::t = 0;
			glb::horizontalMove = 0;
			glb::verticalMove = 0;
			MoveWindow(hWnd, glb::x, glb::y, glb::width, glb::height, 1);
			SetTimer(hWnd, 1, glb::stepSpan, NULL);
		}
		else if (wParam == VK_ESCAPE)
			KillTimer(hWnd, 1);
		break;

	case WM_TIMER:
		glb::t++;
		WindowStep(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}

void WindowStep(HWND hWnd)
{
	HWND hWndScreen = GetDesktopWindow();
	RECT clientRect;
	GetClientRect(hWndScreen, &clientRect);
	glb::screenX = clientRect.left;
	glb::screenY = clientRect.top;
	glb::screenWidth = clientRect.right;
	glb::screenHeight = clientRect.bottom;

	if (glb::y == 0 && glb::x < glb::screenWidth - glb::width)
	{
		glb::horizontalMove++;
		glb::x = glb::horizontalMove * glb::step;
		MoveWindow(hWnd, glb::x, glb::y, glb::width, glb::height, 1);
	}

	if (glb::y < glb::screenHeight - glb::height && glb::x >= glb::screenWidth - glb::width)
	{
		glb::verticalMove++;
		glb::y = glb::verticalMove * glb::step;
		MoveWindow(hWnd, glb::x, glb::y, glb::width, glb::height, 1);
	}

	if (glb::y >= glb::screenHeight - glb::height && glb::x > 0)
	{
		glb::horizontalMove--;
		glb::x = glb::horizontalMove * glb::step;
		MoveWindow(hWnd, glb::x, glb::y, glb::width, glb::height, 1);
	}

	if (glb::y >= 0 && glb::x <= 0)
	{
		glb::verticalMove--;
		glb::y = glb::verticalMove * glb::step;
		MoveWindow(hWnd, glb::x, glb::y, glb::width, glb::height, 1);
	}
}