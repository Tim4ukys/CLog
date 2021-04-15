#pragma once
#include <Windows.h>
#include <stdio.h>  

class CLog
{
public:
	CLog(const char* FileName, const char* PluginName);
	~CLog();

	void					Write(const char* fmt, ...);

private:
	const char*				stFileName;
	char					g_szWorkingDirectory[MAX_PATH];

	FILE*					g_flLog = NULL;
	FILE*					g_flLogAll = NULL;
};
