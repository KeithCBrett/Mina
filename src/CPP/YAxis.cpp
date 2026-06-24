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


void YAxis::paint(QPainter *painter)
{
  QPen pen(m_color, 2);

  painter->setPen(pen);
  painter->setRenderHints(QPainter::Antialiasing, true);

  for (int i = 1 ; i < NUM_ELEMENTS ; i++)
  {
    // Draw axis marking.
    painter->drawLine(0, ((height() / NUM_ELEMENTS) * i),
                      3, ((height() / NUM_ELEMENTS) * i));
    // Draw axis number.
    painter->drawText(6,
                      ((height() / NUM_ELEMENTS) * i) + 6, "100");
  }
}
