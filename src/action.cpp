#include "action.h"
#include <cstdint>


namespace action
{
	int
	DisplaySynopsis ()
	{
		std::cout << "kcbfin - A Security Analyzer\n";
		std::cout << "Version: 00.00.00\n";
		return 0;
	}


	uint64_t
	GetNumberStdin (std::string inp_string)
	{
		std::cout << inp_string;
		uint64_t out_num = -1;
		std::cin >> out_num;
		if (out_num == 0)
		{
			out_num = -1;
		}
		return out_num;
	}


	int
	ClearScreen ()
	{
		std::cout << "\033[2J\033[1;1H";
		return 0;
	}


	int
	DisplayResult ()
	{
		return -1;
	}
}
