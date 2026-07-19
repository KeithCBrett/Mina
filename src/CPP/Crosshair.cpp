// Crosshair.cpp represents the class implementation for the crosshair that
// appears whenever the user mouses over the candlestick chart found on the
// 'Browse' page.

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


#include "../../include/Crosshair.hpp"
#include "../../include/YAxis.hpp"
#include <QPainter>


// Useful constants for drawing lines of known length.
#define SMALL_LINE (width() / 100)
#define MEDIUM_LINE (width() / 50)
#define BIG_LINE (width() / 10)

#define NUM_Y_ELEMENTS 10


Crosshair::Crosshair(QQuickItem *parent) : QQuickPaintedItem(parent)
{
}


QColor Crosshair::color() const
{
  return m_color;
}


void Crosshair::setColor(const QColor &color)
{
  m_color = color;
}


double Crosshair::posX() const
{
  return m_posX;
}


void Crosshair::setPosX(const double &posX)
{
  if (posX != m_posX)
  {
    m_posX = posX;
    update();
    emit posXChanged();
  }
}


double Crosshair::posY() const
{
  return m_posY;
}


void Crosshair::setPosY(const double &posY)
{
  if (posY != m_posY)
  {
    m_posY = posY;
    update();
    emit posYChanged();
  }
}


double Crosshair::min() const
{
  return m_min;
}


void Crosshair::setMin(const double &min)
{
  if (min != m_min)
  {
    m_min = min;
    update();
    emit minChanged();
  }
}


double Crosshair::max() const
{
  return m_max;
}


void Crosshair::setMax(const double &max)
{
  if (max != m_max)
  {
    m_max = max;
    update();
    emit maxChanged();
  }
}


QString Crosshair::price() const
{
  return m_price;
}


void Crosshair::setPrice(const QString &price)
{
  if (price != m_price)
  {
    m_price = price;
    update();
    emit priceChanged();
  }
}


bool Crosshair::rightSwapped() const
{
  return m_rightSwapped;
}


void Crosshair::setRightSwapped(const bool &rightSwapped)
{
  if (rightSwapped != m_rightSwapped)
  {
    m_rightSwapped = rightSwapped;
    update();
    emit rightSwappedChanged();
  }
}


bool Crosshair::leftSwapped() const
{
  return m_leftSwapped;
}


void Crosshair::setLeftSwapped(const bool &leftSwapped)
{
  if (leftSwapped != m_leftSwapped)
  {
    m_leftSwapped = leftSwapped;
    update();
    emit leftSwappedChanged();
  }
}


bool Crosshair::topSwapped() const
{
  return m_topSwapped;
}


void Crosshair::setTopSwapped(const bool &topSwapped)
{
  if (topSwapped != m_topSwapped)
  {
    m_topSwapped = topSwapped;
    update();
    emit topSwappedChanged();
  }
}


// Draw price box for when cursor is too far to the right of the chart.
// Misnomer because we actually draw this box to the left of the axis.
void Crosshair::drawRightPriceBox(QPainter *painter)
{
  QPen pen(m_color, 2);
  pen.setCapStyle(Qt::RoundCap);
  painter->setPen(pen);

  QFont font = painter->font();
  font.setPointSize(std::trunc(width() / 100));
  painter->setFont(font);
  
  QPointF p1(m_posX - SMALL_LINE, m_posY - SMALL_LINE);
  QPointF p2;

  p2 += QPointF(p1.x() - BIG_LINE, p1.y());
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, -MEDIUM_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(BIG_LINE - SMALL_LINE, 0.0);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(SMALL_LINE, SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, SMALL_LINE);
  painter->drawLine(p1, p2);

  painter->drawText(m_posX - BIG_LINE, m_posY - (SMALL_LINE + SMALL_LINE / 2), m_price);
}


// Draw date box for when cursor is too far to the right of the chart.
// Misnomer because we actually draw this box to the left of the axis.
void Crosshair::drawRightDateBox(QPainter *painter)
{
  QPen pen(m_color, 2);
  pen.setCapStyle(Qt::RoundCap);
  painter->setPen(pen);

  QFont font = painter->font();
  font.setPointSize(std::trunc(width() / 100));
  painter->setFont(font);
  
  QPointF p1(m_posX - (SMALL_LINE * 2 + BIG_LINE), m_posY - SMALL_LINE);
  QPointF p2;

  p2 += QPointF(p1.x() - BIG_LINE, p1.y());
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, -SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(SMALL_LINE, -SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(BIG_LINE - SMALL_LINE, 0.0);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, MEDIUM_LINE);
  painter->drawLine(p1, p2);

  painter->drawText(m_posX - BIG_LINE * 2 + SMALL_LINE * 0.1,
                    m_posY - (SMALL_LINE + SMALL_LINE / 2), "99/99/99");
}


// Draw price box for when cursor is too far to the left of the chart.
// Misnomer because we actually draw this box to the right of the axis.
void Crosshair::drawLeftPriceBox(QPainter *painter)
{
  QPen pen(m_color, 2);
  pen.setCapStyle(Qt::RoundCap);
  painter->setPen(pen);

  QFont font = painter->font();
  font.setPointSize(std::trunc(width() / 100));
  painter->setFont(font);

  QPointF p1(m_posX + BIG_LINE + MEDIUM_LINE, m_posY - SMALL_LINE);
  QPointF p2;

  p2 += QPointF(p1.x() + BIG_LINE, p1.y());
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, -SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(-SMALL_LINE, -SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(-(BIG_LINE - SMALL_LINE), 0.0);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, MEDIUM_LINE);
  painter->drawLine(p1, p2);

  painter->drawText(m_posX + BIG_LINE + MEDIUM_LINE + SMALL_LINE,
                    m_posY - (SMALL_LINE + SMALL_LINE / 2), m_price);
}


// Draw date box for when cursor is too far to the left of the chart.
// Misnomer because we actually draw this box to the right of the axis.
void Crosshair::drawLeftDateBox(QPainter *painter)
{
  QPen pen(m_color, 2);
  pen.setCapStyle(Qt::RoundCap);
  painter->setPen(pen);

  QFont font = painter->font();
  font.setPointSize(std::trunc(width() / 100));
  painter->setFont(font);

  QPointF p1(m_posX + SMALL_LINE, m_posY - SMALL_LINE);
  QPointF p2;

  p2 += QPointF(p1.x() + BIG_LINE, p1.y());
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, -MEDIUM_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(-BIG_LINE + SMALL_LINE, 0.0);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(-SMALL_LINE, SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, SMALL_LINE);
  painter->drawLine(p1, p2);

  painter->drawText(m_posX + MEDIUM_LINE + SMALL_LINE * 1.1,
                    m_posY - (SMALL_LINE + SMALL_LINE / 2), "99/99/99");
}


// Draw price box for when cursor is too far to the top of the chart.
// Misnomer because we actually draw this box to the bottom of the axis.
void Crosshair::drawTopPriceBox(QPainter *painter)
{
  QPen pen(m_color, 2);
  pen.setCapStyle(Qt::RoundCap);
  painter->setPen(pen);

  QFont font = painter->font();
  font.setPointSize(std::trunc(width() / 100));
  painter->setFont(font);

  QPointF p1(m_posX + SMALL_LINE, m_posY + SMALL_LINE);
  QPointF p2;

  p2 += QPointF(p1.x() + BIG_LINE, p1.y());
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(-SMALL_LINE, SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(-(BIG_LINE - SMALL_LINE), 0.0);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, -MEDIUM_LINE);
  painter->drawLine(p1, p2);

  painter->drawText(m_posX + MEDIUM_LINE,
                    m_posY + MEDIUM_LINE + SMALL_LINE / 2, m_price);
}


// Draw date box for when cursor is too far to the top of the chart.
// Misnomer because we actually draw this box to the bottom of the axis.
void Crosshair::drawTopDateBox(QPainter *painter)
{
  QPen pen(m_color, 2);
  pen.setCapStyle(Qt::RoundCap);
  painter->setPen(pen);

  QFont font = painter->font();
  font.setPointSize(std::trunc(width() / 100));
  painter->setFont(font);

  QPointF p1(m_posX - SMALL_LINE, m_posY + SMALL_LINE);
  QPointF p2;

  p2 += QPointF(p1.x() - BIG_LINE, p1.y());
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(SMALL_LINE, SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(BIG_LINE - SMALL_LINE, 0.0);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, -MEDIUM_LINE);
  painter->drawLine(p1, p2);

  painter->drawText(m_posX - BIG_LINE + SMALL_LINE * 1.1,
                    m_posY + MEDIUM_LINE + SMALL_LINE / 2, "99/99/99");
}


// Draw price box for when cursor is too far to the top right of the chart.
// Misnomer because we actually draw this box to the bottom left of the axis.
void Crosshair::drawTopRightPriceBox(QPainter *painter)
{
  QPen pen(m_color, 2);
  pen.setCapStyle(Qt::RoundCap);
  painter->setPen(pen);

  QFont font = painter->font();
  font.setPointSize(std::trunc(width() / 100));
  painter->setFont(font);

  QPointF p1(m_posX - SMALL_LINE, m_posY + SMALL_LINE);
  QPointF p2;

  p2 += QPointF(p1.x() -BIG_LINE, p1.y());
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, MEDIUM_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(BIG_LINE - SMALL_LINE, 0.0);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(SMALL_LINE, -SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, -SMALL_LINE);
  painter->drawLine(p1, p2);

  painter->drawText(m_posX - BIG_LINE,
                    m_posY + MEDIUM_LINE + SMALL_LINE / 2, m_price);
}


// Draw date box for when cursor is too far to the top right of the chart.
// Misnomer because we actually draw this box to the bottom left of the axis.
void Crosshair::drawTopRightDateBox(QPainter *painter)
{
  QPen pen(m_color, 2);
  pen.setCapStyle(Qt::RoundCap);
  painter->setPen(pen);

  QFont font = painter->font();
  font.setPointSize(std::trunc(width() / 100));
  painter->setFont(font);

  QPointF p1(m_posX + -(SMALL_LINE * 2 + BIG_LINE), m_posY + SMALL_LINE);
  QPointF p2;

  p2 += QPointF(p1.x() - BIG_LINE, p1.y());
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(SMALL_LINE, SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(BIG_LINE - SMALL_LINE, 0.0);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, -MEDIUM_LINE);
  painter->drawLine(p1, p2);

  painter->drawText(m_posX - BIG_LINE * 2,
                    m_posY + MEDIUM_LINE + SMALL_LINE / 2, "99/99/99");
}


// Draw price box for when cursor is too far to the top left of the chart.
// Misnomer because we actually draw this box to the bottom right of the axis.
void Crosshair::drawTopLeftPriceBox(QPainter *painter)
{
  QPen pen(m_color, 2);
  pen.setCapStyle(Qt::RoundCap);
  painter->setPen(pen);

  QFont font = painter->font();
  font.setPointSize(std::trunc(width() / 100));
  painter->setFont(font);

  QPointF p1(m_posX + MEDIUM_LINE + BIG_LINE, m_posY + SMALL_LINE);
  QPointF p2;

  p2 += QPointF(p1.x() + BIG_LINE, p1.y());
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(-SMALL_LINE, SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(-(BIG_LINE - SMALL_LINE), 0.0);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, -MEDIUM_LINE);
  painter->drawLine(p1, p2);

  painter->drawText(m_posX + BIG_LINE + MEDIUM_LINE + SMALL_LINE,
                    m_posY + MEDIUM_LINE + SMALL_LINE / 2, m_price);
}


// Draw date box for when cursor is too far to the top left of the chart.
// Misnomer because we actually draw this box to the bottom right of the axis.
void Crosshair::drawTopLeftDateBox(QPainter *painter)
{
  QPen pen(m_color, 2);
  pen.setCapStyle(Qt::RoundCap);
  painter->setPen(pen);

  QFont font = painter->font();
  font.setPointSize(std::trunc(width() / 100));
  painter->setFont(font);

  QPointF p1(m_posX + SMALL_LINE, m_posY + SMALL_LINE);
  QPointF p2;

  p2 += QPointF(p1.x() + BIG_LINE, p1.y());
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, MEDIUM_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(-(BIG_LINE - SMALL_LINE), 0.0);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(-SMALL_LINE, -SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, -SMALL_LINE);
  painter->drawLine(p1, p2);

  painter->drawText(m_posX + MEDIUM_LINE + SMALL_LINE * 1.1,
                    m_posY + MEDIUM_LINE + SMALL_LINE / 2, "99/99/99");
}


void Crosshair::drawDefaultPriceBox(QPainter *painter)
{
  QPen pen(m_color, 2);
  pen.setCapStyle(Qt::RoundCap);
  painter->setPen(pen);

  QFont font = painter->font();
  font.setPointSize(std::trunc(width() / 100));
  painter->setFont(font);

  QPointF p1(m_posX + SMALL_LINE, m_posY - SMALL_LINE);
  QPointF p2;

  p2 += QPointF(p1.x() + BIG_LINE, p1.y());
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 -= QPointF(0.0, SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(-SMALL_LINE, -SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(-(BIG_LINE - SMALL_LINE), 0.0);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, MEDIUM_LINE);
  painter->drawLine(p1, p2);

  // Above code drew the box, below code draws the text.
  painter->drawText(m_posX + MEDIUM_LINE, m_posY - (SMALL_LINE + SMALL_LINE / 2), m_price);
}


void Crosshair::drawDefaultDateBox(QPainter *painter)
{
  QPen pen(m_color, 2);
  pen.setCapStyle(Qt::RoundCap);
  painter->setPen(pen);

  QFont font = painter->font();
  font.setPointSize(std::trunc(width() / 100));
  painter->setFont(font);
  
  QPointF p1(m_posX - SMALL_LINE, m_posY - SMALL_LINE);
  QPointF p2;

  p2 += QPointF(p1.x() - BIG_LINE, p1.y());
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, -SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(SMALL_LINE, -SMALL_LINE);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(BIG_LINE - SMALL_LINE, 0.0);
  painter->drawLine(p1, p2);

  p1 = p2;
  p2 += QPointF(0.0, MEDIUM_LINE);
  painter->drawLine(p1, p2);

  // Above code drew the box, below code draws the text.
  painter->drawText(m_posX - BIG_LINE + SMALL_LINE * 1.1,
                    m_posY - (SMALL_LINE + SMALL_LINE / 2), "99/99/99");
}


QString Crosshair::stepSize(double inp_first_axis_number)
{
  double step_size = m_max - m_min;
  step_size = step_size / NUM_Y_ELEMENTS;

  // We try to round to a whole number whenever we can.
  int round_step_size = 0;

  std::string temp_string;

  if (step_size < 0.1)
  {
    // In case of irrational numbers. Truncates 0.0XXXX... to 0.0X.
    temp_string = std::to_string(step_size).substr(0, 4);
    step_size = std::stod(temp_string);

    // Check if axis fits data.
    while (m_max >= (step_size * (NUM_Y_ELEMENTS - 1) + inp_first_axis_number))
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
           >= (round_step_size * (NUM_Y_ELEMENTS - 1) + inp_first_axis_number))
    {
      round_step_size++;
    }
    return QString::number(round_step_size);
  }
}


QString Crosshair::firstYAxisNumber(double inp_min)
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


// price() computes the number to display for the price window to the top right
// of the cursor. This is done via the mouse cursor's Y position.
QString Crosshair::getPrice()
{
  double first_axis_number = firstYAxisNumber(m_min).toDouble();
  double step_count = stepSize(first_axis_number).toDouble();

  double bottom_chart_num = first_axis_number - step_count;
  double top_chart_num = first_axis_number + step_count * 10;

  double offset = top_chart_num - bottom_chart_num;
  double y_position = 1.0 - m_posY / height();

  return QString::number(std::round(bottom_chart_num + offset * y_position));
}


void Crosshair::paint(QPainter *painter)
{
  QPen pen(m_color, 2);
  pen.setStyle(Qt::DashLine);

  painter->setPen(pen);
  painter->setRenderHints(QPainter::Antialiasing, true);

  // Horizontal line.
  painter->drawLine(0, m_posY, width(), m_posY);

  // Vertical line.
  painter->drawLine(m_posX, 0, m_posX, height());

  pen.setStyle(Qt::SolidLine);
  painter->setPen(pen);
  painter->setRenderHints(QPainter::Antialiasing, true);

  // Here we handle swapping the price and date windows over the axis whenever
  // the cursor gets to close to the chart axises.
  if (m_rightSwapped == true && m_topSwapped == false)
  {
    drawRightPriceBox(painter);
    drawRightDateBox(painter);
  }
  else if (m_rightSwapped == true && m_topSwapped == true)
  {
    drawTopRightPriceBox(painter);
    drawTopRightDateBox(painter);
  }
  else if (m_leftSwapped == true && m_topSwapped == false)
  {
    drawLeftPriceBox(painter);
    drawLeftDateBox(painter);
  }
  else if (m_leftSwapped == true && m_topSwapped == true)
  {
    drawTopLeftPriceBox(painter);
    drawTopLeftDateBox(painter);
  }
  else if (m_topSwapped == true)
  {
    drawTopPriceBox(painter);
    drawTopDateBox(painter);
  }
  else
  {
    drawDefaultPriceBox(painter);
    drawDefaultDateBox(painter);
  }
}
