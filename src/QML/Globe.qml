// Globe.qml is a subcomponent to our dropdown menu. It represents the
// globe in the top right of the screen.

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


import QtQuick
import QtQuick.Effects


Item {
    id: root

    height: ConstSingleton.globeWidth
    width: ConstSingleton.globeWidth

    anchors.left: parent.left
    anchors.top: parent.top
    anchors.rightMargin: ConstSingleton.globeMargin
    anchors.topMargin: ConstSingleton.globeMargin

    Image {
        id: globe

        source: "images/globe.png"

        smooth: true

        // We would rather see the colored overlay we create later.
        visible: false

        anchors.fill: parent

        Behavior on anchors.rightMargin {
            PropertyAnimation {
                easing.type: Easing.InOutQuad
                duration: ConstSingleton.baseAnimationSpeed
            }
        }
    }

    MultiEffect {
        id: colorGlobe
        source: globe

        anchors.fill: globe

        colorization: 1.0
        colorizationColor: ColorScheme.foreground

        // Whenever the globe is rotated, animate it
        Behavior on rotation {
            NumberAnimation {
                from: 0
                to: 720
                duration: 300
            }
        }
    }

    MouseArea {
        id: globeMouse

        anchors.fill: root

        hoverEnabled: true

        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor

        onEntered: {
            colorGlobe.rotation += 360
        }

        onClicked: {
            root.state == "toggle" ? root.state = "" : root.state = "toggle";

            if ((root.state == "") && (aboutMenu.state == "toggle")) {
                aboutMenu.state = "";
            }

            if ((root.state == "") && (helpMenu.state == "toggle")) {
                helpMenu.state = "";
            }

            if ((helpMenu.state == "toggle") || (aboutMenu.state == "toggle")) {
                ConstSingleton.buttonsVisible = false;
            } else {
                ConstSingleton.buttonsVisible = true;
            }
        }
    }

    states: [
        State {
            name: "toggle"

            PropertyChanges {
                target: root.parent
                anchors.leftMargin: (parent.width / 4) * 3
            }
        }
    ]
}
