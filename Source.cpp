/*
	BDJM

	B Ц потоки одного процесса;
	D Ц критические секции;
	J Ц файлы, отображаемые в пам€ть;
	M - выборочна€ дисперси€ трех чисел;
*/

#include "Source.hpp"
#include <string>


int main()
{
	double values[VALUE_NUM]{};
	{
		std::cout << "Enter values:\n";
		std::string buffer;
		for (unsigned i = 0; i < VALUE_NUM; i++)
		{
			std::cout << "x_" << i + 1 << " = ";
			std::cin >> buffer;
			values[i] = std::stod(buffer);
		}
	}
		
	HANDLE file_values = CreateFileW(values_path, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD written_bytes = 0;
	WriteFile(file_values, values, sizeof(values), &written_bytes, NULL);

	SumParams param_sum_a{	values_path, sum_a_path };
	SumParams param_sum_b{	   sqr_path, sum_b_path };

	DivParams param_div_a{ sum_a_path, div_a_path, VALUE_NUM };
	DivParams param_div_b{ sum_b_path, div_b_path,         2 };

	InitializeCriticalSection(&cs_sum);
	InitializeCriticalSection(&cs_div);
	InitializeCriticalSection(&cs_sub);
	InitializeCriticalSection(&cs_sqr);

	DWORD info_sum_a;
	DWORD info_div_a;
	DWORD info_sub;
	DWORD info_sqr;
	DWORD info_sum_b;
	DWORD info_div_b;

	CreateThread(NULL, 0, &Sum, (LPVOID)&param_sum_a, 0, &info_sum_a);
	CreateThread(NULL, 0, &Div, (LPVOID)&param_div_a, 0, &info_div_a);
	CreateThread(NULL, 0, &Sub,					NULL, 0, &info_sub);
	CreateThread(NULL, 0, &Sqr,					NULL, 0, &info_sqr);
	CreateThread(NULL, 0, &Sum, (LPVOID)&param_sum_b, 0, &info_sum_b);
	CreateThread(NULL, 0, &Div, (LPVOID)&param_div_b, 0, &info_div_b);

	HANDLE file_res = CreateFileW(div_b_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE mapping_res = CreateFileMappingW(file_res, 0, PAGE_READONLY, 0, 0, NULL);
	double* res = (double*)MapViewOfFile(mapping_res, PAGE_READONLY, 0, 0, NULL);

	return 0;
}