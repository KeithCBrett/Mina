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
#include "CurlInit.hpp"
#include <curl/curl.h>

// Curl write function
#include "CurlWriter.hpp"


namespace action {
	static char curl_error_buffer[CURL_ERROR_SIZE];

	std::string stock_data_buffer;
	std::string *p_stock_data_buffer = &stock_data_buffer;

	std::string error_string = "";
	std::string *p_error_string = &error_string;

	std::string *CurlInit
		(CURL *&curl, std::string url, struct curl_slist *headers)
	{
		CURLcode result;

		curl = curl_easy_init ();
		if (!curl)
		{
			fprintf (stderr, "Failed to create CURL handle.\n");
			return p_error_string;
		}

		result = curl_easy_setopt
			(curl, CURLOPT_ERRORBUFFER, curl_error_buffer);
		if (result != CURLE_OK)
		{
			fprintf
				(stderr,
				 "Failed to set error buffer [%d].\n",
				 result);
			return p_error_string;
		}

		result = curl_easy_setopt
			(curl, CURLOPT_CUSTOMREQUEST, "GET");
		if (result != CURLE_OK)
		{
			fprintf
				(stderr,
				 "Failed to set custom curl request [%s].\n",
				 curl_error_buffer);
			return p_error_string;
		}

		result = curl_easy_setopt
			(curl, CURLOPT_WRITEFUNCTION, CurlWriter);
		if (result != CURLE_OK)
		{
			fprintf
				(stderr,
				 "Failed to set writer [%s].\n",
				 curl_error_buffer);
			return p_error_string;
		}

		result = curl_easy_setopt
			(curl, CURLOPT_WRITEDATA, &stock_data_buffer);
		if (result != CURLE_OK)
		{
			fprintf
				(stderr,
				 "Failed to set write data [%s].\n",
				 curl_error_buffer);
			return p_error_string;
		}

		result = curl_easy_setopt
			(curl, CURLOPT_URL, url.c_str ());
		if (result != CURLE_OK)
		{
			fprintf
				(stderr,
				 "Failed to set URL [%s].\n",
				 curl_error_buffer);
			return p_error_string;
		}

		result = curl_easy_setopt
			(curl, CURLOPT_HTTPHEADER, headers);
		if (result != CURLE_OK)
		{
			fprintf
				(stderr,
				 "Failed to set headers [%s].\n",
				 curl_error_buffer);
			return p_error_string;
		}

		return p_stock_data_buffer;
	}
}
