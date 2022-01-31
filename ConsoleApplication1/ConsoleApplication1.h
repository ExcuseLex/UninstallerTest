#pragma once

#include <Windows.h>
#include <string>

class uninstall
{
public:
	std::wstring UninstallPath;
	std::wstring DisplayName;
	std::wstring RegKeyName;
	HKEY RegAppHKEY;
	DWORD DwType;

    uninstall(WCHAR _UninstallPath[1023], WCHAR _DisplayName[1023], WCHAR _RegKeyName[1023], HKEY _RegAppHKEY, DWORD _DwType)
    {
		UninstallPath = _UninstallPath;
		DisplayName = _DisplayName;
		RegKeyName = _RegKeyName;
		RegAppHKEY = _RegAppHKEY;
		DwType = _DwType;
    };
};


