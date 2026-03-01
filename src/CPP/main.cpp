// kcbfin is a equity/security analyzer capable of performing various
// calculations related to valuing businesses and other cash flow producing
// assets

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

// App headers
#include "../include/Ebita.hpp"
#include "../include/CurlInit.hpp"

// GUI headers (Qt)
#include <QtQuick>
#include <QApplication>
#include <QtQml>

// We need curl to get stock data from our API
#include <curl/curl.h>
#include <string>

int
main (int argc, char *argv[])
{
	std::string url = "https://data.alpaca.markets/v2/stocks/AAPL/bars?tim"
		"eframe=1D&start=2024-01-03T00%3A00%3A00Z&end=2024-01-04T00%3A"
		"00%3A00Z&limit=1000&adjustment=raw&feed=sip&sort=asc";

	std::string my_key = "APCA-API-KEY-ID: PKVOZ3RYLJ3RUPWOAIQKFEMG4F";
	std::string my_secret = "APCA-API-SECRET-KEY: 8vHFEREYTc2C11SAWTPds7zs"
		"ojwbHmJgruv7DtYxPiHW";

	std::string *curl_output_buffer;

	CURL *hnd = NULL;

	struct curl_slist *headers = NULL;
	headers = curl_slist_append (headers, "accept: application/json");
	headers = curl_slist_append (headers, my_key.c_str ());
	headers = curl_slist_append (headers, my_secret.c_str ());

	curl_output_buffer = action::CurlInit (hnd, url, headers);
	CURLcode ret = curl_easy_perform (hnd);
	if (curl_output_buffer->empty () == true)
	{
		fprintf (stderr, "Error initializing curl.\n");
	}

	fprintf (stderr, "%s\n", (*curl_output_buffer).c_str ());

	QApplication gui (argc, argv);
	QQmlApplicationEngine engine ("../../src/QML/Main.qml");
	return gui.exec ();
}
