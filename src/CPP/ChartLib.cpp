// ChartLib.cpp represents the implementation for ChartLib. ChartLib is a
// general library that provides utilities useful for drawing charts.

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


#include "../../include/ChartLib.hpp"


// We need curl to get stock data from our API
#include "../include/CurlInit.hpp"
#include <curl/curl.h>

#include <iostream>


#define NUM_WEEKDAYS 7
#define NUM_WEEKENDS 2


std::string global_string = ChartLib::candleChunk("AAPL", 0);


namespace ChartLib {
    // Function for computing the bottom most YAxis number.
    QString firstYAxisNumber(double min)
    {
        if (min <= 0)
        {
            QString out("-1");
            return out;
        }

        double temp = min;
        double integral = 0.05;

        // We only want to return a double for small numbers. Otherwise we would
        // rather work with integers.
        int trunc_temp = 0;

        QString out_string;

        if (temp < 1.0)
        {
            // Here we coerce the output to end in 0 or 5.
            while (((std::modf(temp, &integral)) != 0)
                || ((std::modf(temp, &integral)) != 0.05))
            {
                temp = temp - 0.01;
            }

            out_string = QString::number(temp);
            return out_string;
        }
        else if ((temp >= 1.0) && (temp < 5.0))
        {
            trunc_temp = std::trunc(temp);

            out_string = QString::number(trunc_temp);

            return out_string;
        }
        else
        {
            trunc_temp = std::trunc(temp);

            // Here we coerce the output to be divisible by 5 for aethetic reasons.
            while ((trunc_temp % 5) != 0)
            {
                trunc_temp--;
            }

            out_string = QString::number(trunc_temp);

            return out_string;
        }
    }


    // Function for computing the step size used for computing most of the YAxis
    // numbers.
    QString stepSize(double inp_first_axis_number, double min, double max)
    {
        // Error handling.
        // Bottom axis number should be greater than zero.
        if (inp_first_axis_number <= 0)
        {
            return QString::number(-1);
        }
        // Max should be greater than min.
        if (min >= max)
        {
            return QString::number(-1);
        }
        // Min and max should be greater than zero.
        if ((min <= 0) || (max <= 0))
        {
            return QString::number(-1);
        }

        double step_size = max - min;
        step_size = step_size / NUM_Y_AXIS_ELEMENTS;

        // We try to round to a whole number whenever we can.
        int round_step_size = 0;

        std::string temp_string;

        if (step_size < 0.1)
        {
            // In case of irrational numbers. Truncates 0.0XXXX... to 0.0X.
            temp_string = std::to_string(step_size).substr(0, 4);
            step_size = std::stod(temp_string);

            // Check if axis fits data.
            while (max >= (step_size * (NUM_Y_AXIS_ELEMENTS - 1)
                            + inp_first_axis_number))
            {
                // If not, generate axis of wider range.
                step_size = step_size + 0.01;
            }

            // Axis fits, now we get our step_size to be divisible by five.

            // First we check if we can make the step size evenly divisible by
            // five via subtraction (and have it be greater than or equal to our
            // max). This ensures the lowest step size possible.
            int curr = inp_first_axis_number + (step_size - ((int)step_size % 5)) * 9;
            if (max <= curr)
            {
                step_size = step_size - ((int)step_size % 5);
                return QString::number(step_size);
            }
            // This check is for if a unaltered step size is divisible by five.
            // If thats true and the first if statement fails, then that means
            // that we are already at the lowest step size.
            else if (((int)step_size % 5) == 0)
            {
                return QString::number(step_size);

            }
            // Otherwise we add until divisible by five.
            else
            {
                while (((int)step_size % 5) != 0)
                {
                    step_size++;
                }

                return QString::number(step_size);
            }
        }
        else
        {
            round_step_size = std::round(step_size);

            while (max
            >= (round_step_size * (NUM_Y_AXIS_ELEMENTS - 1)
                + inp_first_axis_number))
            {
                round_step_size++;
            }

            // Axis fits, now we get our step_size to be divisible by five.

            // First we check if we can make the step size evenly divisible by
            // five via subtraction (and have it be greater than or equal to our
            // max). This ensures the lowest step size possible.
            int curr = inp_first_axis_number + (round_step_size
                                                - (round_step_size % 5)) * 9;
            if (max <= curr)
            {
                round_step_size = round_step_size - ((int)round_step_size % 5);
                return QString::number(round_step_size);
            }
            // This check is for if a unaltered step size is divisible by five.
            // If thats true and the first if statement fails, then that means
            // that we are already at the lowest step size.
            else if (((int)round_step_size % 5) == 0)
            {
                return QString::number(round_step_size);

            }
            // Otherwise we add until divisible by five.
            else
            {
                while (((int)round_step_size % 5) != 0)
                {
                    round_step_size++;
                }

                return QString::number(round_step_size);
            }
        }
    }

    // Converts a dollar amount into a Y-point on our candlestick chart according
    // to our axis.
    double candleYPoint(double inp_num, double min, double max, double height,
                        size_t num_axis_elements)
    {
        // Error handling.
        // Price should be greater than zero.
        if (inp_num <= 0)
        {
            return -1;
        }
        // Min should be greater than zero.
        if (min <= 0)
        {
            return -1;
        }
        // Max should be greater than zero.
        if (max <= 0)
        {
            return -1;
        }
        // Height should be greater than zero.
        if (height <= 0)
        {
            return -1;
        }
        if (min >= max)
        {
            return -1;
        }

        double first_y_number = firstYAxisNumber(min).toDouble();
        double step = stepSize(first_y_number, min, max).toDouble();

        double chart_min = first_y_number - step;
        double chart_max = first_y_number + (num_axis_elements * step);

        double out_y = chart_max - chart_min;
        double index = inp_num - chart_min;
        out_y = index / out_y;
        out_y = 1.0 - out_y;

        return (out_y * height);
    }


    // Calculates the length of our candle according to the axis. We will need this
    // when we try to draw a candle with drawRect.
    double candleLength(double open, double close)
    {
        // Error handling.
        // Open should be greater than zero.
        if (open <= 0)
        {
            return -1;
        }
        // Close should be greater than zero.
        if (close <= 0)
        {
            return -1;
        }

        double big;
        double small;

        if (open > close)
        {
            big = open;
            small = close;
            return (big - small);
        }
        else
        {
            big = close;
            small = open;
            return (big - small);
        }
    }


    // If we were to try to get data for say 100 days from the past, we would be
    // off by a significant amount (because QDate counts weekends but our candle
    // data has no such weekends). This algorithm would return 100 + however many
    // days we need to skip due to weekends.
    size_t offsetStep(size_t inp_step, qint64 date_offset)
    {
        // Error handling.
        // We don't allow inp_step greater than 100, this algorithm won't scale
        // well for that (or for big inp_step in general). We loop for each
        // inp_step.
        if (inp_step > 100)
        {
           return -1;
        }

        size_t out_step = 0;

        // original_input + days skipped = output.
        size_t original_input = inp_step;

        // So that we can check if we are on a weekend (to exlude it).
        QDate curr_day = QDate::currentDate();

        // We use inp_step to track our progress.
        while (inp_step > 0)
        {
            // In theory, if we count the days we skip, and add it to our orginal
            // input, this will give us the total distance traveled (which is
            // what we want as output). Since we skip days in which the market is
            // closed, that is what we will count.
            if (!marketOpen(curr_day))
            {
                out_step++;
            }

            // If market wasn't open on the day we are checking, we have to
            // ignore it and move on.
            if (marketOpen(curr_day))
            {
                inp_step--;
            }

            // Get previous day to progress loop.
            curr_day = curr_day.addDays(-1);
        }

        return (out_step + original_input);
    }


    bool marketOpen(QDate inp_date)
    {
        bool out_bool = true;

        // If it's a weekend, the market is closed.
        if (weekend(inp_date))
        {
            return false;
        }

        // TODO Holidays go here.

        return out_bool;
    }


    // Helper to check whether or not a given day is a weekend. We need this so that
    // we can make QDate addDays() skip weekends.
    bool weekend(QDate inp_date)
    {
        if ((inp_date.dayOfWeek() == 6) || (inp_date.dayOfWeek() == 7))
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    // Returns the oldest date we are currently rendering a candle for. We need this
    // for when we make a request for data from Alpaca server.
    QDate startDate(QDate end_date, qint64 date_offset)
    {
        size_t offset;

        if (weekend(end_date))
        {
            offset = offsetStep(100, date_offset);
        }
        else
        {
            offset = offsetStep(100, date_offset);
        }

        QDate start_date = end_date;

        std::cout << "offsetStep: " << offset << "\n";

        start_date = start_date.addDays(-(offset - 1));

        return start_date;
    }


    // This function will either return today or (if today is a weekend) today - 2.
    QDate endDate(qint64 date_offset)
    {
        QDate end_date = QDate::currentDate();
        end_date = end_date.addDays(-date_offset);

        end_date = end_date.addDays(-offsetStep(0, 0));

        return end_date;
    }


    // Returns a chunk of stock data to parse.
    std::string candleChunk(std::string ticker, qint64 date_offset)
    {
        QDate end_date = endDate(date_offset);
        QDate start_date = startDate(end_date, date_offset);
        std::cout << "start_date: " << start_date.toString().toStdString() << "\n";
        const char *printstr = qPrintable(end_date.toString());

        std::string my_key = "APCA-API-KEY-ID: PKVOZ3RYLJ3RUPWOAIQKFEMG4F";
        std::string my_secret = "APCA-API-SECRET-KEY: 8vHFEREYTc2C11SAWTPds7zs"
            "ojwbHmJgruv7DtYxPiHW";

        std::string url = callString(start_date, end_date, ticker, date_offset);

        std::string *curl_output_buffer;
        CURL *hnd = NULL;
        struct curl_slist *headers = NULL;

        headers = curl_slist_append(headers, "accept: application/json");
        headers = curl_slist_append(headers, my_key.c_str());
        headers = curl_slist_append(headers, my_secret.c_str());

        curl_output_buffer = action::CurlInit(hnd, url, headers);
        CURLcode ret = curl_easy_perform(hnd);
        if (curl_output_buffer->empty() == true)
        {
            fprintf(stderr, "Error initializing curl.\n");
        }

        // fprintf(stderr, "%s\n", (*curl_output_buffer).c_str());
        return *curl_output_buffer;
    }


    // Creates a string to send to the Alpaca server so that we may obtain financial
    // data. Argument ticker decides for which stock we are getting data for.
    // Arguments start_date and end_date are used to set the timeframe of data we
    // want.
    std::string callString(QDate start_date, QDate end_date, std::string ticker,
                           qint64 date_offset)
    {
        std::string out_string;

        // Needed for all URLS.
        std::string s1 = "https://data.alpaca.markets/v2/stocks/bars?symbols=";

        // Set timeframe for each bar.
        std::string s3 = "&timeframe=1D&start=";

        std::string startPoint = qDateToAPIDate(start_date);

        std::string s4 = "&end=";

        // End point to get data for.
        std::string endPoint = qDateToAPIDate(end_date);

        std::string s6 = "&limit=1000&adjustment=raw&feed=sip&sort=asc";

        if (date_offset == 0)
        {
            out_string = s1 + ticker + s3 + startPoint + s6;
        }
        else
        {
            out_string = s1 + ticker + s3 + startPoint + s4 + endPoint + s6;
        }

        return out_string;
    }


    // Converts QDate so that we can use it to make request to Alpaca server for
    // financial data.
    std::string qDateToAPIDate(QDate inp_date)
    {
        QString out_string = inp_date.toString("yyyy-MM-dd");
        return out_string.toStdString();
    }


    // Parses raw data into a CandleData. CandleData is just a struct that holds
    // four arrays. It has an array for high, low, open, and close. With this in
    // mind, CandleData c.high[0] represents the high for the first bar of data.
    CandleData candleData()
    {
        CandleData out_data;

        // Current positions for our candle data arrays.
        int high_pos = 0;
        int low_pos = 0;
        int open_pos = 0;
        int close_pos = 0;

        // Stores our position in the raw data.
        int raw_data_index = 0;
        char c = global_string[raw_data_index];

        // In order to lex doubles we are going to use the distance to the nearest
        // comma (so we know when to stop lexing).
        size_t comma_distance = 0;

        // str_value is like value but it lets us do substring stuff (instead of
        // number stuff).
        double value = 0.0;
        std::string str_value = "";

        while (c != ']')
        {
            switch (c)
            {
                case 'c':
                    // Get to first number (skip quote and colon).
                    raw_data_index += 3;
                    c = global_string[raw_data_index];

                    // Capture double value.
                    comma_distance = global_string.find_first_of(',', raw_data_index);
                    value = std::stod(global_string.substr(raw_data_index, comma_distance));

                    // Store value and do array book keeping.
                    out_data.close[close_pos] = value;
                    close_pos++;

                    break;
                case 'h':
                    // Get to first number (skip quote and colon).
                    raw_data_index += 3;
                    c = global_string[raw_data_index];

                    // Capture double value.
                    comma_distance = global_string.find_first_of(',', raw_data_index);
                    value = std::stod(global_string.substr(raw_data_index, comma_distance));

                    // Store value and do array book keeping.
                    out_data.high[high_pos] = value;
                    high_pos++;

                    break;
                case 'l':
                    // Get to first number (skip quote and colon).
                    raw_data_index += 3;
                    c = global_string[raw_data_index];

                    // Capture double value.
                    comma_distance = global_string.find_first_of(',', raw_data_index);
                    value = std::stod(global_string.substr(raw_data_index, comma_distance));

                    // Store value and do array book keeping.
                    out_data.low[low_pos] = value;
                    low_pos++;

                    break;
                case 'o':
                    // Get to first number (skip quote and colon).
                    raw_data_index += 3;
                    c = global_string[raw_data_index];

                    // Capture double value.
                    comma_distance = global_string.find_first_of(',', raw_data_index);
                    value = std::stod(global_string.substr(raw_data_index, comma_distance));

                    // Store value and do array book keeping.
                    out_data.open[open_pos] = value;
                    open_pos++;

                    break;
                default:
                    raw_data_index++;
                    c = global_string[raw_data_index];

                    break;
            }
        }

        return out_data;
    }


    // Function for computing all the YAxis numbers (except the one computed
    // by firstYAxisNumber()).
    QString otherYAxisNumber(double min, double max,
                             double first_axis_number, int position)
    {
        double step_size = stepSize(first_axis_number, min, max).toDouble();
        return QString::number(step_size * (position - 1) + first_axis_number);
    }
}
