// test_offsetStep.cpp represents the valid and invalid input unit tests
// for function offsetStep of module ChartLib

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


// This function is resposible for excluding dates from our axis. Essentially,
// to get any particular date for our X-axis, we count backwards from today. So
// if we wanted a date 100 days in the past, we start from today, and count 100
// days backwards, excluding weekends. The function will return 100 plus the
// number of weekends encountered in the range.


TEST (OffsetStepValidInp, ChartTests)
{
    // This function can be difficult to test, due to it relying on the current
    // calendar position. We will have to use some control flow.
    qint64 date_offset = 0;
    QDate curr_day = QDate::currentDate();

    size_t step;
    size_t result;
    size_t expected;

    // If its currently Sunday, offsetStep(0, 0) should return two days prior (2)
    // on account of Sunday and Saturday being skipped. If its a weekday,
    // offsetStep(0, 0) = 0.
    if (curr_day.dayOfWeek() == 7)
    {
        step = 0;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 2;
        EXPECT_EQ(result, expected);
    }
    else if (curr_day.dayOfWeek() == 6)
    {
        step = 0;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 1;
        EXPECT_EQ(result, expected);
    }
    else
    {
        step = 0;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 0;
        EXPECT_EQ(result, expected);
    }

    // Now we check if we can go back a week, which should skip a weekend.
    if (curr_day.dayOfWeek() == 7)
    {
        // We skip two days because it's currently Sunday, and two more for the
        // weekend encountered.
        step = 7;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 11; // step + 2 (for Sunday) + 2 (1 weekend encountered)
        EXPECT_EQ(result, expected);
    }
    else if (curr_day.dayOfWeek() == 6)
    {
        // We skip one day because it's currently Saturday, and two more for the
        // weekend encountered.
        step = 7;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 10; // step + 1 (for Saturday) + 2 (1 weekend encountered)
        EXPECT_EQ(result, expected);
    }
    else
    {
        // Here we only skip days for weekends encountered.
        step = 7;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 9; // step + 2 (1 weekend encountered)
        EXPECT_EQ(result, expected);
    }

    // If we go back 100 days, we should skip 40 days on weekdays, 41 on
    // Saturdays, and 42 on Sundays.
    // Sunday
    if (curr_day.dayOfWeek() == 7)
    {
        step = 100;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 142;
        EXPECT_EQ(result, expected);
    }
    // Saturday
    else if (curr_day.dayOfWeek() == 6)
    {
        step = 100;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 141;
        EXPECT_EQ(result, expected);
    }
    // Weekday
    else
    {
        step = 100;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 140;
        EXPECT_EQ(result, expected);
    }
}


TEST (OffsetStepInvalidInp, ChartTests)
{
    // Our step will be a number between zero and 100 (correlating to the 100 X
    // axis elements on our chart). Any thing more doesn't make sense for our use
    // case. This algorithm also scales O(n) for n step, so if someone wants to
    // use this for step greater than 100, they should just rewrite offsetStep
    // to be more performant.
    size_t step = 999;
    qint64 date_offset = 0;
    size_t result = ChartLib::offsetStep(step, date_offset);
    size_t expected = -1;
    EXPECT_EQ(result, expected);
}
