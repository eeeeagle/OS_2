#include "Math.hpp"
#include <string>

void calc(CRITICAL_SECTION& cs)
{
	EnterCriticalSection(&cs_wait_2);
	LeaveCriticalSection(&cs);
	while (cs_wait_2.LockCount != -1);
	LeaveCriticalSection(&cs_wait_1);
}

int main()
{
	CreateDirectoryW(path_temp, NULL);

	double values[VALUE_NUM]{};
	{
		std::cout << "Enter values:" << '\n';
		std::string buffer;
		for (unsigned i = 0; i < VALUE_NUM; i++)
		{
			std::cout << "x_" << i + 1 << " = ";
			std::cin >> buffer;
			values[i] = std::stod(buffer);
		}
		std::cout << '\n';
	}

	HANDLE file_values = CreateFileW(path_values, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD written_bytes = 0;
	WriteFile(file_values, values, sizeof(values), &written_bytes, NULL);
	CloseHandle(file_values);

	InitializeCriticalSection(&cs_wait_1);
	InitializeCriticalSection(&cs_wait_2);
	InitializeCriticalSection(&cs_sum_1);
	InitializeCriticalSection(&cs_sum_2);
	InitializeCriticalSection(&cs_div_1);
	InitializeCriticalSection(&cs_div_2);
	InitializeCriticalSection(&cs_sub);
	InitializeCriticalSection(&cs_sqr);

	EnterCriticalSection(&cs_sum_1);
	EnterCriticalSection(&cs_sum_2);
	EnterCriticalSection(&cs_div_1);
	EnterCriticalSection(&cs_div_2);
	EnterCriticalSection(&cs_sub);
	EnterCriticalSection(&cs_sqr);

	DWORD id_sum_1;
	DWORD id_div_1;
	DWORD id_sub;
	DWORD id_sqr;
	DWORD id_sum_2;
	DWORD id_div_2;

	CreateThread(NULL, 0, &Sum_1, NULL, 0, &id_sum_1);
	CreateThread(NULL, 0, &Div_1, NULL, 0, &id_div_1);
	CreateThread(NULL, 0, &Sub,	  NULL, 0, &id_sub);
	CreateThread(NULL, 0, &Sqr,	  NULL, 0, &id_sqr);
	CreateThread(NULL, 0, &Sum_2, NULL, 0, &id_sum_2);
	CreateThread(NULL, 0, &Div_2, NULL, 0, &id_div_2);

	calc(cs_sum_1);
	calc(cs_div_1);
	calc(cs_sub);
	calc(cs_sqr);
	calc(cs_sum_2);
	calc(cs_div_2);

	HANDLE file_res = CreateFileW(path_div_2, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE mapping_res = CreateFileMappingW(file_res, 0, PAGE_READONLY, 0, 0, NULL);
	if (mapping_res == 0)
		ExitProcess(-9);

	double* res = (double*)MapViewOfFile(mapping_res, FILE_MAP_READ, 0, 0, NULL);
	if (res == nullptr)
		ExitProcess(-10);

	std::cout << '\n' << '\n' << "Res value = " << *res << '\n';
	UnmapViewOfFile(res);
	CloseHandle(file_res);
	CloseHandle(mapping_res);
	
	system("pause");

	DeleteFileW(path_values);
	DeleteFileW(path_sum_1);
	DeleteFileW(path_sum_2);
	DeleteFileW(path_div_1);
	DeleteFileW(path_div_2);
	DeleteFileW(path_sub);
	DeleteFileW(path_sqr);

	RemoveDirectoryW(path_temp);
	return 0;
}