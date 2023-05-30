#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>

BOOL WINAPI MyHandlerRoutine( DWORD dwCtrlType ) {
	TerminateProcess(GetCurrentProcess(), 2);
	return TRUE;
}

FILE* f1 = NULL, * f2 = NULL, * f3 = NULL;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
    switch (dwReason) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        AllocConsole();
        SetConsoleCtrlHandler(MyHandlerRoutine, TRUE);
        f1 = freopen("CONIN$", "rb", stdin);
        f2 = freopen("CONOUT$", "wb", stdout);
        f3 = freopen("CONOUT$", "wb", stderr);
        break;
    case DLL_PROCESS_DETACH:
        fclose(f1);
        fclose(f2);
        fclose(f3);
        FreeConsole();
        break;
    }
    return TRUE;
}