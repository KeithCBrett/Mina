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
    QString stepSize(double inp_first_axis_number);
}


#endif // CHARTLIB_H
