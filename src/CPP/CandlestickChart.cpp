// CandlestickChart.cpp represents the class implementation for the bar chart seen on
// the 'Browse' page.

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


#include "../../include/CandlestickChart.hpp"
#include <QPainter>


#define NUM_Y_AXIS_ELEMENTS 10
#define NUM_X_AXIS_ELEMENTS 101


CandlestickChart::CandlestickChart(QQuickItem *parent)
  : QQuickPaintedItem(parent)
{
}


QColor CandlestickChart::borderColor() const
{
  return m_borderColor;
}


void CandlestickChart::setBorderColor(const QColor &borderColor)
{
  m_borderColor = borderColor;
}


// Draws the lines small lines and dollar amounts associated with the y-axis.
void CandlestickChart::drawYAxis(QPainter *painter, float min, float max)
{
  for (int i = 1 ; i <= NUM_Y_AXIS_ELEMENTS ; i++)
  {
    // Draw axis marking.
    painter->drawLine(width() - 5, (height() / (NUM_Y_AXIS_ELEMENTS + 1) * i),
                      width(), (height() / (NUM_Y_AXIS_ELEMENTS + 1) * i));
  }
}


void CandlestickChart::drawXAxis(QPainter *painter)
{
  QDate date = QDate::currentDate();
  
  for (int i = 1 ; i <= NUM_X_AXIS_ELEMENTS ; i++)
  {
    painter->drawLine(width() / NUM_X_AXIS_ELEMENTS * i, (height() - 7),
                      width() / NUM_X_AXIS_ELEMENTS * i, height());

    if ((i % 10 == 0) && (i <= NUM_X_AXIS_ELEMENTS - 10))
    {
      painter->drawText((width() / NUM_X_AXIS_ELEMENTS * i) - width() * 0.0185,
                        height() * 0.99,
                        date.addDays(-(NUM_X_AXIS_ELEMENTS - i - 1
                                       + m_dateOffset)).toString("MM/dd"));
    }
  }
}


qint64 CandlestickChart::dateOffset() const
{
  return m_dateOffset;
}


void CandlestickChart::setDateOffset(const qint64 &dateOffset)
{
  if (dateOffset != m_dateOffset)
  {
    m_dateOffset = dateOffset;
    update();
    emit dateOffsetChanged();
  }
}


void CandlestickChart::paint(QPainter *painter)
{

  QPen pen(m_borderColor, 2);

  painter->setPen(pen);
  painter->setRenderHints(QPainter::Antialiasing, true);

  // Draw bar chart border.
  QRectF rect(0, 0, width(), height());
  qreal offset = pen.widthF() / 2.0;
  rect.adjust(offset, offset, -offset, -offset);
  painter->drawRect(rect);

  // Paint the axises to the screen.
  drawYAxis(painter, 0.06, 0.20);
  drawXAxis(painter);
}
