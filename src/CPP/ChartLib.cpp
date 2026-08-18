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
    QString firstYAxisNumber (double min)
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
}
