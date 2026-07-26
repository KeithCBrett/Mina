// CandlestickChart.hpp represents the class declaration for the bar chart found on the
// 'Browse' page. We register this component as a QML object to be used in our
// U.I.

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


#ifndef CANDLESTICK_CHART_H
#define CANDLESTICK_CHART_H


#include <QtQuick/QQuickPaintedItem>
#include <QColor>


class CandlestickChart : public QQuickPaintedItem
{
  Q_OBJECT
  Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor FINAL)
  Q_PROPERTY(double min READ min WRITE setMin FINAL)
  Q_PROPERTY(double max READ max WRITE setMax FINAL)
  Q_PROPERTY(qint64 dateOffset READ dateOffset WRITE setDateOffset
             NOTIFY dateOffsetChanged FINAL)
  QML_ELEMENT

public:
  CandlestickChart(QQuickItem *parent = nullptr);

  QColor borderColor() const;
  void setBorderColor(const QColor &borderColor);

  double min() const;
  void setMin(const double &min);

  double max() const;
  void setMax(const double &max);

  QString stepSize(double inp_first_axis_number);
  QString firstYAxisNumber();

  qint64 dateOffset() const;
  void setDateOffset(const qint64 &dateOffset);

  void paint(QPainter *painter) override;

private:
  QColor m_borderColor;

  double m_min;
  double m_max;

  qint64 m_dateOffset;

  // Helper functions for painting the axises to the screen.
  void drawYAxis(QPainter *painter, float min, float max);
  void drawXAxis(QPainter *painter);

  // Helper functions for drawing candles to the screen.
  void drawCandle(double high, double low, double open, double close,
                  int index, QPainter *painter);
  // This function calculates the Y-point for each candle according to chart
  // axis.
  double candleYPoint(double inp_num);
  // This function calculates the length of our candlestick body.
  double candleLength(double open, double close);

signals:
  void dateOffsetChanged();
};


#endif
