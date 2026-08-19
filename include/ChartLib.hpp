// ChartLib.hpp represents the definitions for ChartLib. ChartLib is a
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


#ifndef CHARTLIB_H
#define CHARTLIB_H


namespace ChartLib {
    // Function for computing the bottom most YAxis number.
    QString firstYAxisNumber(double min);

    // This function computes the distance between Y-axis markings (in dollars,
    // according to chart min and max)
    QString stepSize(double inp_first_axis_number, double min, double max);

    // This function calculates the Y-point for each candle according to chart
    // axis.
    double candleYPoint(double inp_num, double min, double max, double height,
                        size_t num_axis_elements);

    // This function calculates the length of our candlestick body.
    double candleLength(double open, double close);

    // Calculates how far back our starting date is if we have to exclude
    // weekends.
    size_t offsetStep(size_t inp_step, qint64 date_offset);

    // Checks whether or not a given day is a weekend.
    bool weekend(QDate inp_date);

    // This computes the left most date on our chart (earliest). It goes 100 days
    // into the past, skipping weekends.
    QDate startDate(QDate end_date, qint64 date_offset);
}


#endif // CHARTLIB_H
