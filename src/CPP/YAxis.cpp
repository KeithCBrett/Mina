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


#include "../../include/ChartLib.hpp"


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
  if (m_min != min)
  {
    m_min = min;
    update();
    emit minChanged();
  }
}


double YAxis::max() const
{
  return m_max;
}


void YAxis::setMax(const double &max)
{
  if (m_max != max)
  {
    m_max = max;
    update();
    emit maxChanged();
  }
}


// Helper function that draws a number to the axis. inp_location decides where
// on the axis the number will be drawn. inp_location of 0 would be the
// bottom-most position of the axis.
void YAxis::drawYAxisNumber
  (QPainter *inp_painter, int inp_location, QString inp_number)
{
  inp_painter->drawText
    (7, (height() - (height() / (NUM_ELEMENTS + 1)) * inp_location) + 5,
     inp_number);
}


void YAxis::paint(QPainter *painter)
{
  QPen pen(m_color, 2);

  // We compute the first number, then subsequently use that number to compute
  // all the other axis numbers.
  QString first_num = ChartLib::firstYAxisNumber(min());
  QString other_num;

  painter->setPen(pen);
  painter->setRenderHints(QPainter::Antialiasing, true);

  for (auto i = 1 ; i <= NUM_ELEMENTS ; i++)
  {
    // Draw axis marking.
    painter->drawLine(0, ((height() / (NUM_ELEMENTS + 1)) * i),
                      3, ((height() / (NUM_ELEMENTS + 1)) * i));

    // Draw axis number.
    other_num = ChartLib::otherYAxisNumber(m_min, m_max, first_num, i);
    drawYAxisNumber(painter, i, other_num);
  }
}
