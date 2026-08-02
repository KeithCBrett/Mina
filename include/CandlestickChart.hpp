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


#define NUM_X_AXIS_ELEMENTS 101
#define NUM_Y_AXIS_ELEMENTS 10


struct CandleData {
  double open[NUM_X_AXIS_ELEMENTS];
  double close[NUM_X_AXIS_ELEMENTS];
  double high[NUM_X_AXIS_ELEMENTS];
  double low[NUM_X_AXIS_ELEMENTS];
};


class CandlestickChart : public QQuickPaintedItem
{
  Q_OBJECT
  Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor FINAL)
  Q_PROPERTY(double min READ min WRITE setMin NOTIFY minChanged FINAL)
  Q_PROPERTY(double max READ max WRITE setMax NOTIFY maxChanged FINAL)
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

  // This function fills our candle arrays with real stock data.
  void candleData(CandleData &candles);

  // Returns a chunk of stock data we can parse. Offset of zero returns candle
  // for today - 100 days ago.
  std::string candleChunk();

  // Helper function for candleChunk that generates the string we use to make
  // our Alpaca API call (so we can get stock data).
  std::string callString(QDate start_date, QDate end_date, std::string ticker);

  // Converts QDates into Alpaca API dates.
  std::string qDateToAPIDate(QDate inp_date);

  // Helper function for candleChunk that calculates the end date based off of
  // offset and whether or not we end in a weekend.
  QDate endDate();

  // This computes the left most date on our chart (earliest). It goes 100 days
  // into the past, skipping weekends.
  QDate startDate(QDate end_date);

  // Calculates how far back our starting date is if we have to exclude
  // weekends.
  size_t offsetStep(size_t inp_step);

  // Checks whether or not a given day is a weekend.
  bool weekend(QDate inp_date);

signals:
  void dateOffsetChanged();
  void minChanged();
  void maxChanged();
};


#endif
