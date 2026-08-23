// test_candleLength.cpp represents the valid and invalid input unit tests
// for function candleLength of module ChartLib

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


// This function just gets the difference between two doubles as a positive
// number. For instance:
// candleLength(300, 100) = 200
// candleLength(100, 300) = 200
// candleLength(500, 400) = 100


TEST (CandleLengthValidInp, ChartTests)
{
    double open = 200;
    double close = 400;
    double result = ChartLib::candleLength(open, close);
    double expected = 200;
    EXPECT_DOUBLE_EQ(result, expected);

    open = 956.58;
    close = 624.71;
    result = ChartLib::candleLength(open, close);
    expected = 331.87;
    EXPECT_DOUBLE_EQ(result, expected);

    open = 777.77;
    close = 666.66;
    result = ChartLib::candleLength(open, close);
    expected = 111.11;
    EXPECT_DOUBLE_EQ(result, expected);
}


TEST (CandleLengthInvalidInp, ChartTests)
{
    // Open should be greater than zero.
    double open = 0;
    double close = 399.50;
    double result = ChartLib::candleLength(open, close);
    double expected = -1;
    EXPECT_DOUBLE_EQ(result, expected);

    // Close should be greater than zero.
    open = 399.50;
    close = 0;
    result = ChartLib::candleLength(open, close);
    expected = -1;
    EXPECT_DOUBLE_EQ(result, expected);
}
