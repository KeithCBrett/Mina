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


//#include "QtCore"
#include "unit_tests.hpp"


#include "ChartLib.hpp"


QDate t_new_years(2026, 1, 1);
QDate t_mlk_day(2026, 1, 19);
QDate t_washingtons_bday(2026, 2, 16);
QDate t_good_friday(2026, 4, 3);
QDate t_memorial_day(2026, 5, 25);
QDate t_juneteenth(2026, 6, 19);
QDate t_independance_day(2026, 7, 3);
QDate t_labor_day(2026, 9, 7);
QDate t_thanksgiving(2026, 11, 26);
QDate t_christmas(2026, 12, 25);


// This function is resposible for excluding dates from our axis. Essentially,
// to get any particular date for our X-axis, we count backwards from today. So
// if we wanted a date 100 days in the past, we start from today, and count 100
// days backwards, excluding weekends. The function will return 100 plus the
// number of weekends encountered in the range.

// Helper boolean that shows whether input date is a weekend.
bool weekend(QDate inp_date) {
    if ((inp_date.dayOfWeek() == 6) || (inp_date.dayOfWeek() == 7)) {
        return true;
    }
    else {
        return false;
    }
}


bool marketOpen(QDate inp_date) {
    // If it's a weekend, the market is closed.
    if (weekend(inp_date)) {
        return false;
    }

    // We have to skip holidays too.
    // New Years Day.
    if (inp_date == t_new_years) {
        return false;
    }
    else if (inp_date == t_mlk_day) {
        return false;
    }
    else if (inp_date == t_washingtons_bday) {
        return false;
    }
    else if (inp_date == t_good_friday) {
        return false;
    }
    else if (inp_date == t_memorial_day) {
        return false;
    }
    else if (inp_date == t_juneteenth) {
        return false;
    }
    else if (inp_date == t_independance_day) {
        return false;
    }
    else if (inp_date == t_labor_day) {
        return false;
    }
    else if (inp_date == t_thanksgiving) {
        return false;
    }
    else if (inp_date == t_christmas) {
        return false;
    }
    else {
        return true;
    }
}


bool holiday(QDate inp_date) {
    if (inp_date == t_new_years) {
        return true;
    }
    else if (inp_date == t_mlk_day) {
        return true;
    }
    else if (inp_date == t_washingtons_bday) {
        return true;
    }
    else if (inp_date == t_good_friday) {
        return true;
    }
    else if (inp_date == t_memorial_day) {
        return true;
    }
    else if (inp_date == t_juneteenth) {
        return true;
    }
    else if (inp_date == t_independance_day) {
        return true;
    }
    else if (inp_date == t_labor_day) {
        return true;
    }
    else if (inp_date == t_thanksgiving) {
        return true;
    }
    else if (inp_date == t_christmas) {
        return true;
    }
    else {
        return false;
    }
}


// Helper function that is like offsetStep, but returns the number of holidays
// encountered.
int holidays(int inp_step) {
    // Error handling.
    // We don't allow inp_step greater than 100, this algorithm won't scale
    // well for that (or for big inp_step in general). We loop for each
    // inp_step.
    if (inp_step > 100) {
        return -1;
    }

    int holiday_count = 0;

    size_t out_step = 0;

    // original_input + days skipped = output.
    size_t original_input = inp_step;

    // So that we can check if we are on a weekend (to exlude it).
    QDate curr_day = QDate::currentDate();

    if (holiday(curr_day)) {
        holiday_count++;
    }

    // Check if current day is a weekend.
    // Sunday.
    if (curr_day.dayOfWeek() == 7) {
        out_step += 2;
        curr_day = curr_day.addDays(-2);
    }
    // Saturday.
    if (curr_day.dayOfWeek() == 6) {
        out_step += 1;
        curr_day = curr_day.addDays(-1);
    }

    // We use inp_step to track our progress.
    while (inp_step > 0) {
        // In theory, if we count the days we skip, and add it to our orginal
        // input, this will give us the total distance traveled (which is
        // what we want as output). Since we skip days in which the market is
        // closed, that is what we will count.
        if (!marketOpen(curr_day)) {
            out_step++;
        }

        if (holiday(curr_day)) {
            holiday_count++;
        }

        // If market wasn't open on the day we are checking, we have to
        // ignore it and move on.
        if (marketOpen(curr_day)) {
            inp_step--;
        }

        // Get previous day to progress loop.
        curr_day = curr_day.addDays(-1);
    }

    // Sometimes when we break our loop, we end on a closed market day. We
    // count this in our output.
    while (!marketOpen(curr_day)) {
        out_step++;
        if (holiday(curr_day)) {
            holiday_count++;
        }
        curr_day = curr_day.addDays(-1);
    }

    return holiday_count;

}

TEST (OffsetStepValidInp, ChartTests) {
    // This function can be difficult to test, due to it relying on the current
    // calendar position. We will have to use some control flow.
    qint64 date_offset = 0;
    QDate curr_day = QDate::currentDate();

    int step;
    int result;
    int expected;

    // If its currently Sunday, offsetStep(0, 0) should return two days prior (2)
    // on account of Sunday and Saturday being skipped. If its a weekday,
    // offsetStep(0, 0) = 0.
    if (curr_day.dayOfWeek() == 7) {
        step = 0;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 2;
        EXPECT_EQ(result, expected);
    }
    else if (curr_day.dayOfWeek() == 6) {
        step = 0;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 1;
        EXPECT_EQ(result, expected);
    }
    else {
        step = 0;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 0;
        EXPECT_EQ(result, expected);
    }

    // Now we check if we can go back a week, which should skip a weekend (we
    // have to go back two weekend if its Monday or Tuesday).
    if (curr_day.dayOfWeek() == 7) {
        // We skip two days because it's currently Sunday, and two more for the
        // weekend encountered.
        step = 7;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 11; // step + 2 (for Sunday) + 2 (1 weekend encountered)
        EXPECT_EQ(result, expected);
    }
    else if (curr_day.dayOfWeek() == 6) {
        // We skip one day because it's currently Saturday, and two more for the
        // weekend encountered.
        step = 7;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 10; // step + 1 (for Saturday) + 2 (1 weekend encountered)
        EXPECT_EQ(result, expected);
    }
    // Monday and Tuesday we have to skip two weekends.
    else if ((curr_day.dayOfWeek() == 1) || (curr_day.dayOfWeek() == 2)) {
        step = 7;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 11 + holidays(step); // 7 + 4 for the two weekends encountered.
    }
    else {
        // Here we only skip days for weekends encountered.
        step = 7;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 9 + holidays(step); // step + 2 (1 weekend encountered)
        EXPECT_EQ(result, expected);
    }

    // If we go back 100 days, we should skip 40 days on weekdays, 41 on
    // Saturdays, and 42 on Sundays (plus holidays).
    // Sunday
    if (curr_day.dayOfWeek() == 7) {
        step = 100;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 142;
        EXPECT_EQ(result, expected);
    }
    // Saturday
    else if (curr_day.dayOfWeek() == 6) {
        step = 100;
        result = ChartLib::offsetStep(step, date_offset);
        expected = 141;
        EXPECT_EQ(result, expected);
    }
    // Weekday
    else {
        step = 100;
        result = ChartLib::offsetStep(step, date_offset);
        // 42 for weekends, plus however many holidays.
        expected = 142 + holidays(100);
        EXPECT_EQ(result, expected);
    }
}


TEST (OffsetStepInvalidInp, ChartTests) {
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
