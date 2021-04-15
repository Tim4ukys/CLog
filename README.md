# CLog

## Russian
CLog - Это библиотека для работы с `Log` файлами. 

Примеры:
```cpp
CLog*       pLog;

char DLL_NAME[] = "GachiTV.ASI";
char LOG_NAME[] = "GachiTV.LOG";

/*
  В CLog.cpp в IS_GTA_SA вместо 1 поставте любое другое число если log не используется
  в gta_sa.exe
*/
pLog = new CLog(LOG_NAME, DLL_NAME); // Инициализируем библиотеку  

pLog->Write("Это Саид? Позови Саида там..."); // Пишем охуительные истории...
pLog->Write("Ты долг когда отдашь? Мы договаривались, что ты вернёшь долг у Отеля..."); 

delete pLog; // Выгружаем библиотеку
```

## Credits & Greets
[Mod s0beit](https://github.com/BlastHackNet/mod_s0beit_sa-1) - Здесь взял саму реализацию log

[Tim4ukys](vk.com/tim4ukys) - Это я. Вытащил работу с log файлами в отдельный файл и создал библеотеку
для работы с ним
