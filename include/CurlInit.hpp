// CurlInit is a curl helper function. It passes in the proper options to
// curl setup, and return false if an error occured.

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
#ifndef CURL_INIT_H
#define CURL_INIT_H


#include <curl/curl.h>
#include <string>


namespace action {
	std::string *CurlInit
		(CURL *&curl, std::string url, struct curl_slist *headers);
}
#endif
