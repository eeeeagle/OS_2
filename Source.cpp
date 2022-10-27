#include <iostream>
#include <sstream>
#include <Windows.h>
#define N 3

double str_to_double(const std::string& str)
{
	try
	{
		double i{ std::stod(str) };
		return i;
	}
	catch (std::invalid_argument const& ex)
	{
		std::cout	<< "[!] " << ex.what() << " [!]\n"
					<< "INVALID TYPE: " << std::string(str) << '\n'
					<< "    Value must be double float\n\n";
			
	}
	catch (std::out_of_range const& ex)
	{
		std::cout	<< "[!] " << ex.what() << " [!]\n"
					<< "OUT OF RANGE: value = " << std::string(str) << "\n"
					<< "    Avaible value rangemust be double float\n\n";
	}
	exit(EXIT_FAILURE);
}

double mathematical_expectation(const double value[N]) /* TO DO - DIVIDE FOR THREADS*/
{
	return (value[0] + value[1] + value[2]) / N;
}

int main(int argc, char** argv)
{
	if (argc == 2 && std::string(argv[1]) == "-help")
	{
		std::cout	<< "Specify 3 values as arguments to peform sample variance of 3 values\n\n"
					<< "EXAMPLE:\n"
					<< "    .../OS_2.exe <value_1> <value_2> <value_3>\n\n";
		exit(EXIT_SUCCESS);
	}
	else if (argc != 1 && argc != 4)
	{
		std::cout	<< "Wrong arguments. Use -help to get more information.\n\n"
					<< "EXAMPLE:\n"
					<< "    .../OS_2.exe -help\n\n";
		exit(EXIT_FAILURE);
	}

	double value[N] = {0, 0, 0};
	if (argc == 4)
	{
		for (unsigned i = 0; i < N; i++)
		{
			value[i] = str_to_double(argv[i + 1]);
			std::cout << "Read value " << i + 1 << " = " << value[i] << '\n';
		}
	}
	else
	{
		std::string input[N];
		for (unsigned i = 0; i < N; i++)
		{
			std::cout << "Enter value " << i + 1 << " = ";
			std::cin >> input[i];
			value[i] = str_to_double(input[i]);
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