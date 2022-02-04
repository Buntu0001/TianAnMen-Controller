//
// Created by LUNAFE on 2022-02-04.
//

#include "eventhandler.h"



void eventhandler::getComputerName(wchar_t *buf) {
    wchar_t folder[MAX_PATH];
    GetEnvironmentVariableW(L"UserProfile", folder, MAX_PATH);

    wchar_t test[MAX_PATH];
    util::trim(folder, 9, test);

    wcscpy(buf, test);
}



void eventhandler::getOSVersion(wchar_t *buf) {
    typedef NTSTATUS(WINAPI *LPFN_RTLGETVER)(LPOSVERSIONINFOEXW);
    LPFN_RTLGETVER fnRtlGetVer;

    HMODULE h = GetModuleHandle(("ntdll"));
    fnRtlGetVer = (LPFN_RTLGETVER) GetProcAddress(h, "RtlGetVersion");
    if (fnRtlGetVer) {
        OSVERSIONINFOEXW osInfo;

        osInfo.dwOSVersionInfoSize = sizeof(osInfo);
        fnRtlGetVer(&osInfo);

        if (osInfo.dwMajorVersion == 10 && osInfo.dwMinorVersion == 0) {
            if (osInfo.dwBuildNumber >= 22000) {
                wcscpy(buf, L"윈도우 11");
            } else {
                wcscpy(buf, L"Windows 10");
            }
        } else if (osInfo.dwMajorVersion == 6) {
            if (osInfo.dwMinorVersion == 3) {
                wcscpy(buf, L"Windows 8.1");
            } else if (osInfo.dwMinorVersion == 2) {
                wcscpy(buf, L"Windows 8");
            } else if (osInfo.dwMinorVersion == 1) {
                wcscpy(buf, L"Windows 7");
            } else if (osInfo.dwMinorVersion == 0) {
                wcscpy(buf, L"Windows Vista");
            }
        } else {
            wcscpy(buf, L"Windows XP");
        }
    }
}

void eventhandler::getIP(wchar_t *buf) {
    HINTERNET net = InternetOpen("IP retriever",
                                 INTERNET_OPEN_TYPE_PRECONFIG,
                                 NULL,
                                 NULL,
                                 0);

    HINTERNET conn = InternetOpenUrl(net,
                                     "http://myexternalip.com/raw",
                                     NULL,
                                     0,
                                     INTERNET_FLAG_RELOAD,
                                     0);

    char buffer[4096];
    DWORD read;

    InternetReadFile(conn, buffer, sizeof(buffer) / sizeof(buffer[0]), &read);
    InternetCloseHandle(net);

    wchar_t *pBuf;

    int bufSize = MultiByteToWideChar(CP_ACP, 0, buffer, -1, NULL, NULL);
    pBuf = new WCHAR[bufSize];
    MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer) + 1, pBuf, bufSize);

    wcscpy(buf, pBuf);
}

void eventhandler::getActiveWindow(wchar_t *buf) {
    HWND foreground = GetForegroundWindow();
    if (foreground)
    {
        wchar_t window_title[128];
        GetWindowTextW(foreground, window_title, 256);
        if (wcslen(window_title) > 0) {
            wcscpy(buf, window_title);
        } else {
            wcscpy(buf, L"Background");
        }
    }
}

void eventhandler::getGeoID(wchar_t *buf) {
    GEOID myGEO = GetUserGeoID(GEOCLASS_NATION);
    int sizeOfBuffer = GetGeoInfoW(myGEO, GEO_ISO2, NULL, 0, 0);
    WCHAR *buffer = new WCHAR[sizeOfBuffer];
    int result = GetGeoInfoW(myGEO, GEO_ISO2, buffer, sizeOfBuffer, 0);
    wcscpy(buf, buffer);
}


