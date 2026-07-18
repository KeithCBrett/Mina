// Crosshair.hpp represents the class declaration for the crosshair that
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


#ifndef CROSSHAIR_H
#define CROSSHAIR_H


#include <QtQuick/QQuickPaintedItem>


class Crosshair : public QQuickPaintedItem
{
  Q_OBJECT
  Q_PROPERTY(QColor color READ color WRITE setColor FINAL)

  Q_PROPERTY(bool rightSwapped READ rightSwapped WRITE setRightSwapped FINAL)
  Q_PROPERTY(bool leftSwapped READ leftSwapped WRITE setLeftSwapped FINAL)
  Q_PROPERTY(bool topSwapped READ topSwapped WRITE setTopSwapped FINAL)

  Q_PROPERTY(double posX READ posX WRITE setPosX NOTIFY posXChanged FINAL)
  Q_PROPERTY(double posY READ posY WRITE setPosY NOTIFY posYChanged FINAL)

  Q_PROPERTY(double min READ min WRITE setMin NOTIFY minChanged FINAL)
  Q_PROPERTY(double max READ max WRITE setMax NOTIFY maxChanged FINAL)

  Q_PROPERTY(QString price READ price WRITE setPrice NOTIFY priceChanged FINAL)
  QML_ELEMENT

public:
  Crosshair(QQuickItem *parent = nullptr);

  QColor color() const;
  void setColor(const QColor &color);

  double posX() const;
  void setPosX(const double &posX);

  double posY() const;
  void setPosY(const double &posY);

  double min() const;
  void setMin(const double &min);

  double max() const;
  void setMax(const double &max);

  QString price() const;
  void setPrice(const QString &price);

  bool rightSwapped() const;
  void setRightSwapped(const bool &rightSwapped);

  bool leftSwapped() const;
  void setLeftSwapped(const bool &leftSwapped);

  bool topSwapped() const;
  void setTopSwapped(const bool &topSwapped);


  void paint(QPainter *painter) override;

public slots:
  // price() calculates which price to put in the price box based off the
  // current mouse Y position.
  QString getPrice();
  
private:
  QColor m_color;

  double m_posX;
  double m_posY;

  double m_min;
  double m_max;

  QString m_price;

  bool m_rightSwapped;
  bool m_leftSwapped;
  bool m_topSwapped;

  // Sometimes the cursor is in a position where the price and date windows are
  // cutoff. Below we have helper functions to handle the drawing for all of
  // those cases.
  
  // For when cursor is too far to the right.
  void drawRightPriceBox(QPainter *painter);
  void drawRightDateBox(QPainter *painter);

  // For when cursor is too far to the top right.
  void drawTopRightPriceBox(QPainter *painter);
  void drawTopRightDateBox(QPainter *painter);

  // For when cursor is too far to the left.
  void drawLeftPriceBox(QPainter *painter);
  void drawLeftDateBox(QPainter *painter);

  // For when cursor is too far to the top left.
  void drawTopLeftPriceBox(QPainter *painter);
  void drawTopLeftDateBox(QPainter *painter);

  // For when cursor is too far up.
  void drawTopPriceBox(QPainter *painter);
  void drawTopDateBox(QPainter *painter);

  // For when cursor is just right.
  void drawDefaultPriceBox(QPainter *painter);
  void drawDefaultDateBox(QPainter *painter);

  QString stepSize(double inp_first_axis_number);
  QString firstYAxisNumber(double inp_min);

signals:
  void posXChanged();
  void posYChanged();

  void minChanged();
  void maxChanged();

  void priceChanged();

  void rightSwappedChanged();
  void leftSwappedChanged();
  void topSwappedChanged();
};


#endif
