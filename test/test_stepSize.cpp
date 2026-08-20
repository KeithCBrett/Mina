// test_stepSize.cpp represents the valid and invalid input unit tests
// for function stepSize of module ChartLib

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


TEST (StepSizeValidInp, ChartTests)
{
    // - MINIMUM is the lowest price the stock we are charting dropped to.
    // - MAXIMUM is the highest price the stock we are charting reached, this along
    //   with MINIMUM are values we already have.
    // - BAN is equal to the bottom-most axis number for our Y axis (we have
    //   already computed such).
    // - STEP_SIZE is the value we are trying to compute. It should be a
    //   integer.
    // Now that we have that cleared up, we want to compute the lowest step size
    // with the following characteristics:
    //   STEP_SIZE % 5 == 0.
    //   MAXIMUM <= BAN + STEP_SIZE * 9
    // More simply we want a STEP_SIZE that gives us an axis that fits/contains
    // our data, whilst also being divisible by five.
    std::string result = ChartLib::stepSize(120, 121.99, 259.92).toStdString();
    // The STEP_SIZE that fits our criteria is 20
    // 20 % 5 == 0? TRUE
    // 259.92 <= 120 + 20 * 9 (300)
    std::string expected = "20";
    EXPECT_EQ(result, expected);

    result = ChartLib::stepSize(40, 40.63, 142.35).toStdString();
    expected = "15";
    EXPECT_EQ(result, expected);

    result = ChartLib::stepSize(245, 245.51, 344.57).toStdString();
    expected = "15";
    EXPECT_EQ(result, expected);

    result = ChartLib::stepSize(310, 311.49, 1255).toStdString();
    expected = "105";
    EXPECT_EQ(result, expected);
}


TEST (StepSizeInvalidInp, ChartTests)
{
    // Bottom-most number should be greater than zero or there is a problem.
    std::string result = ChartLib::stepSize(0, 40.63, 142.35).toStdString();
    std::string expected = "-1";
    EXPECT_EQ(result, expected);

    // Max should be greater than min. If not, there is a problem.
    result = ChartLib::stepSize(310, 1255, 311.49).toStdString();
    expected = "-1";
    EXPECT_EQ(result, expected);

    // Min should be greater than 0.
    result = ChartLib::stepSize(310, 0, 1255).toStdString();
    expected = "-1";
    EXPECT_EQ(result, expected);

    // Max should be greater than 0.
    result = ChartLib::stepSize(310, 1255, 0).toStdString();
    expected = "-1";
    EXPECT_EQ(result, expected);
}
