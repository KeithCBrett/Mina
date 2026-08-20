// test_firstYAxisNumber.cpp represents the valid and invalid input unit tests
// for function firstYAxisNumber of module ChartLib

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


#include <QtCore>
#include "unit_tests.hpp"


#include "ChartLib.hpp"
#include "../src/CPP/ChartLib.cpp"


TEST (FirstYAxisNumberValidInp, ChartTests)
{
    // We will use std::string instead of QString for better unit test output.
    std::string result = ChartLib::firstYAxisNumber(121.99).toStdString();
    std::string expected = "120"; // Truncate 121.99 to 121, decrement until
    EXPECT_EQ(result, expected);  // divisible by either 5 or 10 (120).

    result = ChartLib::firstYAxisNumber(126.85).toStdString();
    expected = "125";
    EXPECT_EQ(result, expected);

    result = ChartLib::firstYAxisNumber(40.63).toStdString();
    expected = "40";
    EXPECT_EQ(result, expected);

    result = ChartLib::firstYAxisNumber(245.51).toStdString();
    expected = "245";
    EXPECT_EQ(result, expected);
}


TEST (FirstYAxisNumberInvalidInp, ChartTests)
{
    // A negative stock price doesn't exist, handle that.
    std::string result = ChartLib::firstYAxisNumber(-6.88).toStdString();
    std::string expected = "-1";
    EXPECT_EQ(result, expected);

    // You also cant by a share for no price at all.
    result = ChartLib::firstYAxisNumber(0).toStdString();
    expected = "-1";
    EXPECT_EQ(result, expected);
}
