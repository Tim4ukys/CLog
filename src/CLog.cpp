/*
	This is a CLog project file.
	Developer: mod_s0beit_sa 
	
	See more here https://github.com/BlastHackNet/mod_s0beit_sa-1
*/
#include "Log.h"
#include <psapi.h>

#define COMPILE_DT (__DATE__ " " __TIME__)
#define COMPILE_VERSION _MSC_VER

struct t_WindowsInfo
{
	int osPlatform;
	int osVer;
	int winVer;
	int winMajor;
};

CLog::CLog(const char* FileName)
{
	this->stFileName = FileName;

	const HWND hForeground = GetForegroundWindow();
	DWORD dwPID = 0;
	GetWindowThreadProcessId(hForeground, &dwPID);

	const HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwPID);
	TCHAR szPath[MAX_PATH];
	GetProcessImageFileName(hProc, szPath, sizeof(szPath));
	CloseHandle(hProc);
	TCHAR szTitle[MAX_PATH];


	GetFullPathNameA(szTitle, sizeof(szPath), szPath, NULL);
	int str_len = strlen(szPath) - strlen(szTitle);
	for (int i = 0; i < (str_len + 1); i++)
	{
		if (str_len == i)
			this->g_szWorkingDirectory[i] = '\0';
		else
			this->g_szWorkingDirectory[i] = szPath[i];
	}
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
		_snprintf(filename, sizeof(filename), "%s\\%s", this->g_szWorkingDirectory, this->stFileName);

		fopen_s(&g_flLog, filename, "w");
		if (g_flLog == NULL)
			return;
	}

	GetLocalTime(&time);
	fprintf_s(g_flLog, "[%02d:%02d:%02d.%03d] ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	va_start(ap, fmt);
	vfprintf_s(g_flLog, fmt, ap);
	va_end(ap);

	fprintf(g_flLog, "\n");
	fflush(g_flLog);
}


#if PSAPI_VERSION == 1 
#pragma comment(lib, "Psapi.lib")
#else
#pragma comment(lib, "Kernel32.lib")
#endif // PSAPI_VERSION == 1 

