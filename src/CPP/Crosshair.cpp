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

#include <iostream>


#include "../../include/ChartLib.hpp"
//#include "../CPP/ChartLib.cpp"


// Useful constants for drawing lines of known length.
#define SMALL_LINE (width() / 100)
#define MEDIUM_LINE (width() / 50)
#define BIG_LINE (width() / 10)

#define NUM_Y_ELEMENTS 10
#define NUM_X_ELEMENTS 101


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


QString Crosshair::date() const
{
  return m_date;
}


void Crosshair::setDate(const QString &date)
{
  if (date != m_date)
  {
    m_date = date;
    update();
    emit dateChanged();
  }
}


qint64 Crosshair::dateOffset() const
{
  return m_dateOffset;
}


void Crosshair::setDateOffset(const qint64 &dateOffset)
{
  if (dateOffset != m_dateOffset)
  {
    m_dateOffset = dateOffset;
    update();
    emit dateOffsetChanged();
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
                    m_posY - (SMALL_LINE + SMALL_LINE / 2), m_date);
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
                    m_posY - (SMALL_LINE + SMALL_LINE / 2), m_date);
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
                    m_posY + MEDIUM_LINE + SMALL_LINE / 2, m_date);
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
                    m_posY + MEDIUM_LINE + SMALL_LINE / 2, m_date);
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
                    m_posY + MEDIUM_LINE + SMALL_LINE / 2, m_date);
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
  painter->drawText(m_posX + MEDIUM_LINE,
                    m_posY - (SMALL_LINE + SMALL_LINE / 2), m_price);
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
  // painter->drawText(m_posX - BIG_LINE + SMALL_LINE * 1.1,
  //                   m_posY - (SMALL_LINE + SMALL_LINE / 2), "99/99/99");
  painter->drawText(m_posX - BIG_LINE + SMALL_LINE * 1.1,
                    m_posY - (SMALL_LINE + SMALL_LINE / 2), m_date);
}


// price() computes the number to display for the price window to the top right
// of the cursor. This is done via the mouse cursor's Y position.
QString Crosshair::getPrice()
{
  double first_axis_number = ChartLib::firstYAxisNumber(min()).toDouble();
  double step_count = ChartLib::stepSize(first_axis_number, min(), max()).toDouble();

  double bottom_chart_num = first_axis_number - step_count;
  double top_chart_num = first_axis_number + step_count * 10;

  double offset = top_chart_num - bottom_chart_num;
  double y_position = 1.0 - m_posY / height();

  return QString::number(std::round(bottom_chart_num + offset * y_position));
}


QString Crosshair::getDate()
{
  size_t step;
  size_t candle_width = width() / 110;

  QDate date = QDate::currentDate();
  date = date.addDays(-dateOffset());

  if ((m_posX / width()) > 0.5)
  {
    step = std::trunc(m_posX / width() * 100);
  }
  else
  {
    step = std::round(m_posX / width() * 100);
  }

  step = (NUM_X_ELEMENTS - 1) - step;
  step = ChartLib::offsetStep(step - 1, dateOffset());

  if ((m_posX / width()) > 0.5)
  {
    date = date.addDays(-(step));
  }
  else
  {
    date = date.addDays(-(step));
  }

  return date.toString("MM/dd/yy");
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
