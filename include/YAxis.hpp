// YAxis.hpp represents the class declaration for the Y-axis associated with
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


#ifndef Y_AXIS_H
#define Y_AXIS_H


#include <QtQuick/QQuickPaintedItem>
#include <QColor>


class YAxis : public QQuickPaintedItem
{
  Q_OBJECT
  Q_PROPERTY(QColor color READ color WRITE setColor FINAL)
  Q_PROPERTY(double min READ min WRITE setMin FINAL)
  Q_PROPERTY(double max READ max WRITE setMax FINAL)
  QML_ELEMENT

public:
  YAxis(QQuickItem *parent = nullptr);

  QColor color() const;
  void setColor(const QColor &color);

  double min() const;
  void setMin(const double &min);

  double max() const;
  void setMax(const double &max);

  QString stepSize(double inp_first_axis_number);
  QString firstYAxisNumber(double inp_double);

  void paint(QPainter *inp_painter) override;

private:
  QColor m_color;
  double m_min;
  double m_max;

  // Below are helper functions for drawing numbers to our Y axis.
  void drawYAxisNumber(QPainter *inp_painter,
                       int inp_location, QString inp_number);
  QString otherYAxisNumber(double inp_min, double inp_max,
                           QString inp_first_axis_number, int inp_position);
};


#endif
