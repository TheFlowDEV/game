#include "ConsoleFunctions.h"
typedef void (WINAPI* RtlGetVersionFunc)(OSVERSIONINFOEXW*);

void SetXY(short X, short Y) {
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hout, coord);
}
void clear() {
	system("cls");
}
bool IsWindows11()
{
	OSVERSIONINFOEXW osInfo = {};
	osInfo.dwOSVersionInfoSize = sizeof(osInfo);

	HMODULE hNtdll = GetModuleHandleW(L"ntdll.dll");
	if (hNtdll) {
		RtlGetVersionFunc rtlGetVersion = (RtlGetVersionFunc)GetProcAddress(hNtdll, "RtlGetVersion");
		if (rtlGetVersion) {
			rtlGetVersion(&osInfo);

			if (osInfo.dwMajorVersion == 10 && osInfo.dwBuildNumber >= 22000) {
				return true;
			}
		}
	}

	return false;
}
