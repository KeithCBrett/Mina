// DisplaySynopsis prints name of program, version number, etc to stdout

// Copyright (C) 2026  Keith C Brett (KeithCBrett@gmail.com)

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include "../include/DisplaySynopsis.hpp"

namespace action
{
	int
	DisplaySynopsis (bool inp_unit_test)
	{
		if (!inp_unit_test)
		{
			std::cout << "kcbfin - A Security Analyzer\n";
		}

		unsigned num_commits = GetNumCommits ();
		unsigned num_minor = num_commits / 100;
		unsigned num_patch = num_commits % 100;

		if (num_minor > 9)
		{
			if (num_patch > 9)
			{
				if (!inp_unit_test)
				{
					std::cout << "00." << num_minor << "."
						<< num_patch << "\n\n";
				}
			}
			else
			{
				if (!inp_unit_test)
				{
					std::cout << "00." << num_minor << ".0"
						<< num_patch << "\n\n";
				}
			}
		}
		else
		{
			if (num_patch > 9)
			{
				if (!inp_unit_test)
				{
					std::cout << "00.0" << num_minor << "."
						<< num_patch << "\n\n";
				}
			}
			else
			{
				if (!inp_unit_test)
				{
					std::cout << "00.0" << num_minor << ".0"
						<< num_patch << "\n\n";
				}
			}
		}
		return 0;
	}
}
