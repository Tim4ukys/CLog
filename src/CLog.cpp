/********************************************************
*                                                       *
*   Greets:                                             *
*    m0d_s0beit: FYP, NarutoUA, we_sux and other...     *
*                                                       *
*   Credits: Tim4ukys. All rights reserved.             *
*                                                       *
********************************************************/
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
	TCHAR szPath[MAX_PATH]{};
	GetProcessImageFileName(hProc, szPath, sizeof(szPath));
	CloseHandle(hProc);
	TCHAR szTitle[MAX_PATH]{};


	GetFullPathNameA(szTitle, sizeof(szPath), szPath, NULL);
	int str_len = strlen(szPath) - strlen(szTitle);
	for (int i = 0; i < (str_len + 1); i++)
	{
		if (str_len == i)
			/*
				'\0' - нулевой знак, тоже самое что и 0 или NULL.
				Если его не поставить, то это будет не строка - а простой массив
				символов. Этот символ символизирует о конце строки и вообще строка ли эта.
				Если его не поставить, то все функции которые будут с ним работать уйдут 
				за пределы массива, а там уже как повезёт. Если за масивом будет 0, то повезло,
				а вот если нет...
			*/
			this->g_szWorkingDirectory[i] = '\0';
		else
			this->g_szWorkingDirectory[i] = szPath[i];
	}
	this->Write("Compiled: %s CL:%d", COMPILE_DT, COMPILE_VERSION);

	/*
		Почему "t_WindowsInfo*"? Нам нужно прочесть данные из процесса игры 
		и по этому мы ставим знак * говоря компилятору, что это Указатель и 
		задаём ему значение, где именно нужно смотреть. 
		Но, чтобы прочитать данные из памяти через указателя, нужно поставить
		перед ним ещё раз такой знак *, но с начало, нужно скобками показать приоретет, 
		т.е. сказать компилятору что это всё таки указатель. 
		Простым языком запись 1) полностью эквивалентен записи 2):
		1) t_WindowsInfo* = 0xC9AC08;
		   t_WindowsInfo WindowsInfo = *t_WindowsInfo;
		2) t_WindowsInfo WindowsInfo = *(t_WindowsInfo*)0xC9AC08;
		Но, т.к. наша структура имеет размер 16 байт, лучше всего использовать указатель,
		т.к. в большенстве случаев он будет весить 4 байт или 8(как повизёт), ведь он хранит
		только адрес от куда ему нужно читать информацию, а ведь зачем нам создавать точно
		такую же переменную, которая уже как бы созданна в самой игре? 
		По этому я буду использовать Указатель, а не переменную как было выше.
	*/
	// Эти данные нужны чтобы по логу можно было узнать какая система стоит у чела.
	t_WindowsInfo* WindowsInfo = reinterpret_cast<t_WindowsInfo*>(0xC9AC08);

	if (WindowsInfo->osPlatform == 2)
		this->Write("OS: Windows Version %d.%d.%d", WindowsInfo->winMajor, WindowsInfo->winVer, WindowsInfo->osVer);
	else
		this->Write("OS: Not Windows (%d.%d.%d)", WindowsInfo->winMajor, WindowsInfo->winVer, WindowsInfo->osVer);
}

CLog::~CLog()
{
	this->Write("Exited\n");

	if (g_flLog != NULL)
	{
		//fclose(g_flLog);
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
		_snprintf(filename, sizeof(filename), "%s\\%s", this->g_szWorkingDirectory, this->stFileName);

		fopen_s(&g_flLog, filename, "w");
		if (g_flLog == NULL)
			return;
		fclose(g_flLog);
	}
	fopen_s(&g_flLog, filename, "a");
	if (g_flLog)
	{
		GetLocalTime(&time);
		fprintf_s(g_flLog, "[%02d:%02d:%02d.%03d] ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
		va_start(ap, fmt);
		vfprintf_s(g_flLog, fmt, ap);
		va_end(ap);

		fprintf(g_flLog, "\n");
		fflush(g_flLog);
	}
	fclose(g_flLog);
}

#if PSAPI_VERSION == 1 
#pragma comment(lib, "Psapi.lib")
#else
#pragma comment(lib, "Kernel32.lib")
#endif // PSAPI_VERSION == 1 
