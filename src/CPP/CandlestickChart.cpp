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

#include <QPainter>
#include <iostream>


CandlestickChart::CandlestickChart(QQuickItem *parent)
  : QQuickPaintedItem(parent)
{
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
        global_string = ChartLib::candleChunk(ticker.toStdString(), dateOffset());
        m_ticker = ticker;
        update();
        emit tickerChanged();
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


void CandlestickChart::drawXAxis(QPainter *painter)
{
    QDate date = QDate::currentDate();

    // Get candle data from Alpaca so that we can draw our candles.
    CandleData candle_data;
    candle_data = ChartLib::candleData();

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
