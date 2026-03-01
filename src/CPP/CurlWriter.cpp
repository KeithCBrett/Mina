// CurlWriter is one of the prerequisite function implementations needed to
// make curl work in C++. It is used to write the data that we receive from
// whatever server we are pulling data from.

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
#include "CurlWriter.hpp"


namespace action
{
	size_t CurlWriter (char *data, size_t size, size_t nmemb,
			std::string *writer_data)
	{
		if (writer_data == NULL)
		{
			return 0;
		}

		writer_data->append (data, (size * nmemb));

		return (size * nmemb);
	}
}
