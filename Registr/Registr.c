#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <time.h>

HANDLE hConsole;

main()
{
	system("chcp 1251>nul");
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csb;
	GetConsoleScreenBufferInfo(hConsole, &csb);
	
	SHORT a = 12;
	COORD CORD = { a,a };
	csb.dwSize = CORD;
	SetConsoleTextAttribute(hConsole, csb.wAttributes);
	
	HKEY hKey = NULL;
	if (RegOpenKeyW(HKEY_CURRENT_USER, NULL, &hKey) != ERROR_SUCCESS)//открывает раздел HKEY_CURRENT_USER
	{
		return 0;
	}
	HKEY tmp = NULL;
	if (RegCreateKey(hKey, L"MyKey", &tmp) == ERROR_SUCCESS)//создаем ключ
	{
	}
	LPDWORD DataType = NULL;
	LPDWORD Datalen = 512;
	LPWSTR StrValue = malloc(1);
	if (RegGetValueW(hKey, L"MyKey", L"MyStrParam1", RRF_RT_ANY, &DataType, StrValue, &Datalen) == ERROR_SUCCESS)
	{
		
	}
	else
	{
		MessageBoxA(NULL, "Что-то пошло не так", "Информация", MB_OK);
	}


	if (StrValue[0] == 'r')
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
	if (StrValue[0] == 'g')
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN |  FOREGROUND_INTENSITY);
	}
	printf("%s", "так надо\n");
	LPSTR str = calloc(100, 1);
	scanf_s("%s", str);
	sprintf(str, "%s", str);
	DWORD StrParamLen = wcslen(str);
	if (RegSetValueExA(tmp, "MyStrParam1", NULL, REG_SZ, str, StrParamLen * sizeof(WCHAR)) == ERROR_SUCCESS)
	{
		MessageBoxA(NULL, "Числовой параметр успешно создан и ему присвоено значение", "Информация", MB_OK);

	}
	time_t  ttime = time(NULL);
	LPSTR str1 = calloc(100, 1);
	sprintf(str1, "%s", asctime(localtime(&ttime)));
	DWORD StrParamLen1 = wcslen(str1);
	if (RegSetValueExA(tmp, "MyStrParam", NULL, REG_SZ, str1, StrParamLen1 * sizeof(WCHAR)) == ERROR_SUCCESS)
	{
		MessageBoxA(NULL, "Числовой параметр успешно создан и ему присвоено значение", "Информация", MB_OK);
	}
	LPDWORD DataType1 = NULL;
	LPDWORD Datalen1 = 512;
	LPWSTR StrValue1 = malloc(512);
	if (RegGetValueW(hKey, L"MyKey", L"MyStrParam", RRF_RT_ANY, &DataType1, StrValue1, &Datalen1) == ERROR_SUCCESS)
	{
		MessageBox(NULL, StrValue1, L"Значение параметра", MB_OK);
	}
	else
	{
		MessageBoxA(NULL, "Что-то пошло не так", "Информация", MB_OK);
	}
	RegCloseKey(tmp);
	RegCloseKey(hKey);
	return 0;
}