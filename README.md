# CLog

CLog - Это библиотека для отладки и устранения багов в приложениях/плагинах.

Примеры:
```cpp
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
```
В итоге:
```log
TestPlugin started!
My contact: vk.com/tim4ukys or tim4ukys.dev@yandex.ru

[12:35:09.931]: Hello world! My age: 15
[12:35:09.932]:  
[12:35:09.933]: Destory...
```

## Contacts

ВКонтакте - vk.com/tim4ukys

Email - tim4ukys.dev@yandex.ru