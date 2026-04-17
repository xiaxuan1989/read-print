// image.cpp : Defines the entry point for the console application.

#include <stdio.h>
#include "stdlib.h"
#include <windows.h>
#include <iostream>

using namespace std;

typedef HWND(WINAPI* PROCGETCONSOLEWINDOW)();

PROCGETCONSOLEWINDOW getConsoleWindowProc;

int main(int argc, char* argv[])
{
	//获取句柄
	HMODULE hKernel32 = GetModuleHandle(L"kernel32"); // w_char
	getConsoleWindowProc = (PROCGETCONSOLEWINDOW)GetProcAddress(hKernel32, "GetConsoleWindow");
	HWND cmd = getConsoleWindowProc();
	//判断参数
	if (argc == 2 && argv[1][0] == '/' && argv[1][1] == 'd')
	{
		InvalidateRect(cmd, NULL, true);
		return 0;
	}
	if (argc == 6 && argv[1][0] == '/' && argv[1][1] == 's')
	{
		HDC dc = GetDC(cmd);
		int imx = atoi(argv[2]);
		int imy = atoi(argv[3]);
		int imx2 = atoi(argv[4]);
		int imy2 = atoi(argv[5]);
		BitBlt(dc, imx, imy, imx2, imy2, NULL, 0, 0, BLACKNESS);
		return 0;
	}
	//操作DC
	HDC dc = GetDC(cmd);
	HBITMAP hBitmap;

	//hBitmap = (HBITMAP)LoadImage(NULL, argv[1], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	// 将 char* 转换为 wchar_t* 以适配 LoadImageW 的 LPCWSTR 参数
	wchar_t wFileName[MAX_PATH];
	MultiByteToWideChar(CP_ACP, 0, argv[1], -1, wFileName, MAX_PATH);
	hBitmap = (HBITMAP)LoadImageW(NULL, wFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	HDC cmdmem = CreateCompatibleDC(dc);
	SelectObject(cmdmem, hBitmap);
	int imx = atoi(argv[2]);
	int imy = atoi(argv[3]);
	if (argc == 5)
	{
		if (strcmp(argv[4], "/BLACKNESS") == 0)
		{
			BitBlt(dc, imx, imy, 1000, 1000, cmdmem, 0, 0, BLACKNESS);
		}
		if (strcmp(argv[4], "/DSTINVERT") == 0)
		{
			BitBlt(dc, imx, imy, 1000, 1000, cmdmem, 0, 0, DSTINVERT);
		}
		if (strcmp(argv[4], "/MERGECOPY") == 0)
		{
			BitBlt(dc, imx, imy, 1000, 1000, cmdmem, 0, 0, MERGECOPY);
		}
		if (strcmp(argv[4], "/MERGEPAINT") == 0)
		{
			BitBlt(dc, imx, imy, 1000, 1000, cmdmem, 0, 0, MERGEPAINT);
		}
		if (strcmp(argv[4], "/NOTSRCCOPY") == 0)
		{
			BitBlt(dc, imx, imy, 1000, 1000, cmdmem, 0, 0, NOTSRCCOPY);
		}
		if (strcmp(argv[4], "/NOTSRCERASE") == 0)
		{
			BitBlt(dc, imx, imy, 1000, 1000, cmdmem, 0, 0, NOTSRCERASE);
		}
		if (strcmp(argv[4], "/PATCOPY") == 0)
		{
			BitBlt(dc, imx, imy, 1000, 1000, cmdmem, 0, 0, PATCOPY);
		}
		if (strcmp(argv[4], "/PATPAINT") == 0)
		{
			BitBlt(dc, imx, imy, 1000, 1000, cmdmem, 0, 0, PATPAINT);
		}
		if (strcmp(argv[4], "/PATINVERT") == 0)
		{
			BitBlt(dc, imx, imy, 1000, 1000, cmdmem, 0, 0, PATINVERT);
		}
		if (strcmp(argv[4], "/SRCAND") == 0)
		{
			BitBlt(dc, imx, imy, 1000, 1000, cmdmem, 0, 0, SRCAND);
		}
		if (strcmp(argv[4], "/SRCCOPY") == 0)
		{
			BitBlt(dc, imx, imy, 1000, 1000, cmdmem, 0, 0, SRCCOPY);
		}
		if (strcmp(argv[4], "/SRCERASE") == 0)
		{
			BitBlt(dc, imx, imy, 1000, 1000, cmdmem, 0, 0, SRCERASE);
		}
		if (strcmp(argv[4], "/SRCINVERT") == 0)
		{
			BitBlt(dc, imx, imy, 1000, 1000, cmdmem, 0, 0, SRCINVERT);
		}
		if (strcmp(argv[4], "/SRCPAINT") == 0)
		{
			BitBlt(dc, imx, imy, 1000, 1000, cmdmem, 0, 0, SRCPAINT);
		}
		if (strcmp(argv[4], "/WHITENESS") == 0)
		{
			BitBlt(dc, imx, imy, 1000, 1000, cmdmem, 0, 0, WHITENESS);
		}
		DeleteObject(hBitmap);
		DeleteDC(cmdmem);
		ReleaseDC(cmd, dc);
		return 0;
	}
	BitBlt(dc, imx, imy, 1000, 1000, cmdmem, 0, 0, SRCCOPY);
	Sleep(5000);
	DeleteObject(hBitmap);
	DeleteDC(cmdmem);
	ReleaseDC(cmd, dc);
	return 0;
}