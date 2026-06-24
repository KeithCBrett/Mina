// ManualButton.qml represents the U.I. button with the book icon that appears
// whenever the cogwheel in the top right of the screen is clicked.

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


import Qt5Compat.GraphicalEffects
import QtQuick


Item {
    id: root

    visible: ConstSingleton.buttonsVisible

    width: parent.width
    height: (parent.height / 4) - (parent.height / 20)

    Rectangle {
        id: rectangle

        anchors.fill: parent

        anchors.leftMargin: ConstSingleton.borderWidth
        anchors.rightMargin: ConstSingleton.borderWidth
        anchors.bottomMargin: 1

        color: ColorScheme.settingsMenu

        border.color: ColorScheme.settingsMenu
        border.width: ConstSingleton.borderWidth

        MouseArea {
            id: mouse

            anchors.fill: parent

            hoverEnabled: true

            cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor

            onEntered: {
                rectangle.color = ColorScheme.mouseOver
                rectangle.border.color = ColorScheme.foreground
            }

            onExited: {
                rectangle.color = ColorScheme.settingsMenu
                rectangle.border.color = ColorScheme.settingsMenu
            }

            onClicked: {
                stack.push(manualPage)
                cogwheel.state = ""
            }
        }

        Behavior on color {
            ColorAnimation {
                easing.type: Easing.InOutQuad
                duration: ConstSingleton.baseAnimationSpeed
            }
        }
        Behavior on border.color {
            ColorAnimation {
                easing.type: Easing.InOutQuad
                duration: ConstSingleton.baseAnimationSpeed
            }
        }
    }

    Row {
        id: row

        anchors.fill: parent

        leftPadding: row.width / 20
        topPadding: (root.height / 2) - (image.width / 2)

        spacing: 20

        Image {
            id: image

            source: "images/manual.png"

            visible: true

            width:  40
            height: 40

            layer.enabled: true
            layer.effect: ColorOverlay {
                id: colorImage

                visible: true

                anchors.fill: image
                source: image

                color: ColorScheme.foreground
            }
        }

        Text {
            id: text

            text: "Manual"

            topPadding: row.height / 30
            font.family: ConstSingleton.defaultFont
            font.pointSize: ConstSingleton.buttonFontSize

            color: ColorScheme.foreground
        }
    }
}
