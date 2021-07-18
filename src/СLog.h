/********************************************************
*                                                       *
*   Greets:                                             *
*    m0d_s0beit: FYP, NarutoUA, we_sux and other...     *
*                                                       *
*   Credits: Tim4ukys. All rights reserved.             *
*                                                       *
********************************************************/
#pragma once
#include <Windows.h>
#include <stdio.h>  
#include <iostream>

class CLog
{
public:
	CLog(const char* FileName);
	~CLog();

	void					Write(const char* fmt, ...);

private:
	const char*				stFileName;
	char					g_szWorkingDirectory[MAX_PATH];
	
	FILE*					g_flLog = NULL;
	FILE*					g_flLogAll = NULL;
	char					filename[512]{};
};
