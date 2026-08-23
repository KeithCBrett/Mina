// test_candleYPoint.cpp represents the valid and invalid input unit tests
// for function candleYPoint of module ChartLib

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


#include "QtCore"
#include "unit_tests.hpp"


#include "ChartLib.hpp"


// Let us have a chart like so:
//    |                           0 (px)
// 65 |
// 60 |
// 55 |
// 50 |
// 45 |
// 40 |
// 35 |
// 30 |
// 25 |
// 20 |
//     -------------------------- height() (px)
// If we want to draw a point at $55, we face several problems:
// 01. We have our chart so that the axis only ranges from $20 - $65, but this
// is only accounts for a fraction of the chart:
//   - We construct the chart min and max in such a way that we have a
//     padding/buffer area at the top and bottom of the chart, so that data
//     never gets drawn near the bottom or top edges
//   - The height of the chart returns to bottom-most point, padding excluded,
//     so we will have to account for that
// 02. In terms of dollar amount, we don't start at zero which complicates
// things
// 03. The ratio of height to dollar amount is inverted, a largest height of,
// for example, 1080px corresponds to the lowest dollar amount ($15 which isn't
// even rendered)
// We will solve most of these problems by simplifing our chart:
// 01. Here we simplify our chart by extending the chart maximum and minimum:
//
// 70 |                           0 (px)
// 65 |
// 60 |
// 55 |
// 50 |
// 45 |
// 40 |
// 35 |
// 30 |
// 25 |
// 20 |
// 15  -------------------------- height() (px)
//
// 02. To solve this problem, we simplify our chart again:
//   - With our simplification, the chart min and max will change, let the
//   the new min and max be referred to as 'min and 'max
//   - Subract the chart min from every axis value, we will use the above
//   example of $15
//
// 55 |                           0 (px)
// 50 |
// 45 |
// 40 |
// 35 |
// 30 |
// 25 |
// 20 |
// 15 |
// 10 |
// 05 |
// 00  -------------------------- height() (px)
// With these transformations, getting our y-point is easy, let's use $55
// as the value we want a y-point for, and let the height of the chart be
// 1080 pixels:
// 1. Since we adjusted our chart, we will need to adjust our input in the
// same way:
//   'INPUT = INPUT - min
//   'INPUT = $55 - $15
//   'INPUT = $40
// 2. Now let the following be true:
//   k = 'INPUT / 'max
//   k = $40 / $55
//   k = 0.727273
// 3. Convert to pixels and invert to solve problem 3 in our intro:
//   OUTPUT = height() * (1.0 - k)
//   OUTPUT = 1080px * (1.0 - 0.727273)
//   OUTPUT = 1080px * 0.272727
//   OUTPUT = 294.545


TEST (CandleYPointValidInp, ChartTests)
{
    // This represents the stock price we are trying to find a Y-point for.
    double price = 55;
    double min = 20.0;
    double max = 65.0;
    // The height of our chart object in pixels.
    double height = 1080;
    int num_axis_elements = 10;
    double result = ChartLib::candleYPoint(price, min, max, height,
                                           num_axis_elements);
    double expected = 294.545454545454545;
    EXPECT_DOUBLE_EQ(result, expected);

    price = 222.0;
    min = 120;
    max = 300;
    result = ChartLib::candleYPoint(price, min, max, height, num_axis_elements);
    expected = 481.090909090909;
    EXPECT_DOUBLE_EQ(result, expected);

    price = 163.025;
    min = 121.99;
    max = 259.92;
    result = ChartLib::candleYPoint(price, min, max, height, num_axis_elements);
    expected = 770.60454545454547;
    EXPECT_DOUBLE_EQ(result, expected);

    price = 92.8;
    min = 40.63;
    max = 142.35;
    result = ChartLib::candleYPoint(price, min, max, height, num_axis_elements);
    expected = 636.21818181818185;
    EXPECT_DOUBLE_EQ(result, expected);

    price = 309.6;
    min = 245.51;
    max = 344.57;
    result = ChartLib::candleYPoint(price, min, max, height, num_axis_elements);
    expected = 558.98181818181797;
    EXPECT_DOUBLE_EQ(result, expected);
}


TEST (CandleYPointInvalidInp, ChartTests)
{
    // Price should be greater than zero.
    double price = 0;
    double min = 20.0;
    double max = 65.0;
    double height = 1080;
    int num_axis_elements = 10;
    double result = ChartLib::candleYPoint(price, min, max, height,
                                           num_axis_elements);
    double expected = -1;
    EXPECT_DOUBLE_EQ(result, expected);

    // Min should be greater than zero.
    price = 55;
    min = 0;
    max = 65.0;
    result = ChartLib::candleYPoint(price, min, max, height, num_axis_elements);
    expected = -1;
    EXPECT_DOUBLE_EQ(result, expected);

    // Max should be greater than zero.
    price = 55;
    min = 20.0;
    max = 0;
    result = ChartLib::candleYPoint(price, min, max, height, num_axis_elements);
    expected = -1;
    EXPECT_DOUBLE_EQ(result, expected);

    // Height should be greater than zero.
    price = 55;
    min = 20.0;
    max = 65.0;
    height = 0;
    result = ChartLib::candleYPoint(price, min, max, height, num_axis_elements);
    expected = -1;
    EXPECT_DOUBLE_EQ(result, expected);

    // Max should be greater than min.
    price = 55;
    min = 65.0;
    max = 20.0;
    height = 1080;
    result = ChartLib::candleYPoint(price, min, max, height, num_axis_elements);
    expected = -1;
    EXPECT_DOUBLE_EQ(result, expected);
}
