// YAxis.cpp represents the class implementation for the Y-axis associated with
// the candlestick chart that can be found on the 'Browse' page.

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


#include "../../include/YAxis.hpp"
#include <QPainter>
#include <cmath>


#define NUM_ELEMENTS 10


YAxis::YAxis(QQuickItem *parent) : QQuickPaintedItem(parent)
{
}


QColor YAxis::color() const
{
  return m_color;
}


void YAxis::setColor(const QColor &color)
{
  m_color = color;
}


double YAxis::min() const
{
  return m_min;
}


void YAxis::setMin(const double &min)
{
  m_min = min;
}


double YAxis::max() const
{
  return m_max;
}


void YAxis::setMax(const double &max)
{
  m_max = max;
}


// Helper function that draws a number to the axis. inp_location decides where
// on the axis the number will be drawn. inp_location of 0 would be the
// bottom-most position of the axis.
void YAxis::drawYAxisNumber
  (QPainter *inp_painter, int inp_location, QString inp_number)
{
  inp_painter->drawText
    (7, (height() - (height() / (NUM_ELEMENTS + 1)) * inp_location) + 5, inp_number);
}


// Function for computing the bottom most YAxis number.
QString YAxis::firstYAxisNumber(double inp_min)
{
  double temp = inp_min;
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


// Function for computing all the YAxis numbers (except the one computed
// by firstYAxisNumber()).
QString YAxis::otherYAxisNumber(double inp_min, double inp_max,
                                QString inp_first_axis_number, int inp_position)
{
  double step_size = inp_max - inp_min;
  step_size = step_size / NUM_ELEMENTS;

  int trunc_step_size = 0;

  double first_axis_number = inp_first_axis_number.toDouble();

  QString out_string;

  std::string temp_string;
  
  if (step_size < 0.1)
  {
    temp_string = std::to_string(step_size).substr(0, 4);
    step_size = std::stod(temp_string);

    // Check if axis fits data.
    while (inp_max >= (step_size * (NUM_ELEMENTS - 1) + first_axis_number))
    {
      // If not, generate axis of wider range.
      step_size = step_size + 0.01;
    }

    out_string = QString::number(step_size * (inp_position - 1)
                                + first_axis_number);
    return out_string;
  }
  else
  {
    trunc_step_size = std::round(step_size);

    while (inp_max
           >= (trunc_step_size * (NUM_ELEMENTS - 1) + first_axis_number))
    {
      trunc_step_size++;
    }

    out_string = QString::number(trunc_step_size * (inp_position - 1)
                                + first_axis_number);
    return out_string;
  }
}


void YAxis::paint(QPainter *painter)
{
  QPen pen(m_color, 2);

  // We compute the first number, then subsequently use that number to compute
  // all the other axis numbers.
  QString first_num = firstYAxisNumber(m_min);
  QString other_num;

  painter->setPen(pen);
  painter->setRenderHints(QPainter::Antialiasing, true);

  for (auto i = 1 ; i <= NUM_ELEMENTS ; i++)
  {
    // Draw axis marking.
    painter->drawLine(0, ((height() / (NUM_ELEMENTS + 1)) * i),
                      3, ((height() / (NUM_ELEMENTS + 1)) * i));

    // Draw axis number.
    other_num = otherYAxisNumber(m_min, m_max, first_num, i);
    drawYAxisNumber(painter, i, other_num);
  }
}
