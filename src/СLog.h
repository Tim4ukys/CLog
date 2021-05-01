/*
	This is a CLog project file.
	Developer: mod_s0beit_sa 
	
	See more here https://github.com/BlastHackNet/mod_s0beit_sa-1
*/
#pragma once
#include <Windows.h>
#include <stdio.h>  

class CLog
{
public:
	CLog(const char* FileName, const char* PluginName);
	~CLog();

	void					Write(const char* fmt, ...);
	const char* 			cp1251_to_utf8(const char* str);

private:
	const char*				stFileName;
	char					g_szWorkingDirectory[MAX_PATH];
	
	FILE*					g_flLog = NULL;
	FILE*					g_flLogAll = NULL;
};
