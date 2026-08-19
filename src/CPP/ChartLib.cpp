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


namespace ChartLib {
    // Function for computing the bottom most YAxis number.
    QString firstYAxisNumber(double min)
    {
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
            return QString::number(step_size);
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
            return QString::number(round_step_size);
        }
    }

    // Converts a dollar amount into a Y-point on our candlestick chart according
    // to our axis.
    double candleYPoint(double inp_num, double min, double max, double height, size_t num_axis_elements)
    {
        double first_y_number = firstYAxisNumber(min).toDouble();
        double step = stepSize(first_y_number, min, max).toDouble();

        // double chart_min = m_min - step;
        double chart_min = first_y_number - step;

        // double chart_max = m_max + step;
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
}
