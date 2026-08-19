// CandlestickChart.cpp represents the class implementation for the bar chart seen on
// the 'Browse' page.

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


#include "../../include/CandlestickChart.hpp"

#include "../CPP/ChartLib.cpp"

// We need curl to get stock data from our API
#include "../include/CurlInit.hpp"
#include <curl/curl.h>

#include <QPainter>
#include <iostream>


CandlestickChart::CandlestickChart(QQuickItem *parent)
  : QQuickPaintedItem(parent)
{
}


CandlestickChart chart;
std::string global_string = chart.candleChunk("AAPL");


QColor CandlestickChart::borderColor() const
{
    return m_borderColor;
}


void CandlestickChart::setBorderColor(const QColor &borderColor)
{
    m_borderColor = borderColor;
}


double CandlestickChart::min() const
{
    return m_min;
}


void CandlestickChart::setMin(const double &min)
{
    if (m_min != min)
    {
        m_min = min;
        update();
        emit minChanged();
    }
}


double CandlestickChart::max() const
{
    return m_max;
}


void CandlestickChart::setMax(const double &max)
{
    if (m_max != max)
    {
        m_max = max;
        update();
        emit maxChanged();
    }
}


QString CandlestickChart::ticker() const
{
    return m_ticker;
}


void CandlestickChart::setTicker(const QString &ticker)
{
    if (m_ticker != ticker)
    {
        global_string = candleChunk(ticker.toStdString());
        m_ticker = ticker;
        update();
        emit tickerChanged();
    }
}


qint64 CandlestickChart::dateOffset() const
{
    return m_dateOffset;
}


void CandlestickChart::setDateOffset(const qint64 &dateOffset)
{
    if (dateOffset != m_dateOffset)
    {
        m_dateOffset = dateOffset;
        update();
        emit dateOffsetChanged();
    }
}


// Draws the lines small lines and dollar amounts associated with the y-axis.
void CandlestickChart::drawYAxis(QPainter *painter)
{
    for (int i = 1 ; i <= NUM_Y_AXIS_ELEMENTS ; i++)
    {
        // Draw axis marking.
        painter->drawLine(width() - 5, (height() / (NUM_Y_AXIS_ELEMENTS + 1) * i),
                            width(), (height() / (NUM_Y_AXIS_ELEMENTS + 1) * i));
    }
}


// Checks if a given day is a weekend. Useful because we need to ommit weekends
// from our chart.
bool isWeekend(QDate date)
{
    bool out = false;
    int day = date.dayOfWeek();

    if (day == 6)
    {
        out = true;
    }

    if (day == 7)
    {
        out = true;
    }

    return out;
}


void CandlestickChart::drawXAxis(QPainter *painter)
{
    QDate date = QDate::currentDate();

    // Get candle data from Alpaca so that we can draw our candles.
    CandleData candle_data;
    candle_data = candleData();

    // For when its a weekend.
    int weekend_offset = 0;

    QDate temp_date = date;

    if ((temp_date.dayOfWeek() == 6) || (temp_date.dayOfWeek() == 7))
    {
        weekend_offset += 2;
    }

    for (int i = 1 ; i <= NUM_X_AXIS_ELEMENTS ; i++)
    {
        // Draw axis mark to screen.
        painter->drawLine(width() / NUM_X_AXIS_ELEMENTS * i, (height() - 7),
                        width() / NUM_X_AXIS_ELEMENTS * i, height());

        // Draw candle to screen.
        if (i <= (NUM_X_AXIS_ELEMENTS - 1))
        {
            drawCandle(candle_data.high[i], candle_data.low[i], candle_data.open[i],
                        candle_data.close[i], i, painter);
        }

        temp_date = date.addDays(-(i + weekend_offset));

        if ((temp_date.dayOfWeek() == 7) || (temp_date.dayOfWeek() == 6))
        {
            weekend_offset += 2;
            temp_date = date.addDays(-(i + weekend_offset));
        }

        // Draw date to screen.
        if ((i % 10 == 0) && (i <= NUM_X_AXIS_ELEMENTS - 10))
        {
            painter->drawText((width() - ((width() / NUM_X_AXIS_ELEMENTS * i)
                                            - width() * 0.0092) - width() / 27),
                                height() * 0.99, temp_date.toString("MM/dd"));
        }
    }
}


// Draws a ticker to our candlestick chart.
void CandlestickChart::drawTicker(QPainter *painter, QString ticker)
{
    // We don't want this function to mess with our other drawing functions.
    QPainter *restore_painter = painter;

    QFont local_font = painter->font();

    local_font.setPointSize(22);

    painter->setFont(local_font);

    painter->drawText(25, 50, ticker);

    painter = restore_painter;
}


// If we were to try to get data for say 100 days from the past, we would be
// off by a significant amount (because QDate counts weekends but our candle
// data has no such weekends). This algorithm would return 100 + however many
// days we need to skip due to weekends.
size_t CandlestickChart::offsetStep(size_t inp_step)
{
    // Lowest the input will be is 1. This algorithm expects a lowest of 0.
    inp_step--;

    QDate curr_day = QDate::currentDate();
    curr_day = curr_day.addDays(-m_dateOffset);

    size_t temp_input = inp_step;

    // Tracks how far back we are from the present. Progress 100 means context
    // 100 days prior.
    size_t progress = 0;

    // Tracks number of weekends.
    size_t offset = 0;

    // If we are on a weekend, we have to start with a weekend offset.
    if (weekend(curr_day))
    {
        offset = 2;
    }
    else
    {
        offset = 0;
    }

    // Travel inp_step steps omitting weekends.
    while (inp_step != 0)
    {
        // If current day is not a weekend.
        if (!weekend(curr_day.addDays(-(offset + progress))))
        {
            // Then we have made progress.
            inp_step--;
            progress++;
        }
        else
        {
            // Otherwise we haven't made progress so we must note the fact.
            offset += 2;
        }
    }

    // Handle final/current day.
    if (weekend(curr_day.addDays(-(offset + progress))))
    {
        offset += 2;
    }
    else
    {
        offset += 0;
    }

    return (temp_input + offset);
}


// Helper to check whether or not a given day is a weekend. We need this so that
// we can make QDate addDays() skip weekends.
bool CandlestickChart::weekend(QDate inp_date)
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
QDate CandlestickChart::startDate(QDate end_date)
{
    size_t offset;

    if (weekend(end_date))
    {
        offset = offsetStep(105);
    }
    else
    {
        offset = offsetStep(105 + 1);
    }

    QDate start_date = end_date;

    start_date = start_date.addDays(-(offset - 1));

    return start_date;
}


// This function will either return today or (if today is a weekend) today - 2.
QDate CandlestickChart::endDate()
{
    QDate end_date = QDate::currentDate();
    end_date = end_date.addDays(-m_dateOffset);

    while (weekend(end_date))
    {
        end_date = end_date.addDays(-1);
    }

    return end_date;
}


// Returns a chunk of stock data to parse.
std::string CandlestickChart::candleChunk(std::string ticker)
{
    QDate end_date = endDate();
    QDate start_date = startDate(end_date);
    const char *printstr = qPrintable(end_date.toString());

    std::string my_key = "APCA-API-KEY-ID: PKVOZ3RYLJ3RUPWOAIQKFEMG4F";
    std::string my_secret = "APCA-API-SECRET-KEY: 8vHFEREYTc2C11SAWTPds7zs"
        "ojwbHmJgruv7DtYxPiHW";

    std::string url = callString(start_date, end_date, ticker);

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


double CandlestickChart::getMin()
{
    // We dont care about the first 16 chars.
    size_t index = 16;
    char c = global_string[index];

    double minimum = 999999.99;
    double value = 0;

    // To capture the numbers we will need to know the distance to the nearest
    // comma.
    size_t comma_distance = 0;

    while (c != ']')
    {
        switch (c)
        {
            case 'c':
                // Get to first number (skip quote and colon).
                index += 3;
                c = global_string[index];

                // Capture double value.
                comma_distance = global_string.find_first_of(',', index);
                value = std::stod(global_string.substr(index, comma_distance));

                if (value < minimum)
                {
                minimum = value;
                }

                break;
            case 'h':
                // Get to first number (skip quote and colon).
                index += 3;
                c = global_string[index];

                // Capture double value.
                comma_distance = global_string.find_first_of(',', index);
                value = std::stod(global_string.substr(index, comma_distance));

                if (value < minimum)
                {
                minimum = value;
                }

                break;
            case 'l':
                // Get to first number (skip quote and colon).
                index += 3;
                c = global_string[index];

                // Capture double value.
                comma_distance = global_string.find_first_of(',', index);
                value = std::stod(global_string.substr(index, comma_distance));

                if (value < minimum)
                {
                minimum = value;
                }

                break;
            case 'o':
                // Get to first number (skip quote and colon).
                index += 3;
                c = global_string[index];

                // Capture double value.
                comma_distance = global_string.find_first_of(',', index);
                value = std::stod(global_string.substr(index, comma_distance));

                if (value < minimum)
                {
                minimum = value;
                }

                break;
            default:
                index++;
                c = global_string[index];

                break;
        }
    }

    return minimum;
}


// Scans our data for the largest number. We use this to generate a Y-axis that
// fits our data neatly.
double CandlestickChart::getMax()
{
    // We dont care about the first 16 chars.
    size_t index = 16;
    char c = global_string[index];

    double maximum = 0.0;
    double value = 0;

    // To capture the numbers we will need to know the distance to the nearest
    // comma.
    size_t comma_distance = 0;

    while (c != ']')
    {
        switch (c)
        {
            case 'c':
                // Get to first number (skip quote and colon).
                index += 3;
                c = global_string[index];

                // Capture double value.
                comma_distance = global_string.find_first_of(',', index);
                value = std::stod(global_string.substr(index, comma_distance));

                if (value > maximum)
                {
                maximum = value;
                }

                break;
            case 'h':
                // Get to first number (skip quote and colon).
                index += 3;
                c = global_string[index];

                // Capture double value.
                comma_distance = global_string.find_first_of(',', index);
                value = std::stod(global_string.substr(index, comma_distance));

                if (value > maximum)
                {
                maximum = value;
                }

                break;
            case 'l':
                // Get to first number (skip quote and colon).
                index += 3;
                c = global_string[index];

                // Capture double value.
                comma_distance = global_string.find_first_of(',', index);
                value = std::stod(global_string.substr(index, comma_distance));

                if (value > maximum)
                {
                maximum = value;
                }

                break;
            case 'o':
                // Get to first number (skip quote and colon).
                index += 3;
                c = global_string[index];

                // Capture double value.
                comma_distance = global_string.find_first_of(',', index);
                value = std::stod(global_string.substr(index, comma_distance));

                if (value > maximum)
                {
                maximum = value;
                }

                break;
            default:
                index++;
                c = global_string[index];

                break;
        }
    }

    return maximum;
}


// Converts QDate so that we can use it to make request to Alpaca server for
// financial data.
std::string CandlestickChart::qDateToAPIDate(QDate inp_date)
{
    QString out_string = inp_date.toString("yyyy-MM-dd");
    return out_string.toStdString();
}


// Creates a string to send to the Alpaca server so that we may obtain financial
// data. Argument ticker decides for which stock we are getting data for.
// Arguments start_date and end_date are used to set the timeframe of data we
// want.
std::string CandlestickChart::callString(QDate start_date, QDate end_date,
                                         std::string ticker)
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

    if (dateOffset() == 0)
    {
        out_string = s1 + ticker + s3 + startPoint + s6;
    }
    else
    {
        out_string = s1 + ticker + s3 + startPoint + s4 + endPoint + s6;
    }

    return out_string;
}


// Parses raw data into a CandleData. CandleData is just a struct that holds
// four arrays. It has an array for high, low, open, and close. With this in
// mind, CandleData c.high[0] represents the high for the first bar of data.
CandleData CandlestickChart::candleData()
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


// This function performs drawing operations to the screen. We call this
// function in a loop to draw all of the candles that appear on our chart.
void CandlestickChart::drawCandle(double high, double low, double open,
                                  double close, int index, QPainter *painter)
{
    // Calculate x position of candle to draw on our chart.
    double candle_x = width() / NUM_X_AXIS_ELEMENTS;
    candle_x = candle_x * index;

    double candle_width = width() / 110;

    // Save pen so we can restore it (we need to change it so we can draw a
    // different color).
    const QPen input_pen = painter->pen();

    // Green and red pen for upswing and downswing respectively.
    QPen up_pen;
    QColor up_color(39, 77, 234);
    up_pen.setColor(up_color);

    QPen down_pen;
    QColor down_color(186, 22, 80);
    down_pen.setColor(down_color);

    if (ChartLib::candleYPoint(open, min(), max(), height(), NUM_Y_AXIS_ELEMENTS)
        > ChartLib::candleYPoint(close, min(), max(), height(),
                                 NUM_Y_AXIS_ELEMENTS))
    {
        // We want to draw green candles so lets do that.
        painter->setPen(up_pen);

        // Draw top wick.
        painter->drawLine(candle_x, ChartLib::candleYPoint
                          (high, min(), max(), height(), NUM_Y_AXIS_ELEMENTS),
                          candle_x, ChartLib::candleYPoint
                          (close, min(), max(), height(), NUM_Y_AXIS_ELEMENTS));

        // Draw candle body.
        painter->drawRect(candle_x - candle_width / 2,
                          ChartLib::candleYPoint
                          (close, min(), max(), height(), NUM_Y_AXIS_ELEMENTS),
                          candle_width, ChartLib::candleLength
                          (ChartLib::candleYPoint
                           (open, min(), max(), height(), NUM_Y_AXIS_ELEMENTS),
                           ChartLib::candleYPoint
                           (close, min(), max(), height(),
                            NUM_Y_AXIS_ELEMENTS)));

        // Draw bottom wick.
        painter->drawLine(candle_x, ChartLib::candleYPoint
                          (low, min(), max(), height(), NUM_Y_AXIS_ELEMENTS),
                          candle_x, ChartLib::candleYPoint
                          (open, min(), max(), height(), NUM_Y_AXIS_ELEMENTS));

        // We are done drawing green candles. Lets restore the pen to how it was.
        painter->setPen(input_pen);
    }
    else
    {
        painter->setPen(down_pen);

        painter->drawLine(candle_x, ChartLib::candleYPoint
                          (open, min(), max(), height(), NUM_Y_AXIS_ELEMENTS),
                          candle_x, ChartLib::candleYPoint
                          (low, min(), max(), height(), NUM_Y_AXIS_ELEMENTS));

        painter->fillRect(candle_x - candle_width / 2, ChartLib::candleYPoint
                          (open, min(), max(), height(), NUM_Y_AXIS_ELEMENTS),
                          candle_width, ChartLib::candleLength
                          (ChartLib::candleYPoint
                           (open, min(), max(), height(), NUM_Y_AXIS_ELEMENTS),
                           ChartLib::candleYPoint
                           (close, min(), max(), height(), NUM_Y_AXIS_ELEMENTS)),
                          down_color);

        painter->drawLine(candle_x, ChartLib::candleYPoint
                          (close, min(), max(), height(), NUM_Y_AXIS_ELEMENTS),
                          candle_x, ChartLib::candleYPoint
                          (high, min(), max(), height(), NUM_Y_AXIS_ELEMENTS));

        painter->setPen(input_pen);
    }
}




void CandlestickChart::paint(QPainter *painter)
{
    QPen pen(m_borderColor, 2);

    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, false);

    // Draw bar chart border.
    QRectF rect(0, 0, width(), height());
    qreal offset = pen.widthF() / 2.0;
    rect.adjust(offset, offset, -offset, -offset);
    painter->drawRect(rect);

    // Paint the axises to the screen.
    drawYAxis(painter);
    drawXAxis(painter);

    // Draw the ticker to the screen.
    drawTicker(painter, ticker());

    QDate date = QDate::currentDate();
}
