/*
	This is a CLog project file.
	Developer: mod_s0beit_sa 
	
	See more here https://github.com/BlastHackNet/mod_s0beit_sa-1
*/
#include "Log.h"
#include <Windows.h>

#define COMPILE_DT (__DATE__ " " __TIME__)
#define COMPILE_VERSION _MSC_VER

struct t_WindowsInfo
{
	int osPlatform;
	int osVer;
	int winVer;
	int winMajor;
};

#include <iostream>

CLog::CLog(const char* FileName, const char* PluginName)
{
	this->stFileName = FileName;

	char chWorkPath[256];
	GetFullPathNameA(PluginName, sizeof(chWorkPath), chWorkPath, NULL);
	int str_len = strlen(chWorkPath) - strlen(PluginName);
	for (int i = 0; i < (str_len + 1); i++)
	{
		if (str_len == i)
			this->g_szWorkingDirectory[i] = '\0';
		else
			this->g_szWorkingDirectory[i] = chWorkPath[i];
	}

	this->Write("Initializing %s", PluginName);
	this->Write("Compiled: %s CL:%d", COMPILE_DT, COMPILE_VERSION);

	// log windows version for people that forget to report it
	t_WindowsInfo			WindowsInfo;

	WindowsInfo.osPlatform = (int)*(DWORD*)0xC9AC08;
	WindowsInfo.osVer = (int)*(DWORD*)0xC9AC0C;
	WindowsInfo.winVer = (int)*(DWORD*)0xC9AC10;
	WindowsInfo.winMajor = (int)*(DWORD*)0xC9AC14;
	if (WindowsInfo.osPlatform == 2)
		this->Write("OS: Windows Version %d.%d.%d", WindowsInfo.winMajor, WindowsInfo.winVer, WindowsInfo.osVer);
	else
		this->Write("OS: Not Windows (%d.%d.%d)", WindowsInfo.winMajor, WindowsInfo.winVer, WindowsInfo.osVer);
}

CLog::~CLog()
{
	this->Write("Exited\n");

	if (g_flLog != NULL)
	{
		fclose(g_flLog);
		g_flLog = NULL;
	}
}

void CLog::Write(const char* fmt, ...)
{
	if (!this->g_szWorkingDirectory) return;

	SYSTEMTIME	time;
	va_list		ap;

	if (g_flLog == NULL)
	{
		char	filename[512];
		snprintf(filename, sizeof(filename), "%s\\%s", this->g_szWorkingDirectory, this->stFileName);

		fopen_s(&g_flLog, filename, "w");
		if (g_flLog == NULL)
			return;
	}

	GetLocalTime(&time);
	fprintf(g_flLog, "[%02d:%02d:%02d.%03d] ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	va_start(ap, fmt);
	vfprintf(g_flLog, fmt, ap);
	va_end(ap);
	fprintf(g_flLog, "\n");
	fflush(g_flLog);
}

const char* CLog::cp1251_to_utf8(const char* str)
{
	std::string res;
	WCHAR* ures = NULL;
	char* cres = NULL;

	int result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0);
	if (result_u != 0)
	{
		ures = new WCHAR[result_u];
		if (MultiByteToWideChar(1251, 0, str, -1, ures, result_u))
		{
			int result_c = WideCharToMultiByte(CP_UTF8, 0, ures, -1, 0, 0, 0, 0);
			if (result_c != 0)
			{
				cres = new char[result_c];
				if (WideCharToMultiByte(CP_UTF8, 0, ures, -1, cres, result_c, 0, 0))
				{
					res = cres;
				}
			}
		}
	}

	delete[] ures;
	delete[] cres;

	return res.c_str();
}
