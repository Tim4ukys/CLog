/*
	This is a CLog project file.
	Developer: mod_s0beit_sa 
	
	See more here https://github.com/BlastHackNet/mod_s0beit_sa-1
*/
#pragma once
#include <Windows.h>
#include <stdio.h>  
#include <iostream>

class CLog
{
public:
	CLog(const char* fileName, const char* fileExtension);
	~CLog();

	void					Write(const char* fmt, ...);
	void					traceLastFunc(const char* szFunc);

	char					g_szLastFunc[256];
	const char*				stFileName;
	const char*				stFileExtension;
private:
	char					g_szWorkingDirectory[MAX_PATH];
	
	FILE*					g_flLog = NULL;
};
