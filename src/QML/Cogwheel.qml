// Cogwheel.qml is a subcomponent to our dropdown menu. It represents the
// cogwheel in the top right of the screen.

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


// For color overlay
import Qt5Compat.GraphicalEffects
import QtQuick


Item {
    id: root

    height: ConstSingleton.cogwheelWidth
    width: ConstSingleton.cogwheelWidth

    anchors.left: parent.left
    anchors.top: parent.top
    anchors.rightMargin: ConstSingleton.cogwheelMargin
    anchors.topMargin: ConstSingleton.cogwheelMargin

    Image {
        id: cogwheel

		source: "images/setting.png"

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

	// Colors setting button orange
	ColorOverlay {
		id: colorCogwheel

		anchors.fill: cogwheel

		source: cogwheel
		color: ColorScheme.foreground

		// Whenever the cogwheel is rotated, animate it
		Behavior on rotation {
			NumberAnimation {
				from: 0
				to: 720
				duration: 300
			}
		}
	}

	MouseArea {
	    id: cogwheelMouse

	    anchors.fill: root

	    hoverEnabled: true

	    cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor

	    onEntered: {
	        colorCogwheel.rotation += 360
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
