#include <iostream>
#include "CLog.hpp"

CLog* pLog = nullptr;

#define SAFE_DELETE(pointer) if (pointer) { delete pointer; pointer = nullptr; }

int main()
{
	pLog = new CLog(L"logger.log");

	pLog->Log("Hello world! My age: %d", 15);

	SAFE_DELETE(pLog);
	return 0;
}