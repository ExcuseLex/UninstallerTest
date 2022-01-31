#include <iostream>
#include <vector>
#include <string>
#include "ConsoleApplication1.h"

std::vector<uninstall> uninstallVector;

void App_X32_X64() {
    HKEY startHKey = HKEY_LOCAL_MACHINE;
    HKEY hUninstKey = NULL;
    HKEY hAppKey = NULL;
    WCHAR sAppKeyName[1024];
    WCHAR sUninstallPath[1024];
    WCHAR sDisplayName[1024];
    WCHAR sSubKey[1024];

    WCHAR sRoot[] = L"SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall";  //x64 x32
    long lResult = ERROR_SUCCESS;
    DWORD dwType = KEY_READ;
    DWORD dwByte = KEY_ALL_ACCESS;
    DWORD dwBufferSize = 0;


    if (RegOpenKeyEx(startHKey, sRoot, 0, KEY_READ, &hUninstKey) == ERROR_SUCCESS)
    {
        for (DWORD dwIndex = 0; lResult == ERROR_SUCCESS; dwIndex++)
        {           
            dwBufferSize = sizeof(sAppKeyName);
            if ((lResult = RegEnumKeyEx(hUninstKey, dwIndex, (LPWSTR)sAppKeyName,
                &dwBufferSize, NULL, NULL, NULL, NULL)) == ERROR_SUCCESS)
            {              
                wsprintf(sSubKey, L"%s\\%s", sRoot, sAppKeyName);

                if (RegOpenKeyEx(startHKey, sSubKey, 0, KEY_READ, &hAppKey) != ERROR_SUCCESS)
                {
                    RegCloseKey(hAppKey);
                    RegCloseKey(hUninstKey);
                }
               
                dwBufferSize = sizeof(sDisplayName);
                if (RegQueryValueEx(hAppKey, L"DisplayName", NULL,
                    &dwType, (unsigned char*)sDisplayName, &dwBufferSize) == ERROR_SUCCESS)
                {
                    dwBufferSize = sizeof(sUninstallPath);
                    if (RegQueryValueEx(hAppKey, L"UninstallString", NULL,
                        &dwType, (unsigned char*)sUninstallPath, &dwBufferSize) == ERROR_SUCCESS)
                    {
                        uninstallVector.push_back(uninstall(sUninstallPath, sDisplayName, sAppKeyName, startHKey, dwByte));
                        wprintf(L"%s\n", sDisplayName);
                    }
                }
                RegCloseKey(hAppKey);
            }
        }
    }
    RegCloseKey(hUninstKey);

    std::cout << uninstallVector.size();
}

void App_user() {
    HKEY startHKey = HKEY_CURRENT_USER;
    HKEY hUninstKey = NULL;
    HKEY hAppKey = NULL;
    WCHAR sAppKeyName[1024];
    WCHAR sUninstallPath[1024];
    WCHAR sDisplayName[1024];
    WCHAR sSubKey[1024];

    WCHAR sRoot[] = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall";  
    long lResult = ERROR_SUCCESS;
    DWORD dwType = KEY_READ;
    DWORD dwByte = KEY_ALL_ACCESS;
    DWORD dwBufferSize = 0;


    if (RegOpenKeyEx(startHKey, sRoot, 0, KEY_ALL_ACCESS, &hUninstKey) == ERROR_SUCCESS)
    {
        for (DWORD dwIndex = 0; lResult == ERROR_SUCCESS; dwIndex++)
        {           
            dwBufferSize = sizeof(sAppKeyName);
            if ((lResult = RegEnumKeyEx(hUninstKey, dwIndex, (LPWSTR)sAppKeyName,
                &dwBufferSize, NULL, NULL, NULL, NULL)) == ERROR_SUCCESS)
            {               
                wsprintf(sSubKey, L"%s\\%s", sRoot, sAppKeyName);

                if (RegOpenKeyEx(startHKey, sSubKey, 0, KEY_ALL_ACCESS, &hAppKey) != ERROR_SUCCESS)
                {
                    RegCloseKey(hAppKey);
                    RegCloseKey(hUninstKey);
                }
               
                dwBufferSize = sizeof(sDisplayName);
                if (RegQueryValueEx(hAppKey, L"DisplayName", NULL,
                    &dwType, (unsigned char*)sDisplayName, &dwBufferSize) == ERROR_SUCCESS)
                {
                    dwBufferSize = sizeof(sUninstallPath);
                    if (RegQueryValueEx(hAppKey, L"UninstallString", NULL,
                        &dwType, (unsigned char*)sUninstallPath, &dwBufferSize) == ERROR_SUCCESS)
                    {
                        uninstallVector.push_back(uninstall(sUninstallPath, sDisplayName, sAppKeyName, startHKey, dwByte));
                        wprintf(L"%s\n", sDisplayName);
                    }
                }
                RegCloseKey(hAppKey);
            }
        }
    }
    RegCloseKey(hUninstKey);

    std::cout << uninstallVector.size();
}

int main()
{      
    App_X32_X64();
    App_user();   
}


