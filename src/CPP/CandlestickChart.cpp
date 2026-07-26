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


double CandlestickChart::min() const
{
  return m_min;
}


void CandlestickChart::setMin(const double &min)
{
  if (m_min != min)
  {
    m_min = min;
    update();
    emit minChanged();
  }
}


double CandlestickChart::max() const
{
  return m_max;
}


void CandlestickChart::setMax(const double &max)
{
  if (m_max != max)
  {
    m_max = max;
    update();
    emit maxChanged();
  }
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
    // Draw axis mark to screen.
    painter->drawLine(width() / NUM_X_AXIS_ELEMENTS * i, (height() - 7),
                      width() / NUM_X_AXIS_ELEMENTS * i, height());

    // Draw candle to screen.
    if (i <= (NUM_X_AXIS_ELEMENTS - 1))
    {
      if (i % 2 == 0)
      {
        drawCandle(220.83, 138.80, 140.0, 200.0, i, painter);
      }
      else
      {
        drawCandle(220.83, 138.80, 200.0, 140.0, i, painter);
      }
    }

    // Draw dates to screen.
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


// Function for computing the bottom most YAxis number.
QString CandlestickChart::firstYAxisNumber()
{
  double temp = m_min;
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
QString CandlestickChart::stepSize(double inp_first_axis_number)
{
  double step_size = m_max - m_min;
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
    while (m_max >= (step_size * (NUM_Y_AXIS_ELEMENTS - 1)
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

    while (m_max
           >= (round_step_size * (NUM_Y_AXIS_ELEMENTS - 1)
               + inp_first_axis_number))
    {
      round_step_size++;
    }
    return QString::number(round_step_size);
  }
}


double CandlestickChart::candleYPoint(double inp_num)
{
  double first_y_number = firstYAxisNumber().toDouble();
  double step = stepSize(first_y_number).toDouble();

  // double chart_min = m_min - step;
  double chart_min = first_y_number - step;

  // double chart_max = m_max + step;
  double chart_max = first_y_number + (NUM_Y_AXIS_ELEMENTS * step);

  double out_y = chart_max - chart_min;
  double index = inp_num - chart_min;
  out_y = index / out_y;
  out_y = 1.0 - out_y;

  return (out_y * height());
}


double CandlestickChart::candleLength(double open, double close)
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


void CandlestickChart::drawCandle(double high, double low, double open,
                                  double close, int index, QPainter *painter)
{
  // Calculate x position of candle to draw on our chart.
  double candle_x = width() / NUM_X_AXIS_ELEMENTS;
  candle_x = candle_x * index;

  double candle_width = width() / 110;

  // Save pen so we can restore it (we need to change it so we can draw a
  // different color).
  const QPen input_pen = painter->pen();

  // Green and red pen for upswing and downswing respectively.
  QPen up_pen;
  // QColor up_color(39, 77, 234, 92);
  QColor up_color(39, 77, 234);
  up_pen.setColor(up_color);

  QPen down_pen;
  // QColor down_color(186, 22, 80, 73);
  QColor down_color(186, 22, 80);
  down_pen.setColor(down_color);

  if (candleYPoint(open) > candleYPoint(close))
  {
    // We want to draw green candles so lets do that.
    painter->setPen(up_pen);

    // Draw top wick.
    painter->drawLine(candle_x, candleYPoint(high),
                      candle_x, candleYPoint(close));

    // Draw candle body.
    painter->drawRect(candle_x - candle_width / 2,
                      candleYPoint(close),
                      candle_width,
                      candleLength(candleYPoint(open),candleYPoint(close)));


    // Draw bottom wick.
    painter->drawLine(candle_x, candleYPoint(low),
                      candle_x, candleYPoint(open));

    // We are done drawing green candles. Lets restore the pen to how it was.
    painter->setPen(input_pen);
  }
  else
  {
    painter->setPen(down_pen);

    painter->drawLine(candle_x, candleYPoint(open),
                      candle_x, candleYPoint(low));

    painter->fillRect(candle_x - candle_width / 2,
                      candleYPoint(open),
                      candle_width,
                      candleLength(candleYPoint(open), candleYPoint(close)),
                      down_color);

    painter->drawLine(candle_x, candleYPoint(close),
                      candle_x, candleYPoint(high));

    painter->setPen(input_pen);
  }
}


void CandlestickChart::paint(QPainter *painter)
{

  QPen pen(m_borderColor, 2);

  painter->setPen(pen);
  painter->setRenderHints(QPainter::Antialiasing, false);

  // Draw bar chart border.
  QRectF rect(0, 0, width(), height());
  qreal offset = pen.widthF() / 2.0;
  rect.adjust(offset, offset, -offset, -offset);
  painter->drawRect(rect);

  // Paint the axises to the screen.
  drawYAxis(painter, 0.06, 0.20);
  drawXAxis(painter);
}
