#include "action.h"
#include "get_version_num.h"
#include <cstdint>


namespace action
{
	int
	DisplaySynopsis ()
	{
		std::cout << "kcbfin - A Security Analyzer\n";

		unsigned num_commits = GetNumCommits ();
		unsigned num_minor = num_commits / 100;
		unsigned num_patch = num_commits % 100;

		if (num_minor > 9)
		{
			if (num_patch > 9)
			{
				std::cout << "00." << num_minor << "."
					<< num_patch << "\n\n";
			}
			else
			{
				std::cout << "00." << num_minor << ".0"
					<< num_patch << "\n\n";
			}
		}
		else
		{
			if (num_patch > 9)
			{
				std::cout << "00.0" << num_minor << "."
					<< num_patch << "\n\n";
			}
			else
			{
				std::cout << "00.0" << num_minor << ".0"
					<< num_patch << "\n\n";
			}
		}
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
	DisplayResult (bool inp_unit_test, uint64_t inp_EBITA)
	{
		action::ClearScreen ();
		action::DisplaySynopsis ();
		int error = -1;
		if (inp_EBITA != 0)
		{
			if (!inp_unit_test)
			{
				std::cout << "Ebita: " << inp_EBITA;
				std::cout << "\n";
			}
			error = 0;
		}
		return error;
	}
}
