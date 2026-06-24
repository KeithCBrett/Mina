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
  QML_ELEMENT

public:
  YAxis(QQuickItem *parent = nullptr);

  QColor color() const;
  void setColor(const QColor &color);

  void paint(QPainter *painter) override;

private:
  QColor m_color;
};


#endif
