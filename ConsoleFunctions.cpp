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

	HMODULE hNtdll = GetModuleHandleW(L"ntdll.dll");// получаем модуль основного €дра системы
	if (hNtdll) {
		RtlGetVersionFunc rtlGetVersion = (RtlGetVersionFunc)GetProcAddress(hNtdll, "RtlGetVersion");
		if (rtlGetVersion) {
			rtlGetVersion(&osInfo);//получаем версию

			if (osInfo.dwMajorVersion == 10 && osInfo.dwBuildNumber >= 22000) {// у Windows 11 и у Windows 10 MajorVersion равен 10, поэтому мы должны также сравнивать BuildNumber. ≈сли BuildNumber больше или равен 22000, то это Windows 11
				return true;
			}
		}
	}

	return false;
}
