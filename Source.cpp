#include <iostream>
#include <sstream>
#include <Windows.h>
#define N 3

double str_to_double(const std::string& str)
{
	try
	{
		unsigned long i{ std::stod(str) };
		return i;
	}
	catch (std::invalid_argument const& ex)
	{
		std::cout << "INVALID TYPE: " << std::string(str) << '\n'
			<< "    Value must be double float\n\n"
			<< ex.what() << '\n';
	}
	catch (std::out_of_range const& ex)
	{
		std::cout << "OUT OF RANGE: value = " << std::string(str) << "\n\n"
			<< ex.what() << '\n';
	}
	exit(EXIT_FAILURE);
}

double mathematical_expectation(const double value[3]) /* TO DO - DIVIDE FOR THREADS*/
{
	return (value[0] + value[1] + value[2]) / N;
}

int main(int argc, char** argv)
{
	if (argc != 1 || argc != 4)
	{
		std::cout	<< "Wrong arguments. Use -help to get more information.\n\n"
					<< "EXAMPLE:\n"
					<< "    .../OS_2.exe -help\n\n";
		exit(EXIT_FAILURE);
	}
	if (argc == 2 && argv[1] == std::string("-help"))
	{
		std::cout	<< "Specify 3 values as arguments to peform sample variance of 3 values\n\n"
					<< "EXAMPLE:\n"
					<< "    .../OS_2.exe <value_1> <value_2> <value_3>\n\n";
		exit(EXIT_FAILURE);
	}

	double value[3] = {0, 0, 0};
	if (argc == 4)
	{
		for (unsigned i = 0; i < 3; i++)
		{
			value[i] = str_to_double(argv[i + 1]);
			std::cout << "Read value " << i + 1 << " = " << value[i] << '\n';
		}
	}
	else
	{
		for (unsigned i = 0; i < 3; i++)
		{
			std::cout << "Enter value " << i + 1 << " = ";
			std::cin >> value[i];
		}
	}

	/*
		to do
	
		WRITE FILE
		CREATE THREAD

	*/

	std::cout << "\nPerforming sample variance:\n";

	/*
		to do

		READ FILE
		CLOSE THREAD
		PRINT RESULT

	*/

	return 0;
}