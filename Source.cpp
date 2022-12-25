/*
	BDJM

	B Ц потоки одного процесса;
	D Ц критические секции;
	J Ц файлы, отображаемые в пам€ть;
	M - выборочна€ дисперси€ трех чисел;
*/

#include "Source.hpp"
#include <string>

constexpr auto VALUE_NUM = 3;

int main()
{
	DWORD info_sum;
	DWORD info_sub;
	DWORD info_div;
	DWORD info_sqrt;
	CreateThread(NULL, 0, &Sum, NULL, 0, &info_sum);
	CreateThread(NULL, 0, &Sub, NULL, 0, &info_sub);
	CreateThread(NULL, 0, &Div, NULL, 0, &info_div);
	CreateThread(NULL, 0, &Sqrt, NULL, 0, &info_sqrt);

	double value[VALUE_NUM]{};
	{
		std::cout << "Enter values:\n";
		std::string buffer;
		for (unsigned i = 0; i < VALUE_NUM; i++)
		{
			std::cout << "x_" << i + 1 << " = ";
			std::cin >> buffer;
			value[i] = std::stod(buffer);
		}
	}

	/*
		to do
	
		???
	*/

	return 0;
}